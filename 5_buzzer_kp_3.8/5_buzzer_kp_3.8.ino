
int buzzerPin = 2;
bool prevState = false;

void setup() {
  pinMode(buzzerPin,OUTPUT);
  Serial.begin(9600);
  digitalWrite(buzzerPin, LOW);
  Serial.println("Enter the number");


  

}

void loop() {
  digitalWrite(buzzerPin , prevState);

  if (Serial.available())
  {
    String no = Serial.readString();
    Serial.println(no);
    no.trim();

  if (no.toInt() % 2 == 0)
  {
    Serial.println("Even number - Buzzer Off");
    digitalWrite(buzzerPin , LOW);
    prevState = false;

  }
   else
  {
    Serial.println("Odd number - Buzzer On");
    digitalWrite(buzzerPin , HIGH);
    prevState = true;

  }



  }
  delay(10);


}
