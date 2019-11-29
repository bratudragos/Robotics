#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 7, 6, 5, 4);
//const int contrastPin=A5;
char* menuPages[] = {
    "Start Game", "HighScore", "Settings", "Game", "HighScoreMenu", "SettingsMenu"
};

byte arrDown[] = {
    B00100,
    B00100,
    B00100,
    B00100,
    B00100,
    B10101,
    B01110,
    B00100
};

byte arrUp[] = {
    B00100,
    B01110,
    B10101,
    B00100,
    B00100,
    B00100,
    B00100,
    B00100
};

const int buttonPin = 8;
const int yPin = A0;
const int xPin = A1;
int buttonValue = 0;
int lastButtonValue = 0;
int yValue = 0;
int xValue;
int menuCount = 0;
int okX = 1;
int okY = 1;
int lastMenuCount = 0;
int inMainMenu = 1;
int lives = 3;
int score = 0;
int level = 0;
int timeStarted;
int timeNow;
int okClear = 1;
int okExit = 1;
int secCount = 0;
int highScore = 0;
int defaultLevel = 0;
int lastDefaultLevel = 0;

void showMenuPage(int page)
{
    lcd.setCursor(0, 0);
    lcd.print(menuPages[page]);
}

void setup()
{
    pinMode(buttonPin, INPUT_PULLUP);
    pinMode(yPin, INPUT);
    pinMode(xPin, INPUT);
    //pinMode(contrastPin,INPUT);
    lcd.begin(16, 2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display
    //  analogWrite(contrastPin,100);
    lcd.createChar(0, arrDown);
    lcd.createChar(1, arrUp);
    Serial.begin(9600);
}
void loop()
{

    buttonValue = digitalRead(buttonPin);
    if (buttonValue != lastButtonValue && buttonValue == LOW) {
        if (inMainMenu == 1) {
            menuCount = menuCount + 3;
            lcd.clear();
        }
        inMainMenu = 0;
        timeStarted = millis();
        okClear = 1;
        level = defaultLevel;
    }

    if (inMainMenu == 1) {
        yValue = analogRead(yPin);
        if (yValue < 300) {
            if (okY == 1) {
                menuCount = menuCount + 3;
                lcd.clear();
                inMainMenu = 0;
                timeStarted = millis();
                okClear = 1;
                level = defaultLevel;
                okY = 0;
            }
        }
        if (yValue >= 505 && yValue <= 550) {
            okY = 1;
        }
    }

    lastButtonValue = buttonValue;
    if (inMainMenu == 1) {
        lcd.setCursor(15, 0);
        lcd.write(byte(1));
        lcd.setCursor(15, 1);
        lcd.write(byte(0));
        xValue = analogRead(xPin);

        if (xValue < 300) {
            if (okX == 1) {
                menuCount = menuCount + 1;
                okX = 0;
            }
        }
        if (xValue > 800) {
            if (okX == 1) {
                menuCount = menuCount - 1;
                okX = 0;
            }
        }
        if (xValue >= 505 && xValue <= 550) {
            okX = 1;
        }

        menuCount = menuCount % 3;
        if (menuCount == -1)
            menuCount = 2;
    }
    else {
        if (menuCount == 3) {
            timeNow = millis();
            if (timeNow - timeStarted < 10000) {
                okExit = 1;
                lcd.setCursor(0, 0);
                lcd.print("Lives:");
                lcd.print(lives);
                lcd.setCursor(8, 0);
                lcd.print("Level:");
                lcd.print(level);
                lcd.setCursor(0, 1);
                lcd.print("Score:");
                score = 3 * level;
                lcd.print(score);
                if ((timeNow - timeStarted) / 2000 > secCount) {
                    secCount = secCount + 1;
                    level = level + 1;
                }
            }
            else {
                if (okClear == 1) {
                    score = score + 3;
                    if (score > highScore)
                        highScore = score;
                    lcd.clear();
                    okClear == 0;
                    lcd.setCursor(0, 0);
                }
                lcd.print("Finished.Press");
                lcd.setCursor(0, 1);
                lcd.print("button to exit");
                while (okExit == 1) {
                    buttonValue = digitalRead(buttonPin);
                    if (buttonValue != lastButtonValue && buttonValue == LOW) {
                        okExit = 0;
                        menuCount = 0;
                        inMainMenu = 1;
                        lives = 3;
                        level = defaultLevel;
                        score = 0;
                    }
                    lastButtonValue = buttonValue;
                }
                secCount = 0;
            }
        }
        if (menuCount == 4) {
            lcd.setCursor(0, 0);
            lcd.print("HIGHSCORE:");
            lcd.print(highScore);
            okExit = 1;
            while (okExit == 1) {
                buttonValue = digitalRead(buttonPin);
                if (buttonValue != lastButtonValue && buttonValue == LOW) {
                    okExit = 0;
                    menuCount = 0;
                    inMainMenu = 1;
                    lives = 3;
                    level = 0;
                    score = 0;
                }
                lastButtonValue = buttonValue;
            }
        }
        if (menuCount == 5) {
            lcd.setCursor(0, 0);
            lcd.print("Starting level:");
            lcd.setCursor(0, 1);
            lcd.print(defaultLevel);
            okExit = 1;
            while (okExit == 1) {
                lastDefaultLevel = defaultLevel;
                lcd.setCursor(0, 1);
                lcd.print(defaultLevel);
                buttonValue = digitalRead(buttonPin);
                yValue = analogRead(yPin);
                if (yValue < 300) {
                    if (okY == 1) {
                        defaultLevel = defaultLevel + 1;
                        okY = 0;
                    }
                }
                if (yValue > 800) {
                    if (okY == 1) {
                        defaultLevel = defaultLevel - 1;
                        okY = 0;
                    }
                }
                if (defaultLevel != lastDefaultLevel) {
                    lcd.clear();
                    lcd.setCursor(0, 0);
                    lcd.print("Starting level:");
                    lcd.setCursor(0, 1);
                    lcd.print(defaultLevel);
                }

                if (yValue >= 505 && yValue <= 550) {
                    okY = 1;
                }

                if (buttonValue != lastButtonValue && buttonValue == LOW) {
                    okExit = 0;
                    menuCount = 0;
                    inMainMenu = 1;
                    lives = 3;
                    level = 0;
                    score = 0;
                }
                lastButtonValue = buttonValue;
            }
        }
    }
    if (lastMenuCount != menuCount) {
        lcd.clear();
    }
    //Serial.println(menuCount);
    if (inMainMenu == 1) {
        showMenuPage(menuCount);
    }
    lastMenuCount = menuCount;
}
