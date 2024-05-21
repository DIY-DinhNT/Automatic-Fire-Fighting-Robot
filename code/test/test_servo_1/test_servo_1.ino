#include <Servo.h>   // include Arduino Servo library

Servo servo;       // create servo object to control a servo

#define ServoPin  A4    // define Servo control pin connection

void setup()
{

  servo.attach( ServoPin );  // attaches Servo control pin

}


void loop()
{
  uint16_t an = 570; // center

  //  uint16_t an = 870; // left

  uint8_t angle = map(an, 0, 1023, 0, 180);   // scale previous value between 0 and 180 (angle form)

  if ( angle != servo.read() )   // check if angle changed
    servo.write(angle);          // set new servo motor angle

  delay(10);                     // waits for the servo to get there

  an = 170; // right
  map(an, 0, 1023, 0, 180);   // scale previous value between 0 and 180 (angle form)

  if ( angle != servo.read() )   // check if angle changed
    servo.write(angle);          // set new servo motor angle

  delay(10);                     // waits for the servo to get there

}
