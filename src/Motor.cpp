#include <Motor.h>
#include <Arduino.h>
#include <math.h>

Motor::Motor(int in1, int in2, int pwm) {
    this->in1 = in1;
    this->in2 = in2;
    this->pwmPin = pwm;
    this->speed = 0;
}

void Motor::setSpeed(int speed) {
    this->speed = abs(speed);

    if (speed > 0) {
        digitalWrite(this->in1, HIGH);
        digitalWrite(this->in2, LOW);
    } else if (speed < 0) {
        digitalWrite(this->in1, LOW);
        digitalWrite(this->in2, HIGH);
    } else {
        digitalWrite(this->in1, LOW);
        digitalWrite(this->in2, LOW);
    }

    analogWrite(this->pwmPin, 255*speed);
}

void Motor::stop() {
    this->speed = 0;
    digitalWrite(this->in1, LOW);
    digitalWrite(this->in2, LOW); 
    analogWrite(this->pwmPin, 0);
}

