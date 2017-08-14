//======================================================================================
//A Library to read dual encoders with 2 steps per detent, like those sold by Propwash
//Created by Jacques Bellavance, August 13, 2017
//Version 1.1 (Added debounce and EMF filter)
//            (Uses four classes instead of one)
//Released into the public domain
//--------------------------------------------------------------------------------------
#include "Arduino.h"
#include "DualEncoder.h"


/////////////////////////
//      Debounce       //
/////////////////////////

//Constructor============
Debounce::Debounce() {
}//Debounce--------------

//debouncePin==================================================================================
//pin: the pin that has to be debounced
//ABSTRACT
//  Read pin 16 times
//  While (pin reads are not identical)
//See https://github.com/j-bellavance/EdgeDebounce/blob/master/Tutorials/tutorial.pdf.
//Can also filter Electromagnetic Field (EMF) interferences
//---------------------------------------------------------------------------------------------
byte Debounce::debouncePin(byte pin) {
	unsigned long pinState;
	do {
		pinState = 0xffffffff;
		for (byte i = 1; i <= MYsensitivity; i++) pinState = (pinState << 1) | digitalRead(pin);
	} while ((pinState != debounceDontCare) && (pinState != 0xffffffff));
	return byte(pinState & 0x00000001);
}//--------------------------------------------------------------------------------------------


 /////////////////////////
 //       Contact       //
 /////////////////////////

//============================================================================
Contact::Contact() {}  //Constructor
//----------------------------------------------------------------------------
void Contact::setPin(byte pin) { MYpin = pin; }  //MY variable
//----------------------------------------------------------------------------
void Contact::begin() {pinMode(MYpin, INPUT_PULLUP); }  //Set pinMode
//----------------------------------------------------------------------------
byte Contact::closed() {
	byte pinStatus = debouncePin(MYpin);         //Debounce digitalRead()
	pinStatus = !pinStatus;                      //Always PULLUP
	if (MYstatus == pinStatus) MYedge = STABLE;  //state is stable
	else { if (pinStatus) MYedge = RISING;       //Just rose
         else           MYedge = FALLING;	}    //Just fell
	MYstatus = pinStatus;                        //Record new state
	return pinStatus;                            //Return status
}//----------------------------------------------------------------------------
bool Contact::rose() { return MYedge == RISING; }  //On last call to closed()
//-----------------------------------------------------------------------------
bool Contact::fell() { return MYedge == FALLING; } //On last call to closed()
//-----------------------------------------------------------------------------

/////////////////////////
//      Encoder        //
/////////////////////////

//=======================================================================================
Encoder::Encoder() {}  //Constructor
//---------------------------------------------------------------------------------------
void Encoder::setPins(byte pinA, byte pinB) { 
  MYpinA = pinA; MYpinB = pinB;            //MY variables
  CpinA.setPin(pinA); CpinB.setPin(pinB);  //Set Contacts
}//--------------------------------------------------------------------------------------
void Encoder::begin() { CpinA.begin(); CpinB.begin(); } //Set pinModes
//---------------------------------------------------------------------------------------
int Encoder::read() {
		int pinA = CpinA.closed();                  //Get CpinA's status
		int pinB = CpinB.closed();                  //Get CpinB's status
		if (CpinA.rose()) return (!pinB << 1) - 1;  //Rising edge of A  --> Out
		if (CpinA.fell()) return (pinB << 1) - 1;   //Falling edge of A --> Out
                                                // (var << 1) - 1 is {0, 1} to {-1, 1}
		return 0;                                   //No click
}//--------------------------------------------------------------------------------------


/////////////////////////
//     DualEncoder     //
/////////////////////////

//DualEncoder (Constructor)======================================================
//Arguments : The Arduino pins where the encoders and the switch are connected
//DualEncoder com1(2,3,4,5,6); //For the following setup:
//  Encoder   Arduino
//      B-------3       
//      A-------2
//    Com--+------+--Gnd
//    Com--+      |
//      A-------4 |
//      B-------5 |
// Switch-------6 |
// Switch---------+
//-------------------------------------------------------------------------------
DualEncoder::DualEncoder(int innerPinA, int innerPinB, 
                         int outerPinA, int outerPinB, 
                         int switchPin) {
  MYinnerA = innerPinA; MYinnerB = innerPinB;  //MY variables
  inner.setPins(MYinnerA, MYinnerB);           //Set Encoder
	MYouterA = outerPinA;	MYouterB = outerPinB;  //MY variables
	outer.setPins(MYouterA, MYouterB);           //Set Encoder
	MYpushButton = switchPin;                    //MY variable
  pushButton.setPin(MYpushButton);             //Set Contact
  inner.begin(); outer.begin();                //To make it backward compatible
}//-------------------------------------------------------------------------------
void DualEncoder::begin() {
  inner.begin(); outer.begin();	pushButton.begin(); } //Set pinModes
//--------------------------------------------------------------------------------
int DualEncoder::readInner() { return inner.read(); }
//--------------------------------------------------------------------------------
int DualEncoder::readOuter() { return outer.read(); }
//--------------------------------------------------------------------------------
int DualEncoder::readSwitch() {
  if (pushButton.closed()) { while (pushButton.closed()) {;} return 0; }
  else                                                       return 1;
}//-------------------------------------------------------------------------------


