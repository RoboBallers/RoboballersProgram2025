#include <Movement.h>
#include <math.h>
#include <trig.h>
#include <math.h>


Movement::Movement(Motor *FLMotor, Motor *FRMotor, Motor *BLMotor, Motor *BRMotor)
    : myPID(&Input, &Output, &Setpoint, kp, ki, kd, REVERSE) {
    this->FLMotor = FLMotor;
    this->FRMotor = FRMotor;   
    this->BLMotor = BLMotor;
    this->BRMotor = BRMotor;
}

double Movement::CorrectionAngle() {
    double OffsetedOrientation;
    double absValDiffOrientation = abs(DirectionSensor.zeroedAngle - DirectionSensor.getOrientation());

    if (absValDiffOrientation > 180) {
      if (DirectionSensor.getOrientation() > DirectionSensor.zeroedAngle) {
          OffsetedOrientation = 360 - absValDiffOrientation;
      } else {
          OffsetedOrientation = absValDiffOrientation - 360;
      }
    } else {
      OffsetedOrientation = -(DirectionSensor.zeroedAngle - DirectionSensor.getOrientation());
    }
}

double Movement::findCorrection(double orientationVal) {
    double correction = 1;
    Input = abs(orientationVal);
    myPID.Compute();

    if (orientationVal > 0)
    {
        correction = -1 * (Output / 100);
    }
    else
    {
        correction = (Output / 100);
    }

    if (orientationVal > -5 && orientationVal < 0)
    {
        correction = 0;
    }
    else if (orientationVal < 5 && orientationVal > 0)
    {
        correction = 0;
    }
    else if (orientationVal > 110)
    {
        correction = -1;
    }
    else if (orientationVal < -110)
    {
        correction = 1;
    }

    return correction;
}
// Need to add orientation to the movement function
void Movement::movement(double intended_angle, double speedfactor) {
    double powerFR = Trig::Sin(intended_angle - 53);
    double powerRR = Trig::Sin(intended_angle - 127);
    double powerRL = Trig::Sin(intended_angle - 233);
    double powerFL = Trig::Sin(intended_angle - 307);

    max_power = fmax(fmax(abs(powerFR), abs(powerFL)), fmax(abs(powerRR), abs(powerRL)));

    powerFR = powerFR / max_power;
    powerFL = powerFL / max_power;
    powerRR = powerRR / max_power;
    powerRL = powerRL / max_power;

    double correctionAngle = CorrectionAngle();
    double correction = findCorrection(correctionAngle);

    powerFR += correction;
    powerFL += correction;
    powerRR += correction;
    powerRL += correction;

    max_power = max(max(abs(powerFR), abs(powerFL)), max(abs(powerRR), abs(powerRL)));

    powerFR = powerFR / max_power;
    powerFL = powerFL / max_power;
    powerRR = powerRR / max_power;
    powerRL = powerRL / max_power;

    this->FLMotor->setSpeed(speedfactor * powerFL);
    this->FRMotor->setSpeed(speedfactor * powerFR);
    this->BLMotor->setSpeed(speedfactor * powerRL);
    this->BRMotor->setSpeed(speedfactor * powerRR);
}