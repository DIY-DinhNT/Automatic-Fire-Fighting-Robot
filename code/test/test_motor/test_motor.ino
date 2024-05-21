

#define in1  0          // L298N in1 motors Right           GPIO15(D8)
#define in2  2          // L298N in2 motors Right           GPIO13(D7)
#define in3  13          // L298N in3 motors Left            GPIO2(D4)
#define in4  15

int Speed = 160; // Write The Duty Cycle 0 to 255 Enable for Motor Speed

void setup() { // put your setup code here, to run once

  Serial.begin(9600); // start serial communication at 9600bps

  pinMode(in1, OUTPUT); // declare as output for L298 Pin in1
  pinMode(in2, OUTPUT); // declare as output for L298 Pin in2
  pinMode(in3, OUTPUT); // declare as output for L298 Pin in3
  pinMode(in4, OUTPUT); // declare as output for L298 Pin in4

  delay(500);
}

void loop() {
  forword();
  delay(500);
  Stop();
  delay(1000);
}

void forword() { //forword
  digitalWrite(in1, LOW); //Right Motor forword Pin
  digitalWrite(in2, HIGH);  //Right Motor backword Pin
  digitalWrite(in3, LOW);  //Left Motor backword Pin
  digitalWrite(in4, HIGH); //Left Motor forword Pin
}

void backword() { //backword
  digitalWrite(in1, LOW);  //Right Motor forword Pin
  digitalWrite(in2, HIGH); //Right Motor backword Pin
  digitalWrite(in3, HIGH); //Left Motor backword Pin
  digitalWrite(in4, LOW);  //Left Motor forword Pin
}

void turnRight() { //turnRight
  digitalWrite(in1, LOW);  //Right Motor forword Pin
  digitalWrite(in2, HIGH); //Right Motor backword Pin
  digitalWrite(in3, LOW);  //Left Motor backword Pin
  digitalWrite(in4, HIGH); //Left Motor forword Pin
}

void turnLeft() { //turnLeft
  digitalWrite(in1, HIGH); //Right Motor forword Pin
  digitalWrite(in2, LOW);  //Right Motor backword Pin
  digitalWrite(in3, HIGH); //Left Motor backword Pin
  digitalWrite(in4, LOW);  //Left Motor forword Pin
}

void Stop() { //stop
  digitalWrite(in1, LOW); //Right Motor forword Pin
  digitalWrite(in2, LOW); //Right Motor backword Pin
  digitalWrite(in3, LOW); //Left Motor backword Pin
  digitalWrite(in4, LOW); //Left Motor forword Pin
}
