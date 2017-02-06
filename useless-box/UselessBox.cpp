#include "UselessBox.h"


UselessBox::UselessBox(uint8_t pinServoDoor, uint8_t minAngleServoDoor, uint8_t maxAngleServoDoor,
                       uint8_t pinServoFinger, uint8_t minAngleServoFinger, uint8_t maxAngleServoFinger
#ifdef USELESSBOX_WITH_HEAD
                       , uint8_t pinServoHead, uint8_t minAngleServoHead, uint8_t maxAngleServoHead
#endif
                      )
{
    _servoPin[SERVO_DOOR_INDEX] = pinServoDoor;
    _servoMinAngle[SERVO_DOOR_INDEX] = minAngleServoDoor;
    _servoMaxAngle[SERVO_DOOR_INDEX] = maxAngleServoDoor;
    
    _servoPin[SERVO_FINGER_INDEX] = pinServoFinger;
    _servoMinAngle[SERVO_FINGER_INDEX] = minAngleServoFinger;
    _servoMaxAngle[SERVO_FINGER_INDEX] = maxAngleServoFinger;

#ifdef USELESSBOX_WITH_HEAD
    _servoPin[SERVO_HEAD_INDEX] = pinServoHead;
    _servoMinAngle[SERVO_HEAD_INDEX] = minAngleServoHead;
    _servoMaxAngle[SERVO_HEAD_INDEX] = maxAngleServoHead;
#endif

}

void UselessBox::begin() {
    _servos[SERVO_DOOR_INDEX].attach(_servoPin[SERVO_DOOR_INDEX]);
    _servos[SERVO_DOOR_INDEX].write(_servoMinAngle[SERVO_DOOR_INDEX]);
    _servoCurrentAngle[SERVO_DOOR_INDEX] = _servoMinAngle[SERVO_DOOR_INDEX];
    _servos[SERVO_FINGER_INDEX].attach(_servoPin[SERVO_FINGER_INDEX]);
    _servos[SERVO_FINGER_INDEX].write(_servoMinAngle[SERVO_FINGER_INDEX]);
    _servoCurrentAngle[SERVO_FINGER_INDEX] = _servoMinAngle[SERVO_FINGER_INDEX];

#ifdef USELESSBOX_WITH_HEAD
    _servos[SERVO_HEAD_INDEX].attach(_servoPin[SERVO_HEAD_INDEX]);
    _servos[SERVO_HEAD_INDEX].write(_servoMinAngle[SERVO_HEAD_INDEX]);
    _servoCurrentAngle[SERVO_HEAD_INDEX] = _servoMinAngle[SERVO_HEAD_INDEX];
#endif
}

uint8_t UselessBox::anglePercentToDegrees(uint8_t servo, uint8_t percent) {
    return uint8_t(_servoMinAngle[servo]
                   + ((_servoMaxAngle[servo] - _servoMinAngle[servo]) * percent / 100));
}

void UselessBox::moveServo(uint8_t servo, uint8_t percent, uint8_t speed) {
    uint8_t angle = anglePercentToDegrees(servo, percent);
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
            simpleClose();
            break;
        default:
            simpleClose();
            break;
    }
}

void UselessBox::simpleClose() {
    moveServo(SERVO_DOOR_INDEX, 100);
#ifdef USELESSBOX_WITH_HEAD
    moveServo(SERVO_HEAD_INDEX, 100);
#endif
    moveServo(SERVO_FINGER_INDEX, 100);
    moveServo(SERVO_FINGER_INDEX, 0);
#ifdef USELESSBOX_WITH_HEAD
    moveServo(SERVO_HEAD_INDEX, 0);
#endif
    moveServo(SERVO_DOOR_INDEX, 0);
}
