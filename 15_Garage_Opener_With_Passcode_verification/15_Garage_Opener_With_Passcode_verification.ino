#include <Wire.h>
#include <NewPing.h>
#include <AccelStepper.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

int buzzerPin = 2;
int redPin = 10;   // Red pin of RGB LED
int bluePin = 11;  // Blue pin of RGB LED
AccelStepper stepper(8, 10, 12, 11, 13);

LiquidCrystal_I2C lcd(0x20, 4,5,6,0,1,2,3,7,NEGATIVE);
NewPing sonar(7,8,250);

int distance = 0;
int threshold = 50;
bool closeState = true;
bool openState = false;
bool passcodeEntered = false;

const String keyCode = "1234";
String keyCodeBuffer = "";

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};

Keypad kpd = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup() {
  lcd.begin(16,2);
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("Garage Door Opener");
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);
  Serial.println("Garage Door Opener");
  stepper.setMaxSpeed(1000.0);
  stepper.setSpeed(200);
  stepper.setAcceleration(100.0);
}

void loop() {
  distance = sonar.ping_cm();

  if (!passcodeEntered) {
    lcd.clear();
    lcd.print("Enter Passcode");
    delay(100); // Added delay to avoid rapid LCD updates
  }

  if (distance > threshold) {
    if (!closeState) {
      stepper.moveTo(-1000);
      digitalWrite(buzzerPin,HIGH);
      delay(2000);
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Goodbye");
      stepper.runToPosition();
      closeState = true;
    } else {
      lcd.backlight();
      lcd.setCursor(1,0);
      digitalWrite(buzzerPin,LOW);
      stepper.moveTo(1000);
      lcd.clear();
      lcd.print("No objects");
      stepper.runToPosition();
      openState = false;
    }
  } else if (distance <= threshold) {
    if (!openState && passcodeEntered) {
      moveStepper();
    }
  }

  char key = kpd.getKey();
  if (!passcodeEntered && key != 0) {
    if (key >= '0' && key <= '9') {
      keyCodeBuffer += key;
    } else if (key == '#') {
      if (keyCode == keyCodeBuffer) {
        Serial.println("Passcode is correct");
        lcd.clear();
        lcd.print("Access Granted");
        // Glow blue light for correct passcode
        digitalWrite(bluePin, HIGH);
        // Double beep sound
        doubleBeep();
        delay(2000); // Keep blue light on for 2 seconds
        digitalWrite(bluePin, LOW);
        passcodeEntered = true;
      } else {
        digitalWrite(buzzerPin, HIGH);
        Serial.println("Passcode is incorrect");
        lcd.clear();
        lcd.print("Access Denied");
        // Glow red light for incorrect passcode
        digitalWrite(redPin, HIGH);
        delay(2000); // Keep red light on for 2 seconds
        digitalWrite(redPin, LOW);
        digitalWrite(buzzerPin, LOW);
      }
      keyCodeBuffer = "";
    } else {
      Serial.println("Invalid Key");
    }
  }

  delay(10);
}

void doubleBeep() {
  // Beep twice with a short delay between
  digitalWrite(buzzerPin, HIGH);
  delay(200);
  digitalWrite(buzzerPin, LOW);
  delay(200);
  digitalWrite(buzzerPin, HIGH);
  delay(200);
  digitalWrite(buzzerPin, LOW);
}

void moveStepper() {
  stepper.moveTo(1000); // Move the stepper motor
  stepper.runToPosition();
}
