//
// Created by Pierre Leca on 2017-02-05.
//

#ifndef ARDUINO_USELESSBOX_H
#define ARDUINO_USELESSBOX_H

class UselessBox {

protected:
    uint8_t _pinServoDoor;
    uint8_t _servoDoorStartAngle;
    uint8_t _servoDoorFinalAngle;
    uint8_t _pinServoArm;
    uint8_t _servoArmStartAngle;
    uint8_t _servoArmFinalAngle;
    uint8_t _pinServoHead;
    uint8_t _servoHeadStartAngle;
    uint8_t _servoHeadFinalAngle;

public:
    UselessBox(uint8_t pinServoDoor, // Servo opening the main door
               // Start angle and final angle when the door is closed or full open
               uint8_t servoDoorStartAngle, uint8_t servoDoorFinalAngle,
               // Servo manipulating the arm to close the switch
               uint8_t pinServoArm,
               // Start angle and final angle when the arm is at rest or switching off
               uint8_t servoArmStartAngle, uint8_t servoDoorArmAngle,
               // If there is a 3rd servo to up and down the "head" that showing of when the door is opening
               uint8_t pinServoHead = null,
               // Start angle and final angle when the head is at rest or showing of
               uint8_t servoArmHeadAngle = 0, uint8_t servoDoorHeadAngle = 0);

    void begin();

    void switchOff(uint_8 how);

    void openClose();
};

#endif //ARDUINO_USELESSBOX_H
