int ledPin;
int reqdPattern;

void ledPattern1();
void ledPattern2();
void ledPattern3();
void ledPattern4();

void setup() {
  Serial.begin(9600);

  for(ledPin = 2; ledPin < 6; ledPin++){
    pinMode(ledPin, OUTPUT);
  }
  Serial.println("Enter the pattern number(1,2,3,4)");
}
void ledPattern1(){

  for (ledPin = 2; ledPin < 6; ledPin++){
    digitalWrite(ledPin,HIGH);
    delay(1000);
  }
  for (ledPin = 2; ledPin < 6; ledPin++){
    digitalWrite(ledPin,LOW);
    delay(1000);
  }
}
void ledPattern2(){

  for (ledPin = 2; ledPin < 6; ledPin++){
    digitalWrite(ledPin,HIGH);
    delay(1000);
    digitalWrite(ledPin,LOW);
    delay(1000);
  }
}
void ledPattern3(){

  for (ledPin = 5; ledPin > 0; ledPin--){
    digitalWrite(ledPin,HIGH);
    delay(1000);
  }
  for (ledPin = 5; ledPin > 0; ledPin--){
    digitalWrite(ledPin,LOW);
    delay(1000);
  }
}
void ledPattern4(){

  for (ledPin = 1; ledPin < 6; ledPin=ledPin + 2){
    digitalWrite(ledPin,HIGH);
    delay(1000);
  }
  for (ledPin = 2; ledPin < 6; ledPin=ledPin + 2){
    digitalWrite(ledPin,HIGH);
    delay(1000);
  }
  for (ledPin = 1; ledPin < 6; ledPin=ledPin + 2){
    digitalWrite(ledPin,LOW);
    delay(1000);
  }
  for (ledPin = 2; ledPin < 6; ledPin=ledPin + 2){
    digitalWrite(ledPin,LOW);
    delay(1000);
  }
}
 

void loop() {
  if (Serial.available() > 0){
    int reqdPattern = Serial.parseInt();
    if (reqdPattern == 1)
      ledPattern1 ();
    else if (reqdPattern == 2)
      ledPattern2 ();
    else if (reqdPattern == 3)
      ledPattern3 ();
    else if (reqdPattern == 4)
      ledPattern4 ();
    else
      Serial.println("Invalid Pattern");




  }
  

}
