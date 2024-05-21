#define servo A4

int k = 1;

void setup() {
  pinMode(servo, OUTPUT);
  Serial.begin(9600); // start serial communication at 9600bps

  for (int angle = 90; angle <= 140; angle += 5)  {
    servoPulse(servo, angle);
  }
  for (int angle = 140; angle >= 40; angle -= 5)  {
    servoPulse(servo, angle);
  }

  for (int angle = 40; angle <= 95; angle += 5)  {
    servoPulse(servo, angle);
  }
  delay(5000);
}


void loop() {
  /* huong theo chieu day dien */
  delay(1000);
  // ben phai
  if ( k == 1) {
    for (int angle = 90; angle >= 40; angle -= 3) {
      servoPulse(servo, angle);
    }
    for (int angle = 40; angle <= 90; angle += 3) {
      servoPulse(servo, angle);
    }
    k = 2;
  }
  delay(3000);
  // 2 ben
  if (k == 2) {
    for (int angle = 90; angle <= 140; angle += 3) {
      servoPulse(servo, angle);
    }

    for (int angle = 140; angle >= 40; angle -= 3) {
      servoPulse(servo, angle);
    }

    for (int angle = 40; angle <= 90; angle += 3) {
      servoPulse(servo, angle);
    }
    k = 3;
  }
  delay(3000);
  // ben trai
  if (k == 3) {
    for (int angle = 90; angle <= 140; angle += 3) {
      servoPulse(servo, angle);
    }

    for (int angle = 140; angle >= 90; angle -= 3) {
      servoPulse(servo, angle);
    }
    k = 0;
  }
}

void servoPulse (int pin, int angle) {
  int pwm = (angle * 11) + 500;    // Convert angle to microseconds
  Serial.println(pwm);
  digitalWrite(pin, HIGH);
  delayMicroseconds(pwm);
  digitalWrite(pin, LOW);
  delay(50);                   // Refresh cycle of servo
}
