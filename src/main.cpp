#include <Arduino.h>
#include <Motor.h>
#include <Movement.h>
#include <LineDetection.h>
#include <CompassSensor.h>
#include <BallFinding.h>
#include <Switches.h>
#include <Goal.h>

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
int countCalibrate = 0;



BallFinding ballFinding;
// CompassSensor compassSensor;
Switches switches;
LineDetection linedetection;
Goal goal;


Motor FL(FLIN1, FLIN2, FLEnable);
Motor FR(FRIN1, FRIN2, FREnable);
Motor BL(BLIN1, BLIN2, BLEnable);
Motor BR(BRIN1, BRIN2, BREnable);

Movement movement(FL, FR, BL, BR);
// LineDetection line;
// BallFinding ballFinding;

void setup() {
  // put your setup code here, to run once:


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
  linedetection.getSensorValues();
  for (int i = 0; i < 24; i++) {
    Serial.println("Sensor " + String(i) + String(" ") + String(linedetection.vals[i]));
  }
}

void testingCompass() {
  // Serial.println("Current Desired Angle is " + String(compassSensor.zeroedAngle));
  // Serial.println("Current offset is: " + String(compassSensor.currentOffset()));
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
  FL.setSpeed(-100);
  delay(200);
  FR.setSpeed(-100);
  delay(200);
  BL.setSpeed(-100);
  delay(200);
  BR.setSpeed(-100);
  delay(200);
}

void testingMotors2() {
  // digitalWrite(FLIN1, HIGH);
  // digitalWrite(FLIN2, LOW);
  // analogWrite(FLEnable, 100);

  // digitalWrite(FRIN1, HIGH);
  // digitalWrite(FRIN2, LOW);
  // analogWrite(FREnable, 100);

  // digitalWrite(BRIN1, HIGH);
  // digitalWrite(BRIN2, LOW);
  // analogWrite(BREnable, 100);

  // digitalWrite(BLIN1, HIGH);
  // digitalWrite(BLIN2, LOW);
  // analogWrite(BLEnable, 150);
}

void loop() {
  // if (switches.isCalibrateAngle()) {
  //   compassSensor.zeroedAngle = compassSensor.getOrientation();
  // }

  // if (switches.isStart()) {
      // movement.movement(90, 0.3, 0);

      // delay(200);
  // movement.movement(ballFinding.orbit(), 0.25, 0);

      
  // } else {
  //   Serial.println("Swithc is off");
  //   movement.movement(0,0,0);
  // }
  testingballSensors();
  delay(500);


// orbit
  movement.movement(ballFinding.orbit(ballFinding.ballAngle()),0.4,0);
  // Serial.println(ballFinding.ballAngle());
  // delay(200);
  // Serial.println();
  // Serial.println(ballFinding.orbit());
  // delay(200);

  // BL.setSpeed(-0.4);
  // BR.setSpeed(-0.4);
  // FR.setSpeed(-0.4);
  // FL.setSpeed(-0.4);
  // BL.setSpeed(1);
  // delay(200);
  // BL.setSpeed(-1);
  // delay(200);
  
  // testingMotors2();

  // testingMotors();



  // testingMotors();
  // BL.setSpeed(0.7);

  // delay(500);




  
  // if (line.lineDetected) {
    // move.movement(line.Output(), 1);
  // } else {
  //   move.movement(ballFinding.orbit(), 1);
  // }
 
}

