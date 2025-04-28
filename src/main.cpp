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

bool compassdone = false;
bool compassDone2 = false;

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
Goal goal(compassSensor, switches);

elapsedMillis orbitBallTimer;
elapsedMillis lineAvoidanceTimer;

bool ballInFront = false;
int lineCount = 0;

double prevDesiredOrientation = 0;
double desiredOrientation = 0;

int haveBallThreshold = 400;


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
  Serial2.begin(9600);
  compassSensor.callibrate();
  // goal.beginCamera();
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

void testingCamera() {
  goal.retrieveAngle();
}

void process() {
  if(switches.isStart()) {
    // double haveBallAverage = (ballFinding.sensorVals[0] + ballFinding.sensorVals[23] + ballFinding.sensorVals[1]) / 3;
    Serial.println("Start switch is on");
    // Serial.println("Line Angle to move at: " + String(line.Output()));
    // desiredOrientation = goal.retrieveAngle();

    // Serial.println("Desired Orientation: " + String(desiredOrientation));

    // if (abs(desiredOrientation) > 45 && desiredOrientation != 999) {
    //   Serial.println("Desired Orientation is greater than 45 so changing it to 0");
    //   desiredOrientation = 0;
    // }

    // if (desiredOrientation == 999) {
    //   Serial.println("Desired Orientation is 999 so changing it to 0");
    //   desiredOrientation = 0;
    // } else {
    //     desiredOrientation = compassSensor.currentOffset() - desiredOrientation;
    // }

    // Serial.println("Desired Orientation: " + String(desiredOrientation));
    double lineAngle = line.Output();
    double orbitAngle = ballFinding.orbit(ballFinding.ballAngle());


    if (lineAngle != -1 && line.getChord() > 0.15) {
      if (lineCount == 0 && lineAvoidanceTimer > 0) {
        lineAvoidanceTimer = 0;
      }
      if (lineCount >= 7) {
        Serial.println("Line count passed");
        Serial.println();
        Serial.println();
        Serial.println();
        Serial.println();
        Serial.println();
        Serial.println();
        Serial.println();
        Serial.println();
        Serial.println();
        Serial.println();
        Serial.println();
        Serial.println();
        Serial.println();
        movement.movement(orbitAngle, 0.55, 0);
        // movement.movement(0,0.55,0);
        lineCount = 0;
      } else {
        lineCount++;
        movement.movement(lineAngle, 0.55, 0);
      }
      // }
        // Serial.println("Line Angle to move at: " + String(lineAngle));
    } 
    else {
        movement.movement(orbitAngle, 0.55, 0);
        // movement.rotateToGoal(desiredOrientation,0.75);
        Serial.println("Ball Orbit: " + String(orbitAngle));
        if (orbitAngle == 0) {
          if (!ballInFront) {
              ballInFront = true;
              orbitBallTimer = 0;
          } else if (orbitBallTimer >= 500) {
              goal.score();
          }
      } else {
          ballInFront = false;
      }
    }
    // Serial.println("Ball Angle: " + String(ballFinding.ballAngle()));
    // Serial.println("Ball Orbit: " + String(ballFinding.orbit(ballFinding.ballAngle())));

    // testingLineAngle();
    // Serial.println("Chord length: " + String(line.getChord()));
    // Serial.println("Avoidance angle: " + String(line.Output()));

    // line.lineDetected = false;
  } else if (switches.isCompassCalibration()) {
    Serial.println("Callibrating Compass");
    movement.stop();
    calibration.calibrateCompassSensor();
    compassdone = true;
    if (compassdone && !compassDone2) {
        compassDone2 = true;
        FL.setSpeed(0.3);
        delay(400);
    }
    movement.stop();
  }
  
  else if (switches.isCalibrateLine()) {
    movement.stop();
    Serial.println("Callibrating Line sensors");
    calibration.calibrateLineSensors();

      // for (int i = 0; i < 24; i++) {
      //   Serial.println("Calibrated line value for sensor " + String(i) + " is: " + String(line.calibrateVals[i]));
      // }
    } else {
      movement.stop();
    }

  goal.kickBackground();

  if (lineAvoidanceTimer > 1500) {
    // Serial.println("Line avoidance timer being reset");
    lineAvoidanceTimer = 0;
    lineCount = 0;
  }
}

void testingMovementWithCompass(double angle, double speedFactor, double desiredOrientation) {
  if (switches.isCompassCalibration()) {
    movement.stop();
    calibration.calibrateCompassSensor();
    Serial.println("Callibrating Compass Sensor");
    compassdone = true;
    if (compassdone && !compassDone2) {
        compassDone2 = true;
        FL.setSpeed(0.3);
        delay(400);
    }
  } else {
    movement.movement(angle,speedFactor,desiredOrientation);
  }
}

void testingRotateToGoal(double desiredOrientation, double speedFactor) {
  if(switches.isStart()) {
    // Serial.println("Start switch is on");
    // Serial.println("Line Angle to move at: " + String(line.Output()));
    // desiredOrientation = goal.retrieveAngle();

    double orbit_val = ballFinding.orbit(ballFinding.ballAngle());
    movement.movement(orbit_val, 0.55, desiredOrientation);

  } else if (switches.isCompassCalibration()) {
    Serial.println("Callibrating Compass");
    movement.stop();
    calibration.calibrateCompassSensor();
    compassdone = true;
    if (compassdone && !compassDone2) {
        compassDone2 = true;
        FL.setSpeed(0.3);
        delay(400);
    }
    movement.stop();
  } else {
      movement.stop();
    }
}

void loop() {
  process();


  //  delay(400);
  // testingCamera();
  // Serial.println();
  // delay(400);

  // testingMovementWithCompass(45,0.6,15);

  // testingCamera();

  // testingRotateToGoal(goal.retrieveAngle(), 0.45);

  // Serial.println("Hello");
  // if (Serial2.available()) {
  //   char c = Serial2.read();
  //   Serial.println(c);  // Just print each character as it comes
  // }

    //  if (Serial2.available()) {
    //     if (Serial2.read() == 0xAA) { // Sync byte detected
    //         while (Serial2.available() < 4); // wait for full 4 bytes
    //         int value = 0;
    //         Serial2.readBytes((char*)&value, sizeof(value));
    //         Serial.println("Goal Angle from OpenMV: " + String(value));
    //     }
    // }

  // testingSensors();

}

