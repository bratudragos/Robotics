int writeRedPin = 11;
int writeBluePin = 9;
int writeGreenPin = 10;
int readRedPin = A2;
int readGreenPin = A1;
int readBluePin = A0;
int redValue;
int greenValue;
int blueValue;

void setup() {}

void loop() {
  redValue = analogRead(readRedPin);
  greenValue = analogRead(readGreenPin);
  blueValue = analogRead(readBluePin);

  redValue = map(redValue, 0, 1023, 0, 255);
  greenValue = map(greenValue, 0, 1023, 0, 255);
  blueValue = map(blueValue, 0, 1023, 0, 255);

  setColor(redValue, greenValue, blueValue);
}

void setColor(int redValue, int greenValue, int blueValue) {
  analogWrite(writeRedPin, redValue);
  analogWrite(writeGreenPin, greenValue);
  analogWrite(writeBluePin, blueValue);
}
