#include <Servo.h>

const unsigned int TRIG_PIN = 13;
const unsigned int ECHO_PIN = 12;

//#define servo A4
#define ServoPin  A4    // define Servo control pin connection
int angle = 100; // servo center
Servo servo;
int k = 1;

int pinRelay = 2;
int pinLed = 3;
int distanceCM = 0;

#define enA 10//Enable1 L298 Pin enA 
#define in1 9 //Motor1  L298 Pin in1 
#define in2 8 //Motor1  L298 Pin in2 
#define in3 7 //Motor2  L298 Pin in3 
#define in4 6 //Motor2  L298 Pin in4 
#define enB 5 //Enable2 L298 Pin enB 
int Speed = 160; // Write The Duty Cycle 0 to 255 Enable for Motor Speed

#define ir_R A0
int s1, s2, s3;

void setup()
{
  Serial.begin(9600); // start serial communication at 9600bps
  closePump();

  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(pinRelay, OUTPUT);
  pinMode(pinLed, OUTPUT);
  pinMode(ir_R, INPUT);// declare fire sensor pin as input
  initMotorDriver();
  initServo();
  offLed();
  delay(1000);
}

void loop() {
  s1 = analogRead(ir_R);
  Serial.println("==========================================");
  Serial.println(s1);
  Serial.println("==========================================");
  delay(1000);
  Serial.println(getDistance());
  distanceCM = getDistance();

  if (distanceCM < 10) {
    forword();
  }
  onLed();
  delay(1000);
  offLed();
  delay(1000);

  if ((distanceCM > 10) && (distanceCM > 20)) {

    Stop();
  }

  if (k == 1) {
    delay(5000);
    if ( k == 1) {
      servoTurnRight();
      k = 2;
      openPump();
    }
    delay(5000);
    if ( k == 2) {
      servo2Direction();
      k = 3;
      closePump();
    }
    delay(5000);
    if ( k == 3) {
      servoTurnLeft();
      k = 0;
    }
  }

}
/* Code for Motor driver */
void initMotorDriver()
{
  pinMode(enA, OUTPUT); // declare as output for L298 Pin enA
  pinMode(in1, OUTPUT); // declare as output for L298 Pin in1
  pinMode(in2, OUTPUT); // declare as output for L298 Pin in2
  pinMode(in3, OUTPUT); // declare as output for L298 Pin in3
  pinMode(in4, OUTPUT); // declare as output for L298 Pin in4
  pinMode(enB, OUTPUT); // declare as output for L298 Pin enB

  analogWrite(enA, Speed); // Write The Duty Cycle 0 to 255 Enable Pin A for Motor1 Speed
  analogWrite(enB, Speed); // Write The Duty Cycle 0 to 255 Enable Pin B for Motor2 Speed
}

void forword() { //forword
  Serial.println("forword");
  digitalWrite(in1, HIGH); //Right Motor forword Pin
  digitalWrite(in2, LOW);  //Right Motor backword Pin
  digitalWrite(in3, LOW);  //Left Motor backword Pin
  digitalWrite(in4, HIGH); //Left Motor forword Pin
}

void backword() { //backword
  Serial.println("backword");
  digitalWrite(in1, LOW);  //Right Motor forword Pin
  digitalWrite(in2, HIGH); //Right Motor backword Pin
  digitalWrite(in3, HIGH); //Left Motor backword Pin
  digitalWrite(in4, LOW);  //Left Motor forword Pin
}

void turnRight() { //turnRight
  Serial.println("turnRight");
  digitalWrite(in1, LOW);  //Right Motor forword Pin
  digitalWrite(in2, HIGH); //Right Motor backword Pin
  digitalWrite(in3, LOW);  //Left Motor backword Pin
  digitalWrite(in4, HIGH); //Left Motor forword Pin
}

void turnLeft() { //turnLeft
  Serial.println("turnLeft");
  digitalWrite(in1, HIGH); //Right Motor forword Pin
  digitalWrite(in2, LOW);  //Right Motor backword Pin
  digitalWrite(in3, HIGH); //Left Motor backword Pin
  digitalWrite(in4, LOW);  //Left Motor forword Pin
}

void Stop() { //stop
  Serial.println("stop");
  digitalWrite(in1, LOW); //Right Motor forword Pin
  digitalWrite(in2, LOW); //Right Motor backword Pin
  digitalWrite(in3, LOW); //Left Motor backword Pin
  digitalWrite(in4, LOW); //Left Motor forword Pin
}
/* ---------------------------------------------------- */

/* Code for Servo */
void initServo() {
  pinMode(ServoPin, OUTPUT);
  servo.attach(ServoPin);
  servo.write(angle);

  //  for (int angle = 90; angle <= 140; angle += 5)  {
  //    servoPulse(servo, angle);
  //  }
  //  for (int angle = 140; angle >= 40; angle -= 5)  {
  //    servoPulse(servo, angle);
  //  }
  //
  //  for (int angle = 40; angle <= 95; angle += 5)  {
  //    servoPulse(servo, angle);
  //  }
}

void servoTurnRight() {
  //  for (int angle = 90; angle >= 40; angle -= 3) {
  //    servoPulse(servo, angle);
  //  }
  //  for (int angle = 40; angle <= 90; angle += 3) {
  //    servoPulse(servo, angle);
  //  }
  for (angle = 100; angle > 40; angle--)
  {
    servo.write(angle);
    delay(15);
  }
}

void servo2Direction() {
  //  for (int angle = 90; angle <= 140; angle += 3) {
  //    servoPulse(servo, angle);
  //  }
  //
  //  for (int angle = 140; angle >= 40; angle -= 3) {
  //    servoPulse(servo, angle);
  //  }
  //
  //  for (int angle = 40; angle <= 90; angle += 3) {
  //    servoPulse(servo, angle);
  //  }
  servo.write(100);
  for (angle = 100; angle < 160; angle++)
  {
    servo.write(angle);
    delay(15);
  }
  servo.write(100);
  // now scan back from 180 to 0 degrees
  for (angle = 100; angle > 40; angle--)
  {
    servo.write(angle);
    delay(15);
  }
  servo.write(100);
}

void servoTurnLeft() {
  for (angle = 100; angle < 160; angle++)
  {
    servo.write(angle);
    delay(15);
  }
}

void servoPulse (int pin, int angle) {
  int pwm = (angle * 11) + 500;    // Convert angle to microseconds
  digitalWrite(pin, HIGH);
  delayMicroseconds(pwm);
  digitalWrite(pin, LOW);
  delay(50);                   // Refresh cycle of servo
}
/* ---------------------------------------------------- */

/* Code for Pump */
void openPump() {
  digitalWrite(pinRelay, LOW);
}

void closePump() {
  digitalWrite(pinRelay, HIGH);
}
/* ---------------------------------------------------- */

/* Code for SRF-05 */
int getDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);


  const unsigned long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration / 29 / 2;
  if (duration == 0) {
    Serial.println("Warning: no pulse from sensor");
  }
  //  else {
  //    Serial.print("distance to nearest object:");
  //    Serial.println(distance);
  //    Serial.println(" cm");
  //  }
  return distance;
}
/* ---------------------------------------------------- */
/* Code for LED */
void offLed() {
  digitalWrite(pinLed, HIGH);
}

void onLed() {
  digitalWrite(pinLed, LOW);
}
