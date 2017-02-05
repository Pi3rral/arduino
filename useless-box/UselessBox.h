#ifndef ARDUINO_USELESSBOX_H
#define ARDUINO_USELESSBOX_H


#include "Arduino.h"
#include "Servo.h"


//#define USELESSBOX_WITH_HEAD


#define NB_SERVOS 2

#define SERVO_DOOR_INDEX    0
#define SERVO_FINGER_INDEX  1

#ifdef USELESSBOX_WITH_HEAD
#define SERVO_HEAD_INDEX    2
#define NB_SERVOS 3
#endif

#define SPEED_SLOW  30
#define SPEED_STD   20
#define SPEED_FAST  10
#define SPEED_VFAST 5

class UselessBox {

protected:
    Servo _servos[NB_SERVOS];
    uint8_t _servoPin[NB_SERVOS];
    uint8_t _servoStartAngle[NB_SERVOS];
    uint8_t _servoFinalAngle[NB_SERVOS];
    uint8_t _servoCurrentAngle[NB_SERVOS];

public:
    UselessBox(uint8_t pinServoDoor, // Servo opening the main door
               // Start angle and final angle when the door is closed or full open
               uint8_t servoDoorStartAngle, uint8_t servoDoorFinalAngle,
               // Servo manipulating the finger to close the switch
               uint8_t pinServoFinger,
               // Start angle and final angle when the finger is at rest or switching off
               uint8_t servoFingerStartAngle, uint8_t servoDoorFingerAngle
#ifdef USELESSBOX_WITH_HEAD
               // If there is a 3rd servo to up and down the "head" that showing of when the door is opening
               , uint8_t pinServoHead = 0,
               // Start angle and final angle when the head is at rest or showing of
               uint8_t servoFingerHeadAngle = 0, uint8_t servoDoorHeadAngle = 0
#endif
               );

    void begin();

    void moveServo(uint8_t servo, uint8_t angle, uint8_t speed = SPEED_STD);

    void switchOff(uint8_t how);

    void openClose();
};

#endif //ARDUINO_USELESSBOX_H
