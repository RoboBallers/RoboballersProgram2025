#include <Switches.h>
#include <Arduino.h>

Switches::Switches() {
    
}

bool Switches::isDiodeCalibration() {
    return digitalRead(calDiodePin) == HIGH;
}

bool Switches::isStart() {
    return digitalRead(startPin) == HIGH;
}

bool Switches::isCalibrateLine() {
    return digitalRead(calibrateLinePin) == HIGH;
}