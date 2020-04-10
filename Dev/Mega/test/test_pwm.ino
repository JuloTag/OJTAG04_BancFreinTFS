const int pwmPin =  12;

void setup() {

  Serial.begin(9600);  // init. serial
  pinMode(pwmPin, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {

  int sensorValue = analogRead(A0);
  analogWrite(pwmPin, sensorValue/4); // valeur max du pwm de 255
  float voltage = sensorValue * (5.0 / 1023.0);
  Serial.println(sensorValue);
  Serial.println(voltage);
  delay(100);
}
