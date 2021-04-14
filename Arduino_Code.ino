#include <AFMotor.h>
#include <Servo.h>

const int mtr1 = 1;
const int mtr2 = 2;
const int mtr3 = 3;
const int mtr4 = 4;

AF_DCMotor motor1(mtr1, MOTOR12_64KHZ); // DC motor on M1 with 64KHz pwm
AF_DCMotor motor2(mtr2, MOTOR12_64KHZ); // DC motor on M2 with 64KHz pwm
AF_DCMotor motor3(mtr3, MOTOR12_64KHZ); // DC motor on M3 with 64KHz pwm
AF_DCMotor motor4(mtr4, MOTOR12_64KHZ); // DC motor on M4 with 64KHz pwm
Servo servo1;

int Speed = 120;
String voice;

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps
  motor1.setSpeed(Speed); // set the motor1 speed between 0 and 255
  motor2.setSpeed(Speed); //  set the motor2 speed between 0 and 255
  motor3.setSpeed(Speed); // set the motor3 speed between 0 and 255
  motor4.setSpeed(Speed); //set the  motor4 speed between 0 and 255
  servo1.attach(9); // turn on servo
  delay(500);
}

void forwardd(int Speed) {
  motor1.setSpeed(Speed);
  motor1.run(FORWARD);
  motor2.setSpeed(Speed);
  motor2.run(FORWARD);
  motor3.setSpeed(Speed);
  motor3.run(FORWARD);
  motor4.setSpeed(Speed);
  motor4.run(FORWARD);
  delay(1500);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);

}

void backwardd(int Speed) {
  motor1.setSpeed(Speed);
  motor1.run(BACKWARD);
  motor2.setSpeed(Speed);
  motor2.run(BACKWARD);
  motor3.setSpeed(Speed);
  motor3.run(BACKWARD);
  motor4.setSpeed(Speed);
  motor4.run(BACKWARD);
  delay(1500);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
void leftt(int Speed) {
  servo1.write(180);
  delay(500);
  servo1.write(90);
  delay(500);
  motor1.setSpeed(Speed);
  motor1.run(FORWARD);
  motor2.setSpeed(Speed);
  motor2.run(BACKWARD);
  motor3.setSpeed(Speed);
  motor3.run(FORWARD);
  motor4.setSpeed(Speed);
  motor4.run(BACKWARD);
  delay(500);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void rightt(int Speed) {
  servo1.write(0);
  delay(500);
  servo1.write(90);
  delay(500);
  motor1.setSpeed(Speed);
  motor1.run(BACKWARD);
  motor2.setSpeed(Speed);
  motor2.run(FORWARD);
  motor3.setSpeed(Speed);
  motor3.run(BACKWARD);
  motor4.setSpeed(Speed);
  motor4.run(FORWARD);
  delay(500);
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void Stopp() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}
void loop() {

  delay(10);
  while (Serial.available()) {
    voice = "";
    voice = Serial.readString();
    Serial.print(voice);
  }

  if (voice.length() > 20 ) {
    Speed = voice.toInt();
  }
  //Sets the motor speed as desired by the user
  motor1.setSpeed(Speed);
  motor2.setSpeed(Speed);
  motor3.setSpeed(Speed);
  motor4.setSpeed(Speed);


  //##########################  Control Command  ##############################//

  if (voice == "*move forward#") {
    forwardd(Speed);
  } else if (voice == "*move backward#") {
    backwardd(Speed);
  } else if (voice == "*turn left#") {
    leftt(Speed);
  } else if (voice == "*turn right#") {
    rightt(Speed);
  } else if (voice == "*stop#") {
    Stopp();
  }
  voice = "";
}
