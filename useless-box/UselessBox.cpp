#include "UselessBox.h"


UselessBox::UselessBox(uint8_t pinServoDoor, uint8_t servoDoorStartAngle, uint8_t servoDoorFinalAngle,
                       uint8_t pinServoArm, uint8_t servoArmStartAngle, uint8_t servoDoorArmAngle, uint8_t pinServoHead,
                       uint8_t servoArmHeadAngle, uint8_t servoDoorHeadAngle):
_pinServoDoor(pinServoDoor), _servoDoorStartAngle(servoDoorStartAngle), _servoDoorFinalAngle(servoDoorFinalAngle),
_pinServoArm(pinServoArm), _servoArmStartAngle(servoArmStartAngle), _servoArmFinalAngle(_servoArmFinalAngle),
_pinServoHead(pinServoHead), _servoHeadStartAngle(_servoHeadStartAngle), _servoHeadFinalAngle(_servoHeadFinalAngle)
{

}


void UselessBox::switchOff(uint_8 how) {
    switch (how) {
        case 1:
            openClose();
            break;
        default:
            openClose();
            break;
    }
}


void UselessBox::begin() {
    pinMode(_pinServoDoor, OUTPUT);
    pinMode(_pinServoArm, OUTPUT);
    if (_pinServoHead) {
        pinMode(_pinServoHead, OUTPUT);
    }
}

void UselessBox::openClose() {

}