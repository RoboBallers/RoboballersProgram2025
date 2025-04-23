#ifndef GOAL_H
#define GOAL_H
#include <elapsedMillis.h>
#include <CompassSensor.h>

class Goal {
    public:
        Goal(CompassSensor& CompassSensor);
        double retrieveAngle();
        double AngleToMovetoGoal();
        void score();
        void beginCamera();
        void sendColor(char c);
        void kickBackground();
        int lightGate = 15;
        int prevGoalDiode = 0;
        int currGoalDiode = 0;
        int minDiode = 1000;
        int maxDiode = 0;

    private:
        CompassSensor& compassSensor;
        int kickerPin = 26;
        elapsedMillis timer;
        elapsedMillis active;
        int kickHold = 1500; // originally 1000
        int threshold = 80;
  

        
};

#endif // GOAL_H
