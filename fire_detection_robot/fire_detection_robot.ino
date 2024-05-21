// define SRF-04 sensor
const unsigned int TRIG_PIN = 13;
const unsigned int ECHO_PIN = 12;

// define servo
#define ServoPin  A4    // define Servo control pin connection
int angle = 100; // servo center

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
String FireInSide;

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
  initOK();
  Stop();
  delay(1000);
}

void loop() {
  sensor_flame1 = analogRead(ir_R);
  sensor_flame2 = analogRead(ir_C);
  sensor_flame3 = analogRead(ir_L);
  Serial.println("===================");
  Serial.println(sensor_flame1);
  Serial.println(sensor_flame2);
  Serial.println(sensor_flame3);
  Serial.println("===================");
  delay(100);
  distanceCM = getDistance();
  FireInSide = getFireSide(sensor_flame1, sensor_flame2, sensor_flame3);

  if (FireInSide == "Fire_in_Right") {
    if (sensor_flame1 < 400) {
      backward();
      openPump();
      servoTurnRight();
      notification(true, 1);
    }
    else if ((400 <= sensor_flame1) && (sensor_flame1 <= 800)) {
      Stop();
      openPump();
      servoTurnRight();
      notification(true, 1);
    }
    else if ((800 < sensor_flame1) && (sensor_flame1 <= 990)) {
      onLed();
      closePump();
      turnRight();
      if (distanceCM <= 10) {
        Stop();
      }
      else {
        forward();
      }
      offLed();
    }
    else if (sensor_flame1 > 990) {
      Stop();
      closePump();
      offLed();
    }
  }
/*
  else if (FireInSide == "Fire_in_Center") {
    if (sensor_flame2 < 875) {
      backward();
      openPump();
      servo2Direction();
      notification(true, 1);
    }
    else if ((876 <= sensor_flame2) && (sensor_flame2 <= 910)) {
      Stop();
      openPump();
      servo2Direction();
      notification(true, 1);
    }
    else if ((910 < sensor_flame2) && (sensor_flame2 <= 990)) {
      onLed();
      closePump();
      if (distanceCM <= 10) {
        Stop();
      }
      else {
        forward();
      }
      offLed();
    }
    else if (sensor_flame2 > 990) {
      Stop();
      closePump();
      offLed();
    }
  }
*/
  else if (FireInSide == "Fire_in_Left") {
    if (sensor_flame3 < 700) {
      backward();
      openPump();
      servoTurnLeft();
      notification(true, 1);
    }
    else if ((700 <= sensor_flame3) && (sensor_flame3 <= 840)) {
      Stop();
      openPump();
      servoTurnLeft();
      notification(true, 1);
    }
    else if ((840 < sensor_flame3) && (sensor_flame3 <= 990)) {
      onLed();
      closePump();
      turnLeft();
      if (distanceCM <= 10) {
        Stop();
      }
      else {
        forward();
      }
      offLed();
    }
    else if (sensor_flame3 > 990) {
      Stop();
      closePump();
      offLed();
    }
  }
  else {
    Stop();
    closePump();
    offLed();
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

void backward() { //backward
  digitalWrite(in2, LOW);  //Right Motor backward Pin
  digitalWrite(in3, LOW);  //Left Motor backward Pin
  for (int i = 100; i < 130; i++) {
    analogWrite(in1, i);
    analogWrite(in4, i);
  }
  delay(500);
  Stop();
  delay(30);
}

void forward() { //forward
  digitalWrite(in1, LOW);  //Right Motor forward Pin
  digitalWrite(in4, LOW);  //Left Motor forward Pin
  for (int i = 80; i < 130; i++) {
    analogWrite(in2, i);
    analogWrite(in3, i);
  }
  delay(500);
  Stop();
  delay(30);
}

void turnRight() { //turnRight
  digitalWrite(in1, LOW);  //Right Motor forward Pin
  analogWrite(in2, 130);
  digitalWrite(in3, LOW);  //Left Motor backward Pin
  analogWrite(in4, 130);
}

void turnLeft() { //turnLeft
  analogWrite(in1, 130);
  digitalWrite(in2, LOW);  //Right Motor backward Pin
  analogWrite(in3, 130);
  digitalWrite(in4, LOW);  //Left Motor forward Pin
}

void Stop() { //stop
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

void initOK() {
  for (int i = 0; i < 3 ; i++) {
    onLed();
    delay(200);
    offLed();
    delay(200);
  }
}

void notification(bool hasNotifi, int numberBlink)
{
  if (hasNotifi == true)
  {
    for (int i = 0; i < numberBlink ; i++) {
      onLed();
      delay(20);
      offLed();
      delay(20);
    }
  }
  else
  {
    offLed();
  }
}

int findMin(int valSen1, int valSen2, int valSen3) {
  int minVal = valSen1;
  if (valSen2 < minVal) {
    minVal = valSen2;
  }
  if (valSen3 < minVal) {
    minVal = valSen3;
  }
  return minVal;
}

String getFireSide(int valSen1, int valSen2, int valSen3) {
  int minVal = findMin(valSen1, valSen2, valSen3);
  String fireSide = "No_fire";
  if (minVal == valSen1) {
    fireSide = "Fire_in_Right";
  }
  else if (minVal == valSen2) {
    fireSide = "Fire_in_Center";
  }
  else if (minVal == valSen3) {
    fireSide = "Fire_in_Left";
  }
  else {
    fireSide = "No_fire";
  }
  return fireSide;
}
