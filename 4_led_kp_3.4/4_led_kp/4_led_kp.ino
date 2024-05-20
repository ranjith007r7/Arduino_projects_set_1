#include <Keypad.h>

int ledPin;

void ledPattern1();
void ledPattern2();
void ledPattern3();
void ledPattern4();

const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS] [COLS] = {

  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}};

byte rowPins[ROWS] = {2,3,4,5};
byte colPins[COLS] = {6,7,8,9};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS );

void setup() {
  Serial.begin(9600);
  for(ledPin = 10; ledPin < 14; ledPin++){
    pinMode(ledPin, OUTPUT);
  }
  Serial.println("Enter the Pattern number (1,2,3,4)");
  

}

void loop() {

  char customKey = customKeypad.getKey();
  if (customKey){
    if (customKey == '1')
      ledPattern1();
    else if (customKey == '2')
      ledPattern2();
    else if (customKey == '3')
      ledPattern3();
    else if (customKey == '4')
      ledPattern4();
    else
      Serial.println("Invalid pattern");


  }
}

void ledPattern1()
{
  for (ledPin = 2; ledPin < 14; ledPin++){
    digitalWrite(ledPin,HIGH);
    delay(1000);
 }
  for (ledPin = 10; ledPin < 14; ledPin++){
    digitalWrite(ledPin,LOW);
    delay(1000);
 }
}
void ledPattern2()
{
  for (ledPin = 10; ledPin < 14; ledPin++){
     digitalWrite(ledPin,HIGH);
     delay(1000);
     digitalWrite(ledPin,LOW);
     delay(1000);

 }
}

void ledPattern3 (){
  for (ledPin = 13; ledPin > 9; ledPin--){
     digitalWrite(ledPin,HIGH);
     delay(1000);}
     for (ledPin = 13; ledPin > 9; ledPin--){
     digitalWrite(ledPin,LOW);
     delay(1000);

 }



}
void ledPattern4 (){
  for (ledPin = 9; ledPin < 14; ledPin = ledPin + 2){
     digitalWrite(ledPin,HIGH);
     delay(1000);}
     for (ledPin = 10; ledPin < 14; ledPin = ledPin +2){
     digitalWrite(ledPin,HIGH);
     delay(1000);

 }
  for (ledPin = 9; ledPin < 14; ledPin = ledPin + 2){
     digitalWrite(ledPin,LOW);
     delay(1000);}
     for (ledPin = 10; ledPin < 14; ledPin = ledPin +2){
     digitalWrite(ledPin,LOW);
     delay(1000);

 }



}

  


