#include <Movement.h>
#include <math.h>
#include <trig.h>

Movement::Movement(Motor *FLMotor, Motor *FRMotor, Motor *BLMotor, Motor *BRMotor) {
    this->FLMotor = FLMotor;
    this->FRMotor = FRMotor;   
    this->BLMotor = BLMotor;
    this->BRMotor = BRMotor;
}

void Movement::movement(double intended_angle) {
    double powerFR = Trig::Sin(intended_angle - 53);
    double powerRR = Trig::Sin(intended_angle - 127);
    double powerRL = Trig::Sin(intended_angle - 233);
    double powerFL = Trig::Sin(intended_angle - 307);

    max_power = fmax(fmax(abs(powerFR), abs(powerFL)), fmax(abs(powerRR), abs(powerRL)));

    powerFR = powerFR / max_power;
    powerFL = powerFL / max_power;
    powerRR = powerRR / max_power;
    powerRL = powerRL / max_power;

    this->FLMotor->setSpeed(speedfactor);
    this->FRMotor->setSpeed(speedfactor);
    this->BLMotor->setSpeed(speedfactor);
    this->BRMotor->setSpeed(speedfactor);
}