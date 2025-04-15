#include <Arduino.h>
#include <Motor.h>
#include <Movement.h>
#include <LineDetection.h>
#include <CompassSensor.h>
#include <BallFinding.h>
#include <Switches.h>
#include <Goal.h>
#include <Calibration.h>

const int FLIN1 = 2;
const int FLIN2 = 3;
const int FLEnable = 24;

const int FRIN1 = 4;
const int FRIN2 = 5;
const int FREnable = 25;

const int BRIN1 = 6;
const int BRIN2 = 9;
const int BREnable = 22;

const int BLIN1 = 32;
const int BLIN2 = 31;
const int BLEnable = 23;

const int kicker = 26;

double OffsetedOrientation = 0;

Motor FL(FLIN1, FLIN2, FLEnable);
Motor FR(FRIN1, FRIN2, FREnable);
Motor BL(BLIN1, BLIN2, BLEnable);
Motor BR(BRIN1, BRIN2, BREnable);

Movement movement(FL, FR, BL, BR);
LineDetection line;
BallFinding ballFinding;
Calibration callibration(line, compassSensor, movement);
CompassSensor compassSensor;
Switches switches;
Goal goal;

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

  
  // goal.beginCamera();

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
  testingballSensors();
  Serial.println("LINE SENSORS");
  Serial.println("-----------");
  Serial.println("-----------");
  Serial.println("-----------");
  Serial.println();
  testingLineSensors();

  Serial.println("IR SENSORS");
  Serial.println("-----------");
  Serial.println("-----------");
  Serial.println("-----------");
  Serial.println();
 
}

void testingMotors() {
  FL.setSpeed(-0.4);
  delay(200);
  FR.setSpeed(-0.4);
  delay(200);
  BL.setSpeed(-0.4);
  delay(200);
  BR.setSpeed(-0.4);
  delay(200);
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

void loop() {
  // If the compass calibration switch is on
      // current heading will be considered zero
  // otherwise if line calibration switch is on
      // line sensor white color calibration will be constantly updated with robot spinning

  if (switches.isCalibrateAngle()) {
    callibration.calibrateCompassSensor();
  } else if (switches.isCalibrateLine()) {
    callibration.calibrateLineSensors();
  } else {

//  If the match start switch is on, robot will move, else it won't move

/*
  if (switches.isStart()) {
    // put whatever code to only move when start switch is toggled on
  } else {
    Serial.println("Switch is off");
    movement.movement(0,0,0);
  }
*/

  // orbit
  movement.movement(ballFinding.orbit(ballFinding.ballAngle()), 0.4, 0);
  
  // if line is detected, then move at calculated angle, otherwise regular orbit
  /*
   if (line.lineDetected) {
    Serial.println("Line Detected");
    Serial.println("Angle to move at: " + String(line.Output()));
    movement.movement(line.Output(), 0.2, 0);
  } else {
    Serial.println("Line Not Detected");
    movement.movement(ballFinding.orbit(ballFinding.ballAngle()), 0.4, 0);
  }
  */
  }
}

