#include <Wire.h>
#include <NewPing.h>
#include <AccelStepper.h>
#include <LiquidCrystal_I2C.h>

AccelStepper stepper(8, 10, 12, 11, 13);

LiquidCrystal_I2C lcd(0x20, 4,5,6,0,1,2,3,7,NEGATIVE);
NewPing sonar(7,8,250);

int distance = 0;
int threshold = 50;
bool closeState = true;
bool openState = false;

void setup() {

  lcd.begin(16,2);
  lcd.backlight();
  lcd.setCursor(1,0);
  lcd.print("Garage Door Opener");

  Serial.begin(9600);
  Serial.println("Garage Door Opener");
  stepper.setMaxSpeed(1000.0);
  stepper.setSpeed(200);
  stepper.setAcceleration(100.0);
  

}

void loop() {
  distance = sonar.ping_cm();

  if (distance > threshold)
  {
    if (!closeState)
    {
      stepper.moveTo(-1000);
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Goodbye");
      stepper.runToPosition();
      closeState = true;
    }
      else{
        lcd.backlight();
        lcd.setCursor(1,0);
        stepper.moveTo(1000);
        lcd.clear();
        lcd.print("No objects");
        stepper.runToPosition();
        openState = false;

      }
    
    }else if (distance <= threshold){

      if (!openState){
        stepper.moveTo(-1000);
        lcd.clear();
        lcd.print("Welcome Back");
        stepper.runToPosition();
        openState = true;


      }
      else{
      stepper.moveTo(1000);
      lcd.clear();
      lcd.setCursor(1,0);
      lcd.print("Garage Open");
      stepper.runToPosition();
      closeState = false;

      }
    }
    delay(10);
  }
  


