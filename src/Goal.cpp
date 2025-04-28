#include <Goal.h>
#include <Arduino.h>
#include <CompassSensor.h>
#include <Switches.h>


Goal::Goal(CompassSensor& compassSensor, Switches& switches) : 
    compassSensor(compassSensor), switches(switches) {

}

void Goal::score() {

    if (timer > (kickHold + 2000))
    {
        timer = 0;
    }
    if (timer <= kickHold)
    {
        digitalWrite(kickerPin, HIGH);
    }
    else
    {
        digitalWrite(kickerPin, LOW);
    }
    active = 0;
}

void Goal::kickBackground() {
    if (active > 2 && timer > kickHold)
    {
        digitalWrite(kickerPin, LOW);
    }
}

void Goal::beginCamera() {
    // Serial2.begin(9600); 
}

void Goal::sendColor(char color) {
    Serial2.write(color);
}

int Goal::retrieveAngle() {
    int value = 0;

    sendColor(switches.getGoalColor());

    if (Serial2.available()) {
        if (Serial2.read() == 0xAA) { // Sync byte detected
            while (Serial2.available() < 4); // wait for full 4 bytes
            int value = 0;
            Serial2.readBytes((char*)&value, sizeof(value));
            Serial.println("Goal Angle from OpenMV: " + String(value));
        }
    }

    return value;
}

