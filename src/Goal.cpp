#include <Goal.h>
#include <Arduino.h>

Goal::Goal() {

}

void Goal::score() {

    if (timer > (kickHold + 2000))
    {
        timer = 0;
    }
    // if (timer <= kickHold && haveBall())
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
    Serial2.begin(9600); 
}

void Goal::sendColor(char color) {
    Serial2.write(color);
}

bool Goal::haveBall() {
    Serial.println("Have Ball Diode reading value: " + String(analogRead(lightGate)));
    
    if (abs(currGoalDiode - prevGoalDiode) > 40)
    {
        return true;
    }
    return false;

}


// double Goal::retrieveAngle() {
//     double value = 0.0;
//     uint8_t *data = reinterpret_cast<uint8_t *>(&value);

//     if (Serial2.available() >= sizeof(double)) {
//         for (size_t i = 0; i < sizeof(double); i++) {
//             data[i] = Serial2.read();
//         }
//         return value;
//     }

//     Serial.println("ERROR: COULD NOT READ FROM OPENMV");
//     return 0.0;
// }
