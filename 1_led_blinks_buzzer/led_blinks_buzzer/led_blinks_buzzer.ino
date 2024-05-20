void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(2, HIGH);
  digitalWrite(4, LOW);  // turn the LED on (HIGH is the voltage level)
  delay(1000);                      // wait for a second
  digitalWrite(2, LOW);
  digitalWrite(4, HIGH);   // turn the LED off by making the voltage LOW
  delay(1000);                      // wait for a second
}
