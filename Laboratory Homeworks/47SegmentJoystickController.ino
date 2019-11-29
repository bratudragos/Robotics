const int pinA = 12;
const int pinB = 8;
const int pinC = 5;
const int pinD = 3;
const int pinE = 2;
const int pinF = 11;
const int pinG = 6;
const int pinDP = 4;
const int pinD1 = 7;
const int pinD2 = 9;
const int pinD3 = 10;
const int pinD4 = 13;

const int segSize = 8;

const int noOfDisplays = 4;
const int noOfDigits = 10;

const int pinSwitchButton = 14;
const int pinXAxis = A1;
const int pinYAxis = A2;

int dpState = LOW;

int digit = 0;
int previousSwitchValue;
int switchValue;
int xValue;
int yValue;
int numberToShow = 0;

int currentNumber = 0;
unsigned long delayCounting = 50; // incrementing interval
unsigned long lastIncreasing = 0;

// segments array, similar to before
int segments[segSize] = {
    pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};
// digits array, to switch between them easily
int digits[noOfDisplays] = {
    pinD1, pinD2, pinD3, pinD4
};

byte digitMatrix[noOfDigits][segSize - 1] = {
    // a  b  c  d  e  f  g
    { 1, 1, 1, 1, 1, 1, 0 }, // 0
    { 0, 1, 1, 0, 0, 0, 0 }, // 1
    { 1, 1, 0, 1, 1, 0, 1 }, // 2
    { 1, 1, 1, 1, 0, 0, 1 }, // 3
    { 0, 1, 1, 0, 0, 1, 1 }, // 4
    { 1, 0, 1, 1, 0, 1, 1 }, // 5
    { 1, 0, 1, 1, 1, 1, 1 }, // 6
    { 1, 1, 1, 0, 0, 0, 0 }, // 7
    { 1, 1, 1, 1, 1, 1, 1 }, // 8
    { 1, 1, 1, 1, 0, 1, 1 } // 9
};

int numbers[noOfDisplays] = {
    0, 0, 0, 1
};

void displayNumber(byte digit, byte decimalPoint)
{
    for (int i = 0; i < segSize - 1; i++) {
        digitalWrite(segments[i], digitMatrix[digit][i]);
    }
    digitalWrite(segments[segSize - 1], decimalPoint);
}

// activate the display no. received as param
void showDigit(int num)
{
    for (int i = 0; i < noOfDisplays; i++) {
        digitalWrite(digits[i], HIGH);
    }
    digitalWrite(digits[num], LOW);
}

void setup()
{
    pinMode(pinSwitchButton, INPUT_PULLUP);
    pinMode(pinXAxis, INPUT);
    pinMode(pinYAxis, INPUT);
    for (int i = 0; i < segSize - 1; i++) {
        pinMode(segments[i], OUTPUT);
    }
    for (int i = 0; i < noOfDisplays; i++) {
        pinMode(digits[i], OUTPUT);
    }
    Serial.begin(9600);
}
void loop()
{
    previousSwitchValue = switchValue;
    switchValue = digitalRead(pinSwitchButton);
    if (previousSwitchValue == 1 && switchValue == 0) {
        while (switchValue == 0) {
            previousSwitchValue = switchValue;
            switchValue = digitalRead(pinSwitchButton);
        }
        while (switchValue == 1) {
            previousSwitchValue = switchValue;
            switchValue = digitalRead(pinSwitchButton);
            yValue = analogRead(pinYAxis);
            if (yValue < 400) {
                while (yValue < 400) {
                    yValue = analogRead(pinYAxis);
                }
                if (digit == 0)
                    digit = 3;
                else
                    digit--;
            }
            if (yValue > 550) {
                while (yValue > 550) {
                    yValue = analogRead(pinYAxis);
                }
                if (digit == 3)
                    digit = 0;
                else
                    digit++;
            }
            showDigit(digit);
            displayNumber(numbers[digit], HIGH);
        }
        numberToShow = numbers[digit];
        while (switchValue == 0) {
            previousSwitchValue = switchValue;
            switchValue = digitalRead(pinSwitchButton);
        }
        while (switchValue == 1) {
            switchValue = digitalRead(pinSwitchButton);
            xValue = analogRead(pinXAxis);
            if (xValue < 400) {
                while (xValue < 400) {
                    xValue = analogRead(pinXAxis);
                    for (int i = 0; i < 4; i++) {
                        displayNumber(numbers[i], LOW);
                        showDigit(i);
                        delay(5);
                    }
                }
                if (numberToShow == 9)
                    numberToShow = 0;
                else
                    numberToShow++;
            }
            if (xValue > 550) {
                while (xValue > 550) {
                    xValue = analogRead(pinXAxis);
                }
                if (numberToShow == 0)
                    numberToShow = 9;
                else
                    numberToShow--;
            }
            numbers[digit] = numberToShow;
            for (int i = 0; i < 4; i++) {
                displayNumber(numbers[i], LOW);
                showDigit(i);
                delay(5);
            }
        }
    }
    for (int i = 0; i < 4; i++) {
        displayNumber(numbers[i], LOW);
        showDigit(i);
        delay(5);
    }
}
