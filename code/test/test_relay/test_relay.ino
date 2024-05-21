int pinRelay = 2;


void setup() {
  Serial.begin(9600);
  pinMode(pinRelay, OUTPUT);
}



void loop() {
  digitalWrite(pinRelay, LOW);
  delay(10000);
  digitalWrite(pinRelay, HIGH);
  delay(10000);
}
