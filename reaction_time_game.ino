// Code Written By BlueJay
#include <TM1637Display.h>

// Buttons
const byte WHITEBUTTON = 2;
const byte REDBUTTON = 3;
const byte GREENBUTTON = 4;
const byte BLUEBUTTON = 5;

// Toggles
byte whitePrevious;
byte redPrevious;
byte greenPrevious;
byte bluePrevious;

// Light Pins
const byte REDPIN = 9;
const byte GREENPIN = 10;
const byte BLUEPIN = 11;

// Buzzer
const byte BUZZER = 6;

// Score
int points = 0;

// TM1637 Display
const byte CLK_PIN = 8;
const byte DIO_PIN = 7;

TM1637Display counter = TM1637Display(CLK_PIN, DIO_PIN);

// Time
int startTime;

void displayColor(int r, int g, int b) {
  analogWrite(REDPIN, r);
  analogWrite(GREENPIN, g);
  analogWrite(BLUEPIN, b);
}

void setup() {

  pinMode(WHITEBUTTON, INPUT_PULLUP);
  pinMode(REDBUTTON, INPUT_PULLUP);
  pinMode(GREENBUTTON, INPUT_PULLUP);
  pinMode(BLUEBUTTON, INPUT_PULLUP);

  // Countdown
  displayColor(255, 0, 0);
  tone(BUZZER, 300, 200);
  delay(500);
  displayColor(0, 0, 0);
  delay(500);
  displayColor(255, 100, 0);
  tone(BUZZER, 300, 200);
  delay(500);
  displayColor(0, 0, 0);
  delay(500);
  displayColor(255, 255, 0);
  tone(BUZZER, 400, 200);
  delay(500);
  displayColor(0, 0, 0);
  delay(500);

  //Serial.begin(9600);

  counter.setBrightness(7);
  counter.clear();

  startTime = millis();
}

void loop() {
  // Generate Random Light
  randomSeed(analogRead(0));
  static int currentLight = random(4);

  // Display
  if (currentLight == 0) {
    displayColor(100, 100, 100);
  } else if (currentLight == 1) {
    displayColor(100, 0, 0);
  } else if (currentLight == 2) {
    displayColor(0, 100, 0);
  } else if (currentLight == 3) {
    displayColor(0, 0, 100);
  }

  // Button States
  bool whiteCurrent = digitalRead(WHITEBUTTON);
  bool redCurrent = digitalRead(REDBUTTON);
  bool greenCurrent = digitalRead(GREENBUTTON);
  bool blueCurrent = digitalRead(BLUEBUTTON);

  //Serial.println(points);

  if (whiteCurrent == LOW && whitePrevious == HIGH && currentLight == 0) {
    points += 1;
    currentLight = random(4);
    tone(BUZZER, 200, 200);
  }

  if (redCurrent == LOW && redPrevious == HIGH && currentLight == 1) {
    points += 1;
    currentLight = random(4);
    tone(BUZZER, 200, 200);
  }

  if (greenCurrent == LOW && greenPrevious == HIGH && currentLight == 2) {
    points += 1;
    currentLight = random(4);
    tone(BUZZER, 200, 200);
  }

  if (blueCurrent == LOW && bluePrevious == HIGH && currentLight == 3) {
    points += 1;
    currentLight = random(4);
    tone(BUZZER, 200, 200);
  }

  // Check Game Duration
  int currentTime = millis();
  int elapsedTime = currentTime - startTime;
  //Serial.println(elapsedTime);

  // Game is finished: 30 Seconds
  if (elapsedTime > 30000) {
    displayColor(0, 0, 0);
    tone(BUZZER, 350, 200);
    delay(200);
    tone(BUZZER, 350, 200);
    delay(200);
    while (true) {
      counter.clear();
      delay(300);
      counter.showNumberDec(points);
      delay(300);
    }
  }

  // Update Buttons
  whitePrevious = whiteCurrent;
  redPrevious = redCurrent;
  greenPrevious = greenCurrent;
  bluePrevious = blueCurrent;

  //Display Points
  counter.showNumberDec(points);
}
