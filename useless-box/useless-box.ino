/**
* Useless box
*/


#include "UselessBox.h"


#define UBPinSwitch    4

#define UBPinServoDoor 5
#define UBPinServoFinger  6

#define UBServoDoorStartAngle 0
#define UBServoDoorFinalAngle 45

#define UBServoFingerStartAngle 0
#define UBServoFingerFinalAngle 90

UselessBox uselessBox(UBPinServoDoor, UBServoDoorStartAngle, UBServoDoorFinalAngle,
                      UBPinServoFinger, UBServoFingerStartAngle, UBServoFingerFinalAngle);


void setup() {
    pinMode(UBPinSwitch, INPUT);
    uselessBox.begin();
}

void loop() {
//    if(digitalRead(UBPinSwitch) == HIGH)
//    {
//        uselessBox.switchOff(1);
//    }
    uselessBox.switchOff(1);
    delay(5000);
}


