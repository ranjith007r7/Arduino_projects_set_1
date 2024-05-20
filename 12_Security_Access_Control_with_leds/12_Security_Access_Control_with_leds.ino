#include <Keypad.h>

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

const String keyCode = "1234";
String keyCodeBuffer = "";

int buzzerPin = 12;
int redPin = 10;   // Red pin of RGB LED
int bluePin = 11;   // Blue pin of RGB LED

void setup() {
  Serial.begin(9600);
  Serial.println("Enter the passcode using the keypad and press '#' to submit");
  Serial.println("Only Numeric keys are allowed");

  pinMode(buzzerPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Turn off the RGB LED initially
  digitalWrite(redPin, LOW);
  //digitalWrite(greenPin, LOW);
  digitalWrite(bluePin, LOW);
  
}

void loop() {
  char key = kpd.getKey();
  if (key != 0) {
    if (key >= '0' && key <= '9') {
      keyCodeBuffer += key;
    } else if (key == '#') {
      if (keyCode == keyCodeBuffer) {
        Serial.println("Passcode is correct");
        // Glow blue light
        digitalWrite(redPin, LOW);
       // digitalWrite(greenPin, LOW);
        digitalWrite(bluePin, HIGH);
      } else {
        digitalWrite(buzzerPin, HIGH);
        Serial.println("Passcode is incorrect");
        // Glow red light
        digitalWrite(redPin, HIGH);
        //digitalWrite(greenPin, LOW);
        digitalWrite(bluePin, LOW);
        delay(2000);
        digitalWrite(buzzerPin, LOW);
        // Turn off the RGB LED after 2 seconds
        digitalWrite(redPin, LOW);
      }
      keyCodeBuffer = "";
    } else {
      Serial.println("Invalid Key");
    }
  }
  delay(10);
}
