#ifndef GOAL_H
#define GOAL_H
#include <elapsedMillis.h>

class Goal {
    public:
        Goal();
        double retrieveAngle();
        double AngleToMovetoGoal();
        void score();
        void beginCamera();
        void sendColor(char c);
        bool haveBall();
        void kickBackground();
        int lightGate = 15;
        int prevGoalDiode = 0;
        int currGoalDiode = 0;
    private:
        int kickerPin = 26;
        elapsedMillis timer;
        elapsedMillis active;
        int kickHold = 1000;
        int threshold = 80;
  

        
};

#endif // GOAL_H
