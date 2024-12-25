#ifndef MOVEMENT_H
#define MOVEMENT_H

#include <Motor.h>

class Movement {
private:
    Motor *FLMotor;
    Motor *FRMotor;
    Motor *BLMotor;
    Motor *BRMotor;

    double speedfactor;
    double max_power; 

public:
    Movement(Motor *FLMotor, Motor *FRMotor, Motor *BLMotor, Motor *BRMotor);
    void movement(double degrees);
    double orbit(double degrees);
    

};

#endif // MOVEMENT_H
