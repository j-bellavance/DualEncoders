//=========================================================================================================
//Reading dual concentric encoders from Propwash
//
//These encoders have 2 steps per detent.
//This means that reading only the rising (or falling) edge of the signal at pin A
//will report a change only at every other detent.
//This sketch solves the problem by reading on both the rising and the falling edge of the signal at pin A
//As a result, a change is reported on each detent.
//---------------------------------------------------------------------------------------------------------

//======================================================================================
// Encoder   Arduino
// outerB-------2       
// outerA-------3
//    Com--+------+--Gnd
//    Com--+      |
// innerA-------4 |
// innerB-------5 |
// Switch-------6 |
// SwitchCom------+
//---------------------------------------------------------------------------------------
#include <Keyboard.h>
#include <DualEncoder.h>

//              (innerA, innerB, outerA, outerB, Switch)
DualEncoder com1(  2,       3,      4,      5,      6   );

//setup=====================================================
void setup() {
  Keyboard.begin();
  com1.begin();
  Serial.println("Starting");
  Serial.println(CCW);
  Serial.println(CW);
}//setup----------------------------------------------------

//loop=====================================================================
void loop() {
  int stat = com1.readInner(); 
  if (stat == CCW) Keyboard.print("u");
  if (stat ==  CW) Keyboard.print("d");
  stat = com1.readOuter(); 
  if (stat == CCW) Keyboard.print("U");
  if (stat ==  CW) Keyboard.print("D");
  if (com1.readSwitch() == 0) {
    Keyboard.press(ctrlKey);
    Keyboard.press('9');
    delay(100);
    Keyboard.releaseAll();
  }
}//loop-------------------------------------------------------------------
