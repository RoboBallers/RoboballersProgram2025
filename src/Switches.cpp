#include <Switches.h>
#include <Arduino.h>

Switches::Switches() {
    
}

bool Switches::isCompassCalibration() {
    return digitalRead(comapssCalibrationPin) == HIGH;
}

bool Switches::isStart() {
    return digitalRead(startPin) == HIGH;
}

bool Switches::isCalibrateLine() {
    return digitalRead(calibrateLinePin) == HIGH;
}

char Switches::getGoalColor() {
    if (digitalRead(goalColorPin) == HIGH) {
        return 'y';
    } else {
        return 'b';
    }
}