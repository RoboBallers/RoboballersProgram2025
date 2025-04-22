#include <Arduino.h>
#include <Motor.h>
#include <Movement.h>
#include <LineDetection.h>
#include <CompassSensor.h>
#include <BallFinding.h>
#include <Switches.h>
#include <Goal.h>
#include <Calibration.h>
#include <elapsedMillis.h>

const int FRIN1 = 3;
const int FRIN2 = 2;
const int FREnable = 24;

const int BRIN1 = 4;
const int BRIN2 = 5;
const int BREnable = 25;

const int BLIN1 = 9;
const int BLIN2 = 6;
const int BLEnable = 22;

const int FLIN1 = 31;
const int FLIN2 = 32;
const int FLEnable = 23;

const int kicker = 26;

double OffsetedOrientation = 0;

Motor FL(FLIN1, FLIN2, FLEnable);
Motor FR(FRIN1, FRIN2, FREnable);
Motor BL(BLIN1, BLIN2, BLEnable);
Motor BR(BRIN1, BRIN2, BREnable);

CompassSensor compassSensor;
Movement movement(FL, FR, BL, BR, compassSensor);
LineDetection line;
Calibration calibration(line, compassSensor);
BallFinding ballFinding;
Switches switches;
Goal goal(compassSensor);

elapsedMillis orbitTimeElapsed;


void setup() {
  pinMode(FLIN1, OUTPUT);
  pinMode(FLIN2, OUTPUT);
  pinMode(FLEnable, OUTPUT);

  pinMode(FRIN1, OUTPUT);
  pinMode(FRIN2, OUTPUT);
  pinMode(FREnable, OUTPUT);

  pinMode(BLIN1, OUTPUT);
  pinMode(BLIN2, OUTPUT);
  pinMode(BLEnable, OUTPUT);

  pinMode(BRIN1, OUTPUT);
  pinMode(BRIN2, OUTPUT);
  pinMode(BREnable, OUTPUT);

  pinMode(kicker, OUTPUT);

  Serial.begin(9600);

  // compassSensor.callibrate();
}

void testingballSensors() {
  double ballAngle = ballFinding.ballAngle();
  Serial.println("Ball Angle: " + String(ballAngle));
  for (int i = 0; i < 24; i++) {
    Serial.println("Sensor " + String(i) + String(" ") + String(ballFinding.sensorVals[i]));
  }
}

void testingLineSensors() {
  line.getSensorValues();
  for (int i = 0; i < 24; i++) {
    Serial.println("Sensor " + String(i) + String(" ") + String(line.vals[i]));
  }
}

void testingCompass() {
  Serial.println("Current Desired Angle is " + String(compassSensor.zeroedAngle));
  Serial.println("Current offset is: " + String(compassSensor.currentOffset()));
}

void testingSensors() {

  Serial.println("IR SENSORS");
  Serial.println("-----------");
  Serial.println("-----------");
  Serial.println("-----------");
  Serial.println();

  testingballSensors();

  Serial.println("LINE SENSORS");
  Serial.println("-----------");
  Serial.println("-----------");
  Serial.println("-----------");
  Serial.println();

  testingLineSensors();
}

void testingMotors() {
  FL.setSpeed(0.4);
  delay(1000);
  FR.setSpeed(0.4);
  delay(1000);
  BL.setSpeed(0.4);
  delay(1000);
  BR.setSpeed(0.4);
  delay(1000);
}

void testinghaveBallDiode() {
  Serial.println("Diode Reading Value for have ball: " + String(analogRead(15)));
  delay(300);

}

void lineSensorComparison() {
  for (int i = 0; i < 24; i++ ) {
    Serial.println("Sensor " + String(i) + " - " + String(line.vals[i]) + " - " + String(line.calibrateVals[i]));
  }
}

void testingLineAngle() {
    line.getSensorValues();
    line.getIntersectionAngle(line.vals);
    if (line.lineDetected) {
      line.sensorsDetectedLine();
      Serial.println("Intersection Angle: " + String(line.intersectionAngle));
    } else {
      lineSensorComparison();
      Serial.println("No line detected");
    }
}

void testingMotors2() {
  digitalWrite(FLIN1, HIGH);
  digitalWrite(FLIN2, LOW);
  analogWrite(FLEnable, 100);

  digitalWrite(FRIN1, HIGH);
  digitalWrite(FRIN2, LOW);
  analogWrite(FREnable, 100);

  digitalWrite(BRIN1, HIGH);
  digitalWrite(BRIN2, LOW);
  analogWrite(BREnable, 100);

  digitalWrite(BLIN1, HIGH);
  digitalWrite(BLIN2, LOW);
  analogWrite(BLEnable, 150);
}

void kickerWithOrbit() {
  if(switches.isStart()) {
    Serial.println("Start switch is on");

    Serial.println("Ball Angle: " + String(ballFinding.ballAngle()));
    Serial.println("Ball Orbit: " + String(ballFinding.orbit(ballFinding.ballAngle())));
    movement.movement(ballFinding.orbit(ballFinding.ballAngle()), 0.5);

    if (goal.haveBall()) {
      goal.score();
    }
  } else {
    calibration.calibrateCompassSensor();
    movement.stop();
    if (switches.isCalibrateLine()) {
      Serial.println("Callibrating Line sensors");
      calibration.calibrateLineSensors();
      for (int i = 0; i < 24; i++) {
        Serial.println("Calibrated line value for sensor " + String(i) + " is: " + String(line.calibrateVals[i]));
      }
    }
  }


  goal.kickBackground();
}

void loop() {
  goal.currGoalDiode = analogRead(goal.lightGate);
  if(switches.isStart()) {
    // Serial.println("Start switch is on");
    // Serial.println("Line Angle to move at: " + String(line.Output()));
    if (line.Output() != -1) {
      movement.movement(line.Output(), 0.35);
      delay(10);
    } else {
      movement.stop();
    }
    // Serial.println("Ball Angle: " + String(ballFinding.ballAngle()));
    // Serial.println("Ball Orbit: " + String(ballFinding.orbit(ballFinding.ballAngle())));
    // movement.movement(ballFinding.orbit(ballFinding.ballAngle()), 0.5);
    // movement.movement(315,0.25);

    // if (goal.haveBall()) {
    //   goal.score();
    // }

    // testingLineAngle();
    // Serial.println("Chord length: " + String(line.getChord()));
    Serial.println(line.Output());

    line.lineDetected = false;
  } else {
    // calibration.calibrateCompassSensor();
    movement.stop();
    if (switches.isCalibrateLine()) {
      Serial.println("Callibrating Line sensors");
      calibration.calibrateLineSensors();
      for (int i = 0; i < 24; i++) {
        Serial.println("Calibrated line value for sensor " + String(i) + " is: " + String(line.calibrateVals[i]));
      }
    }
  }

  goal.kickBackground();

  // testingMotors();

//kickerWithOrbit();
// testingLineSensors();
// delay(1000);
// Serial.println();
  //BR.setSpeed(0.5);
  

  // if (abs(goal.prevGoalDiode - goal.currGoalDiode) >= 2) {
  //   goal.score();
  // }

  // goal.prevGoalDiode = goal.currGoalDiode;
}

/*
Orbit with correction
Line avoidance
Kicker

Defense


*/

