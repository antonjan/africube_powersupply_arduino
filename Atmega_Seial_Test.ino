
void setup() {
  // Start both serial communications
  Serial.begin(9600);  // For debug messages

}

void loop() {

  // Send a message over Software Serial
  Serial.println("Hello World");
  delay(1000);
}
