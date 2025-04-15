#include <Movement.h>
#include <math.h>
#include <trig.h>
#include <math.h>


Movement::Movement(Motor& FLMotor, Motor& FRMotor, Motor& BLMotor, Motor& BRMotor)
    : FLMotor(FLMotor), FRMotor(FRMotor), BLMotor(BLMotor), BRMotor(BRMotor),
      myPID(&Input, &Output, &Setpoint, this->kp, this->ki, this->kd, REVERSE)  
{
    myPID.SetMode(AUTOMATIC); 
}

double Movement::findCorrection(double desiredOrientation) {
  double correction = 0;
  double orientationDiff = compassSensor.currentOffset() - desiredOrientation;

  Input = abs(orientationDiff);
  myPID.Compute();

  if (orientationDiff > 90) {
    correction = -1;
  } else if (orientationDiff < -90) {
    correction = 1;
  } else if (orientationDiff > 0) {
    correction = -1 * (Output / 100);
  } else if (orientationDiff < 0) {
    correction = (Output / 100);
  }

  return correction;
}

// Need to add orientation to the movement function
void Movement::movement(double intended_movement_angle, double speedfactor, double desiredOrientation) {
    double powerFR = Trig::Sin(intended_movement_angle - 53);
    double powerRR = Trig::Sin(intended_movement_angle - 127);
    double powerRL = Trig::Sin(intended_movement_angle - 233);
    double powerFL = Trig::Sin(intended_movement_angle - 307);

    max_power = fmax(fmax(abs(powerFR), abs(powerFL)), fmax(abs(powerRR), abs(powerRL)));

    powerFR = powerFR / max_power;
    powerFL = powerFL / max_power;
    powerRR = powerRR / max_power;
    powerRL = powerRL / max_power;

    // double correction = findCorrection(desiredOrientation);

    // powerFR += correction;
    // powerFL += correction;
    // powerRR += correction;
    // powerRL += correction;

    // max_power = fmax(fmax(abs(powerFR), abs(powerFL)), fmax(abs(powerRR), abs(powerRL)));

    // powerFR = powerFR / max_power;
    // powerFL = powerFL / max_power;
    // powerRR = powerRR / max_power;
    // powerRL = powerRL / max_power;

    // Serial.println(speedfactor * powerFL);
    // Serial.println(speedfactor * powerFR);
    // Serial.println(speedfactor * powerRL);
    // Serial.println(speedfactor * powerRR);

    // if (powerFL > 1) {
    //   powerFL = 1;
    // } else if (powerFL < -1) {
    //   powerFL = -1;
    // }

    // if (powerFR > 1) {
    //   powerFR = 1;
    // } else if (powerFR < -1) {
    //   powerFR = -1;
    // }

    // if (powerRL > 1) {
    //   powerRL = 1;
    // } else if (powerRL < -1) {
    //   powerRL = -1;
    // }

    // if (powerRR > 1) {
    //   powerRR = 1;
    // } else if (powerRR < -1) {
    //   powerRR = -1;
    // }


    this->FLMotor.setSpeed(speedfactor * powerFL);
    this->FRMotor.setSpeed(-speedfactor * powerFR);
    Serial.println((speedfactor+0.4) * powerRL);
    this->BLMotor.setSpeed(speedfactor * powerRL);
    this->BRMotor.setSpeed(-speedfactor * powerRR);
}

void Movement::circle() {
    this->FLMotor.setSpeed(0.2);
    this->FRMotor.setSpeed(0.2);
    this->BLMotor.setSpeed(0.2);
    this->BRMotor.setSpeed(0.2);
}