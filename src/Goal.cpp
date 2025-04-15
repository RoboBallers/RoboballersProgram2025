#include <Goal.h>
#include <Arduino.h>
#include <CompassSensor.h>

Goal::Goal(CompassSensor& compassSensor) : compassSensor(compassSensor) {

}

void Goal::score() {
    if (haveBall() && compassSensor.currentOffset(retrieveAngle())) {
        digitalWrite(kickerPin, HIGH);
    }
}

void Goal::beginCamera() {
    Serial2.begin(9600); 
}

void Goal::sendColor(char color) {
    Serial2.write(color);
}

bool Goal::haveBall() {
    Serial.println("Have Ball Diode reading value: " + String(analogRead(lightGate)));
    // 700 needs to be tuned, not sure if it will work
    if (analogRead(lightGate) < 700)
    {
        return false;
    }
    else
    {
        return true;
    }

}


double Goal::retrieveAngle() {
    double value = 0.0;
    uint8_t *data = reinterpret_cast<uint8_t *>(&value);

    if (Serial2.available() >= sizeof(double)) {
        for (size_t i = 0; i < sizeof(double); i++) {
            data[i] = Serial2.read();
        }
        return value;
    }

    Serial.println("ERROR: COULD NOT READ FROM OPENMV");
    return 0.0;
}
