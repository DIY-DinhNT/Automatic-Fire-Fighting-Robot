#include <Servo.h>

// define SRF-04 sensor
const unsigned int TRIG_PIN = 13;
const unsigned int ECHO_PIN = 12;

// define servo
#define ServoPin  A4    // define Servo control pin connection
int angle = 100; // servo center
Servo servo;
int k = 1;

int pinRelay = 2;
int pinLed = 3;
int distanceCM = 0;

// define motor
#define enA 10//Enable1 L298 Pin enA 
#define in1 9 //Motor1  L298 Pin in1 
#define in2 8 //Motor1  L298 Pin in2 
#define in3 7 //Motor2  L298 Pin in3 
#define in4 6 //Motor2  L298 Pin in4 
#define enB 5 //Enable2 L298 Pin enB 
int Speed = 130; // Write The Duty Cycle 0 to 255 Enable for Motor Speed

// define flame sensor
#define ir_R A0
#define ir_C A1
#define ir_L A2
int sensor_flame1, sensor_flame2, sensor_flame3;
bool isFire_R = false;
bool isFire_C = false;
bool isFire_L = false;

void setup()
{
  Serial.begin(9600);
  closePump();
  offLed();

  pinMode(ServoPin, OUTPUT);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(pinRelay, OUTPUT);
  pinMode(pinLed, OUTPUT);
  pinMode(ir_R, INPUT);
  pinMode(ir_C, INPUT);
  pinMode(ir_L, INPUT);

  initServo();
  initMotorDriver();
  forward();
  delay(1000);
  Stop();
}

void loop() {
  sensor_flame1 = analogRead(ir_R);
  sensor_flame2 = analogRead(ir_C);
  sensor_flame3 = analogRead(ir_L);
  Serial.println("==========================================");
  Serial.println(sensor_flame1);
  Serial.println(sensor_flame2);
  Serial.println(sensor_flame3);
  Serial.println("==========================================");
  delay(10);
  distanceCM = getDistance();

  //  if (distanceCM < 10) {
  //    turnLeft();
  //    offLed();
  //  }
  //  if ((distanceCM > 10) && (distanceCM < 20)) {
  //    Stop();
  //    onLed();
  //  }
  //  if (distanceCM > 20) {
  //    Stop();
  //    notification(true);
  //    delay(20);
  //  }

  if (sensor_flame1 <= 600) {
    Serial.println("case sensoee11");
    Stop();
    openPump();
    servoTurnRight();
    notification(true);
    isFire_R = true;
  }
  //  else if (sensor_flame1 > 600) {
  //    Serial.println("case sensoee12");
  //    closePump();
  //    offLed();
  //  }
  else if ((sensor_flame2 < 890)) {
    Serial.println("case sensoee22");
    Stop();
    openPump();
    servo2Direction();
  }
  else if (sensor_flame2 > 981) {
    Stop();
    closePump();
  }
  else if (sensor_flame3 < 600) {
    Serial.println("case sensoee3");
    Stop();
    openPump();
    servoTurnLeft();
    notification(true);
  }
  //  else if (sensor_flame1 >= 801 && sensor_flame1 <= 1020) {
  //    closePump();
  //    backward();
  //    delay(100);
  //    turnRight();
  //    delay(200);
  //  }
  //
  else if ((sensor_flame2 >= 891) && (sensor_flame2 <= 980)) {
    Serial.println("case sensoee2");
    closePump();
    forward();
  }
  //
  //  else if (sensor_flame3 >= 251 && sensor_flame3 <= 700) {
  //    closePump();
  //    backward();
  //    delay(100);
  //    turnLeft();
  //    delay(200);
  //  }
  //  if (isFire_R == false ) {
  //    closePump();
  //    Stop();
  //    offLed();
  //  }
  /* if (k ==1) {
     if ( k ==1 ) {
       servoTurnRight();
       openPump();
       k =2;
     }
     delay(4000);
     if ( k == 2) {
       servo2Direction();
       k = 3;
       closePump();
     }
     delay(4000);
     if ( k == 3) {
       servoTurnLeft();
       k = 0;
     }
    } */

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

void backward() { //backward
  Serial.println("forward");
  digitalWrite(in1, HIGH); //Right Motor forward Pin
  digitalWrite(in2, LOW);  //Right Motor backward Pin
  digitalWrite(in3, LOW);  //Left Motor backward Pin
  digitalWrite(in4, HIGH); //Left Motor forward Pin
}

void forward() { //forward
  Serial.println("backward");
  digitalWrite(in1, LOW);  //Right Motor forward Pin
  digitalWrite(in2, HIGH); //Right Motor backward Pin
  digitalWrite(in3, HIGH); //Left Motor backward Pin
  digitalWrite(in4, LOW);  //Left Motor forward Pin
}

void turnRight() { //turnRight
  Serial.println("turnRight");
  digitalWrite(in1, LOW);  //Right Motor forward Pin
  digitalWrite(in2, HIGH); //Right Motor backward Pin
  digitalWrite(in3, LOW);  //Left Motor backward Pin
  digitalWrite(in4, HIGH); //Left Motor forward Pin
}

void turnLeft() { //turnLeft
  Serial.println("turnLeft");
  digitalWrite(in1, HIGH); //Right Motor forward Pin
  digitalWrite(in2, LOW);  //Right Motor backward Pin
  digitalWrite(in3, HIGH); //Left Motor backward Pin
  digitalWrite(in4, LOW);  //Left Motor forward Pin
}

void Stop() { //stop
  Serial.println("stop");
  digitalWrite(in1, LOW); //Right Motor forward Pin
  digitalWrite(in2, LOW); //Right Motor backward Pin
  digitalWrite(in3, LOW); //Left Motor backward Pin
  digitalWrite(in4, LOW); //Left Motor forward Pin
}
/* ---------------------------------------------------- */

/* Code for Servo */
void initServo() {
  for (int angle = 90; angle <= 140; angle += 5)  {
    servoPulse(ServoPin, angle);
  }
  for (int angle = 140; angle >= 40; angle -= 5)  {
    servoPulse(ServoPin, angle);
  }

  for (int angle = 40; angle <= 95; angle += 5)  {
    servoPulse(ServoPin, angle);
  }
}

void servoCenter() {
  servo.write(100);
  delay(50);
}

void servoTurnLeft() {
  for (int angle = 90; angle >= 40; angle -= 3) {
    servoPulse(ServoPin, angle);
  }

  for (int angle = 40; angle <= 90; angle += 3) {
    servoPulse(ServoPin, angle);
  }
}

void servo2Direction() {
  for (int angle = 90; angle <= 140; angle += 3) {
    servoPulse(ServoPin, angle);
  }

  for (int angle = 140; angle >= 40; angle -= 3) {
    servoPulse(ServoPin, angle);
  }

  for (int angle = 40; angle <= 90; angle += 3) {
    servoPulse(ServoPin, angle);
  }
}

void servoTurnRight() {
  for (int angle = 90; angle <= 140; angle += 3) {
    servoPulse(ServoPin, angle);
  }

  for (int angle = 140; angle >= 90; angle -= 3) {
    servoPulse(ServoPin, angle);
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

void notification(bool hasNotifi)
{
  if (hasNotifi == true)
  {
    onLed();
    delay(20);
    offLed();
    delay(20);
  }
  else
  {
    offLed();
  }
}
