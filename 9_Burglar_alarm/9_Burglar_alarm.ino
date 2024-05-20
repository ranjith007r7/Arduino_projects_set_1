
#include <NewPing.h>
#include <LiquidCrystal_I2C.h>

NewPing sonar(7,8,200);


int buzzerPin =10;
int pirPin =12;

const int distThresh = 250;


void setup() {

  pinMode(buzzerPin, OUTPUT);
  pinMode(pirPin, INPUT);
  lcd.begin(16,2);
  
}

void loop() {

  int dist = sonar.ping_cm();

  if (dist < distThresh || digitalRead(pirPin)){

  digitalWrite(buzzerPin, HIGH);
  lcd.home();
  lcd.print("Intruder Detected");
  delay(2000);
  }
  else {
  digitalWrite(buzzerPin, LOW);
  lcd.home();
  lcd.print("NO Intruder");


  }
  delay(10);
 

}
