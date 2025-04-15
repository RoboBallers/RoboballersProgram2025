#include <Switches.h>
#include <Arduino.h>

Switches::Switches() {
    
}
bool Switches::isBlue() {
    return digitalRead(bluePin) == HIGH;
}

bool Switches::isCalibrateAngle() {
    return digitalRead(calibrateAnglePin) == HIGH;
}

bool Switches::isStart() {
    return digitalRead(startPin) == HIGH;
}

bool Switches::isCalibrateLine() {
    return digitalRead(calibrateLinePin) == HIGH;
}