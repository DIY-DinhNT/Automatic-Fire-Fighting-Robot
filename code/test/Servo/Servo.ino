#include <Servo.h>

Servo servo;
int angle = 100; // servo center
#define ServoPin  A4    // define Servo control pin connection
int k = 1;

void setup() {
  servo.attach(ServoPin);
  servo.write(angle);
  Serial.begin(9600);
}


void loop()
{
  //  delay(5000);
  // // scan from 0 to 180 degrees
  //  for(angle = 10; angle < 180; angle++)
  //  {
  //    servo.write(angle);
  //    delay(15);
  //  }
  //  // now scan back from 180 to 0 degrees
  //  for(angle = 180; angle > 10; angle--)
  //  {
  //    servo.write(angle);
  //    delay(15);
  //  }

  // scan from 0 to 180 degrees
  delay(4000);
  if (k == 1) {
    Serial.println("trai");
    for (angle = 100; angle < 160; angle++)
    {
      servo.write(angle);
      delay(15);
    }
    k = 2;
  }
  delay(3000);
  if (k == 2) {
    Serial.println("phai");
    for (angle = 100; angle > 40; angle--)
    {
      servo.write(angle);
      delay(15);
    }
    k = 3;
  }
  delay(3000);
  if (k == 3) {
    for (int i = 0 ; i < 3; i++) {
      Serial.println("2 ben");
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
    k = 0;
  }



  // now scan back from 180 to 0 degrees
  //  for (angle = 180; angle > 10; angle--)
  //  {
  //    servo.write(angle);
  //    delay(15);
  //  }
}
