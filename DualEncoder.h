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

class Debounce {
	public:
    Debounce();
    virtual byte debouncePin(byte pin);
  private:
		byte MYsensitivity = 16;
		unsigned long debounceDontCare = 0xffff0000;
};

class Contact : public Debounce {
#define STABLE 0
#define FALLING 1
#define RISING 2
public:
    Contact();
    Contact (byte pin);
    virtual void begin();
    virtual void setPin(byte pin);
    virtual byte closed();
    virtual bool rose();
    virtual bool fell();
  private:
    byte MYpin;
    byte MYedge;
    byte MYstatus;
};

class Encoder {
  #define CCW -1
  #define CW 1
	public:
    Encoder();
    virtual void setPins(byte pinA, byte pinB);
    virtual void begin();
    virtual int read();
  private:
    byte MYpinA;
    byte MYpinB;
    Contact CpinA;
    Contact CpinB;
};

class DualEncoder {
  public:
    DualEncoder(int innerPinA, int innerPinB, int outerPinA, int outerPinB, int switchPin); //Constructor
    void begin();
    int readInner();       //Read inner encoder : 1>CW, -1>CCW
    int readOuter();       //Read outer encoder : 1>CW, -1>CCW
    int readSwitch();      //Read the status of the switch : 1>Pressed, 0>Released
    
  private:
    byte MYinnerA;
    byte MYinnerB;
    byte MYouterA;
    byte MYouterB;
    byte MYpushButton;
		Encoder inner;
		Encoder outer;
    Contact pushButton;
};

#endif
