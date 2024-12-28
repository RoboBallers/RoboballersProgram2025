#include <switches.h>
#include <Arduino.h>

bool Switches::isBlue() {
    return digitalRead(bluePin) == HIGH;
}

bool Switches::isStart() {
    return digitalRead(startPin) == HIGH;
}

bool Switches::isCalibrate() {
    return digitalRead(calibratePin) == HIGH;
}