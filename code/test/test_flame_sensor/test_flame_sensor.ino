// lowest and highest sensor readings:
const int sensorMin = 0;     //  sensor minimum
const int sensorMax = 1024;  // sensor maximum
//
//void setup()  {
//  // initialize serial communication @ 9600 baud:
//  Serial.begin(9600);
//}
//void loop() {
//  // read the sensor on analog A0:
//  int sensorReading  = analogRead(A1);
//  // map the sensor range (four options):
//  // ex: 'long  int map(long int, long int, long int, long int, long int)'
//  int range = map(sensorReading,  sensorMin, sensorMax, 0, 3);
//
//  // range value:
//  switch (range) {
//  case 0:    // A fire closer than 1.5 feet away.
//    Serial.println("** Close  Fire **");
//    break;
//  case 1:    // A fire between 1-3 feet away.
//    Serial.println("**  Distant Fire **");
//    break;
//  case 2:    // No fire detected.
//    Serial.println("No  Fire");
//    break;
//  }
//  delay(1);  // delay between reads
//}

//#include<SoftwareSerial.h>
//int sensorPin = A0; // select the input pin for the LDR
//int sensorValue = 0; // variable to store the value coming from the sensor
//void setup() {
//  Serial.begin(9600);
//}
//void loop()
//{
//  Serial.println("Welcome to TechPonder Flame Sensor Tutorial");
//  sensorValue = analogRead(sensorPin);
//  Serial.println(sensorValue);
//  if (sensorValue < 100)
//
//  {
//    Serial.println("Fire Detected");
//    Serial.println("LED on");
//    delay(1000);
//  }
//  Serial.println("LED off");
//  delay(sensorValue);
//}

#define ir_R A1

int s1, s2, s3;

void setup() {
  Serial.begin(9600); // start serial communication at 9600bps
  pinMode(ir_R, INPUT);// declare fire sensor pin as input
}

void loop() {
  s2 = analogRead(ir_R);
  Serial.println("==========================================");
  Serial.println(s2);
  Serial.println("==========================================");
  delay(1000);
}
