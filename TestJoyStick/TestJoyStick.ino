void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
int sensorx = analogRead(A1);
int sensory = analogRead(A2);
Serial.println(sensorx);
Serial.println(sensory);
delay(500);
}
