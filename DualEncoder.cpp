//======================================================================================
//A Library to read dual encoders with 2 steps per detent, like those sold by Propwash
//Created by Jacques Bellavance, january 18, 2017
//Released into the public domain
//--------------------------------------------------------------------------------------
#include "Arduino.h"
#include "DualEncoder.h"

//DualEncoder (Constructor)=============================================================================
//Arguments : The Arduino pins where the encoders and the switch are connected
//DualEncoder com1(3,2,4,5,6); //For the following setup:
//  Encoder   Arduino
//      B-------2       
//      A-------3
//    Com--+------+--Gnd
//    Com--+      |
//      A-------4 |
//      B-------5 |
// Switch-------6 |
// Switch---------+
//------------------------------------------------------------------------------------------------------
DualEncoder::DualEncoder(int innerPinA, int innerPinB, int outerPinA, int outerPinB, int switchPin) {
  pinMode(innerPinA, INPUT_PULLUP);  //All pins in INPUT_PULLUP mode
  pinMode(innerPinB, INPUT_PULLUP);
  pinMode(outerPinA, INPUT_PULLUP);
  pinMode(outerPinB, INPUT_PULLUP);
  pinMode(switchPin, INPUT_PULLUP);
  inner.pinA = innerPinA;
	inner.pinB = innerPinB;
  inner.status = 0;
	outer.pinA = outerPinA;
	outer.pinB = outerPinB;
  outer.status = 0;
  momentarySwitch = switchPin;
}//DualEncoder-----------------------------------------------------------------------------------------

//readInner===========================
//Read inner encoder
//------------------------------------
int DualEncoder::readInner() {
	int rotation = 0;                         //Default : No rotation
	int pinA = digitalRead(inner.pinA);       //Read pin A
	int pinB = digitalRead(inner.pinB);       //Read pin B
	if ((!pinA) && (inner.status)) {          //If on the falling edge,
		if (pinB) rotation = 1;                   //If B is high : clockwise
		else      rotation = -1;                  //If not :       counter-clockwise
	}
	if ((pinA) && (!inner.status)) {          //If on the rising edge,
		if (pinB) rotation = -1;                  //If B is high : counter-clockwise
		else      rotation = 1;                   //If not :       clockwise
	}
	inner.status = pinA;
	return rotation;                          //Return the reading
}//reradInner-------------------------

//readOuter===========================
//Read outer encoder
//------------------------------------
int DualEncoder::readOuter() {
	int rotation = 0;                         //Default : No rotation
	int pinA = digitalRead(outer.pinA);       //Read pin A
	int pinB = digitalRead(outer.pinB);       //Read pin B
	if ((!pinA) && (outer.status)) {          //If on the falling edge,
		if (pinB) rotation = 1;                   //If B is high : clockwise
		else      rotation = -1;                  //If not :       counter-clockwise
	}
	if ((pinA) && (!outer.status)) {          //If on the rising edge,
		if (pinB) rotation = -1;                  //If B is high : counter-clockwise
		else      rotation = 1;                   //If not :       clockwise
	}
	outer.status = pinA;
	return rotation;                          //Return the reading
}//readOuter--------------------------

//readSwitch=================================
//Read encoder's momentary switch
//-------------------------------------------
int DualEncoder::readSwitch() {
	if (digitalRead(momentarySwitch) == 0) {
		while (digitalRead(momentarySwitch) == 0) {
      delay(50);
    }
    return 0;
	}
  else return 1;
}//readSwitch--------------------------------


