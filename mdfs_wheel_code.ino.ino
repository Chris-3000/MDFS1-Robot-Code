#include <AFMotor.h>
#include <Servo.h>

AF_DCMotor fl(3); // front left
AF_DCMotor fr(4); // front right
AF_DCMotor bl(2); // back left
AF_DCMotor br(1); // back right

Servo gate;
Servo armLeft;
Servo armRight;

void setAllSpeeds(int speed) {
  fl.setSpeed(speed);
  fr.setSpeed(speed);
  bl.setSpeed(speed);
  br.setSpeed(speed);
}

void flControl(int speed) {
  fl.setSpeed(min(abs(speed), 255));
  if (speed > 0) {
    fl.run(BACKWARD);
  }
  else if (speed < 0) {
    fl.run(FORWARD);
  }
  else {
    fl.run(RELEASE);
  }
}

void frControl(int speed) {
  fr.setSpeed(min(abs(speed), 255));
  if (speed > 0) {
    fr.run(BACKWARD);
  }
  else if (speed < 0) {
    fr.run(FORWARD);
  }
  else {
    fl.run(RELEASE);
  }
}

void blControl(int speed) {
  bl.setSpeed(min(abs(speed), 255));
  if (speed > 0) {
    bl.run(BACKWARD);
  }
  else if (speed < 0) {
    bl.run(FORWARD);
  }
  else {
    fl.run(RELEASE);
  }
}

void brControl(int speed) {
  br.setSpeed(min(abs(speed), 255));
  if (speed > 0) {
    br.run(BACKWARD);
  }
  else if (speed < 0) {
    br.run(FORWARD);
  }
  else {
    fl.run(RELEASE);
  }
}

void moveStraight(int speed) { // positive for forward, negative for backward
  flControl(speed);
  frControl(speed);
  blControl(speed);
  brControl(speed);
}

void moveSideways(int speed) { // positive for right, negative for left
  flControl(speed);
  frControl(-speed);
  blControl(-speed);
  brControl(speed);
}

void turn(int speed) { // positive for right, negative for left
  flControl(speed);
  frControl(-speed);
  blControl(speed);
  brControl(-speed);
}

void stop() {
  flControl(0);
  frControl(0);
  blControl(0);
  brControl(0);
}

void setup() {
  stop();

  // setup servos
  gate.attach(44);
  armLeft.attach(45);
  armRight.attach(46);

  // ensure gate is closed
  gate.write(25);
  
  // ensure arm is in starting position
  armLeft.write(100);
  armRight.write(180 - 100);
}

void loop() {
  armLeft.write(0);
  armRight.write(180 - 0);
  delay(2000);
  moveStraight(255);
  delay(400);
  stop();
  delay(1600);
  armLeft.write(27);
  armRight.write(180 - 27);
  delay(2000);
  gate.write(100);
  delay(2000);
  gate.write(25);
  delay(2000);
}
