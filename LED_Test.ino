// Blink LED on Atmega328P-AU

// Define the LED pin number (
#define LED_PIN 1 //GPIO1

void setup() {
  Serial.begin(9600);
  // Initialize the LED pin as an output
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  // Turn the LED on
  digitalWrite(LED_PIN, HIGH);
  delay(500); // Wait for 1 second

  // Turn the LED off
  digitalWrite(LED_PIN, LOW);
  delay(500); // Wait for 1 second
  //Serial.println("hello World");
}
