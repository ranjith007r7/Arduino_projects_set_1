
#include<Servo.h>
#include<Keypad.h>

Servo servo;
int position = 90;
int value;

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] ={
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
  

byte rowPins[ROWS] = {2,3,4,5};
byte colPins[COLS] = {6,7,8,9};

Keypad kpd = Keypad(makeKeymap(keys),rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
  servo.attach(10);
  

}

void loop() {
  char key =kpd.getKey();

  if (key != 0)
  {
    switch (key)
    {
      case '1':
        position = 0;
        break;
      case '2':
        position = 90;
        break;
      case '3':
        position = 180;
        break;
      default:
      Serial.println("Invalid key pressed");
      break;

    }
    servo.write(position);
  }
  
delay(10);
}
