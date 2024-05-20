
//code to ensure the RGB LED behaves as described. 
//The LED should show green to indicate readiness, 
//red for an incorrect passcode, and blue for a correct passcode,
//the blue LED lighting up and the buzzer sounding two beeps.
//resetting to green after each passcode entry:

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
int bluePin = 11;  // Blue pin of RGB LED

void setup() {
  Serial.begin(9600);
  Serial.println("Enter the passcode using the keypad and press '#' to submit");
  Serial.println("Only Numeric keys are allowed");

  pinMode(buzzerPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Set initial state to ready (green light)
  setReadyState();
}

void loop() {
  char key = kpd.getKey();
  if (key != 0) {
    if (key >= '0' && key <= '9') {
      keyCodeBuffer += key;
    } else if (key == '#') {
      if (keyCode == keyCodeBuffer) {
        Serial.println("Passcode is correct");
        // Glow blue light for correct passcode
        digitalWrite(redPin, LOW);
        digitalWrite(bluePin, HIGH);
        // Double beep sound
        doubleBeep();
        delay(2000); // Keep blue light on for 2 seconds
        digitalWrite(bluePin, LOW);
      } else {
        digitalWrite(buzzerPin, HIGH);
        Serial.println("Passcode is incorrect");
        // Glow red light for incorrect passcode
        digitalWrite(redPin, HIGH);
        delay(2000); // Keep red light on for 2 seconds
        digitalWrite(redPin, LOW);
        digitalWrite(buzzerPin, LOW);
      }
      keyCodeBuffer = "";
      // Reset to ready state after processing passcode
      setReadyState();
    } else {
      Serial.println("Invalid Key");
    }
  }
  delay(10);
}

void setReadyState() {
  // Ensure the RGB LED is in ready state (green light)
  digitalWrite(redPin, LOW);
  digitalWrite(bluePin, LOW);
  // Note: Assume green is on by default and can't be controlled
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
