/**
* Useless box
*/


#include "UselessBox.h"

#define UBPinSwitch    4

#define UBPinServoDoor 5
#define UBPinServoArm  6

#define UBServoDoorStartAngle 0
#define UBServoDoorFinalAngle 30

#define UBServoArmStartAngle 0
#define UBServoArmFinalAngle 45

UselessBox uselessBox(UBPinServoDoor, UBServoDoorStartAngle, UBServoDoorFinalAngle,
                      UBPinServoArm, UBServoArmStartAngle, UBServoArmFinalAngle);

void setup() {
    uselessBox.begin();
    pinMode(UBPinSwitch, INPUT);
}

void loop() {

}
