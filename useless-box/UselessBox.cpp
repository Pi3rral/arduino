#include "UselessBox.h"


UselessBox::UselessBox(uint8_t pinServoDoor, uint8_t servoDoorStartAngle, uint8_t servoDoorFinalAngle,
                       uint8_t pinServoFinger, uint8_t servoFingerStartAngle, uint8_t servoFingerFinalAngle
#ifdef USELESSBOX_WITH_HEAD
                       , uint8_t pinServoHead, uint8_t servoHeadStartAngle, uint8_t servoHeadFinalAngle
#endif
                      )
{
    _servoPin[SERVO_DOOR_INDEX] = pinServoDoor;
    _servoStartAngle[SERVO_DOOR_INDEX] = servoDoorStartAngle;
    _servoFinalAngle[SERVO_DOOR_INDEX] = servoDoorFinalAngle;
    
    _servoPin[SERVO_FINGER_INDEX] = pinServoFinger;
    _servoStartAngle[SERVO_FINGER_INDEX] = servoFingerStartAngle;
    _servoFinalAngle[SERVO_FINGER_INDEX] = servoFingerFinalAngle;

#ifdef USELESSBOX_WITH_HEAD
    _servoPin[SERVO_HEAD_INDEX] = pinServoHead;
    _servoStartAngle[SERVO_HEAD_INDEX] = servoHeadStartAngle;
    _servoFinalAngle[SERVO_HEAD_INDEX] = servoHeadFinalAngle;
#endif

}

void UselessBox::begin() {
    _servos[SERVO_DOOR_INDEX].attach(_servoPin[SERVO_DOOR_INDEX]);
    _servos[SERVO_DOOR_INDEX].write(_servoStartAngle[SERVO_DOOR_INDEX]);
    _servoCurrentAngle[SERVO_DOOR_INDEX] = _servoStartAngle[SERVO_DOOR_INDEX];
    _servos[SERVO_FINGER_INDEX].attach(_servoPin[SERVO_FINGER_INDEX]);
    _servos[SERVO_FINGER_INDEX].write(_servoStartAngle[SERVO_FINGER_INDEX]);
    _servoCurrentAngle[SERVO_FINGER_INDEX] = _servoStartAngle[SERVO_FINGER_INDEX];

#ifdef USELESSBOX_WITH_HEAD
    _servos[SERVO_HEAD_INDEX].attach(_servoPin[SERVO_HEAD_INDEX]);
    _servos[SERVO_HEAD_INDEX].write(_servoStartAngle[SERVO_HEAD_INDEX]);
    _servoCurrentAngle[SERVO_HEAD_INDEX] = _servoStartAngle[SERVO_HEAD_INDEX];
#endif
}

void UselessBox::moveServo(uint8_t servo, uint8_t angle, uint8_t speed) {
    int nbIter = angle - _servoCurrentAngle[servo];
    int multiplier = 1;
    if (nbIter < 0) {
        nbIter = nbIter * -1;
        multiplier = -1;
    }
    for (int i = 0; i < nbIter; ++i) {
        _servos[servo].write(_servoCurrentAngle[servo] + multiplier * i);
        delay(speed);
    }
    _servoCurrentAngle[servo] = angle;
}

void UselessBox::switchOff(uint8_t how) {
    switch (how) {
        case 1:
            openClose();
            break;
        default:
            openClose();
            break;
    }
}

void UselessBox::openClose() {
    moveServo(SERVO_DOOR_INDEX, _servoFinalAngle[SERVO_DOOR_INDEX]);
    moveServo(SERVO_FINGER_INDEX, _servoFinalAngle[SERVO_FINGER_INDEX]);
    moveServo(SERVO_FINGER_INDEX, _servoStartAngle[SERVO_FINGER_INDEX]);
    moveServo(SERVO_DOOR_INDEX, _servoStartAngle[SERVO_DOOR_INDEX]);
}
