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

#include <DualEncoder.h>

//              (innerA, innerB, outerA, outerB, Switch)
DualEncoder com1(  4,      5,      3,      2,      6   );

//setup=====================================================
void setup() {
  Serial.begin(9600);          //To display on the monitor
  Serial.println("Starting");
}//setup----------------------------------------------------

//loop=====================================================================
void loop() {
  int stat = com1.readInner();
  if (stat == CCW) Serial.println("sim/radios/stby_com1_coarse_down");
  if (stat ==  CW) Serial.println("sim/radios/stby_com1_coarse_up");
  stat = com1.readOuter();
  if (stat == CCW) Serial.println("sim/radios/stby_com1_fine_down");
  if (stat ==  CW) Serial.println("sim/radios/stby_com1_fine_up");
  if (com1.readSwitch() == 0) Serial.println("sim/radios/com1_standy_flip");
}//loop-------------------------------------------------------------------
