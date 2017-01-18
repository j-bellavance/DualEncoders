//======================================================================================
//A Library to read dual encoders with 2 steps per detent, like those sold by Propwash
//Created by Jacques Bellavance, january 18, 2017
//Released into the public domain
//--------------------------------------------------------------------------------------

#include "Arduino.h"

#ifndef DualEncoder_h
#define DualEncoder_h

#define CW 1
#define CCW -1

class DualEncoder {
  public:
    DualEncoder(int innerPinA, int innerPinB, int outerPinA, int outerPinB, int switchPin); //Constructor
    int readInner();   //Read inner encoder : 1>CW, -1>CCW
    int readOuter();   //Read outer encoder : 1>CW, -1>CCW
    int readSwitch();  //Read the status of the switch : 0>Pressed, 1>Released
    
  private:
		struct encoder {
			int pinA;
			int pinB;
			int status;
		};
		encoder inner;
		encoder outer;
		int momentarySwitch;  //Switch Pin
};

#endif
