#include <Movement.h>
#include <math.h>
#include <trig.h>


Movement::Movement(Motor& FLMotor, Motor& FRMotor, Motor& BLMotor, Motor& BRMotor)
    : FLMotor(FLMotor), FRMotor(FRMotor), BLMotor(BLMotor), BRMotor(BRMotor)
{
    myPID = new PID(&Input, &Output, &Setpoint, kp, ki, kd, REVERSE);
    myPID->SetMode(AUTOMATIC);
}


// Need to add orientation to the movement function
void Movement::movement(double intended_movement_angle, double speedfactor) {
  intended_movement_angle -= 180;

  if (intended_movement_angle < 0) {
    intended_movement_angle += 360;
  }
  
    double powerFR = Trig::Sin(intended_movement_angle - 53);
    double powerRR = Trig::Sin(intended_movement_angle - 127);
    double powerRL = Trig::Sin(intended_movement_angle - 233);
    double powerFL = Trig::Sin(intended_movement_angle - 307);

    max_power = fmax(fmax(abs(powerFR), abs(powerFL)), fmax(abs(powerRR), abs(powerRL)));

    powerFR = powerFR / max_power;
    powerFL = powerFL / max_power;
    powerRR = powerRR / max_power;
    powerRL = powerRL / max_power;


    if (powerFL > 1) {
      powerFL = 1;
    } else if (powerFL < -1) {
      powerFL = -1;
    }

    if (powerFR > 1) {
      powerFR = 1;
    } else if (powerFR < -1) {
      powerFR = -1;
    }

    if (powerRL > 1) {
      powerRL = 1;
    } else if (powerRL < -1) {
      powerRL = -1;
    }

    if (powerRR > 1) {
      powerRR = 1;
    } else if (powerRR < -1) {
      powerRR = -1;
    }


    this->FLMotor.setSpeed(speedfactor * powerFL);
    this->FRMotor.setSpeed(speedfactor * powerFR);
    this->BLMotor.setSpeed(speedfactor * powerRL);
    this->BRMotor.setSpeed(speedfactor * powerRR);
}

void Movement::circle() {
    this->FLMotor.setSpeed(0.2);
    this->FRMotor.setSpeed(0.2);
    this->BLMotor.setSpeed(0.2);
    this->BRMotor.setSpeed(0.2);
}

void Movement::stop() {
    this->FLMotor.setSpeed(0);
    this->FRMotor.setSpeed(0);
    this->BLMotor.setSpeed(0);
    this->BRMotor.setSpeed(0);
}