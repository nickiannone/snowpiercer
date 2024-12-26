void setup() {
  // Initialize serial communication at 9600 bits per second
  Serial.begin(9600);
}

void loop() {
  // Print a message to the serial monitor
  Serial.println("Hello, Arduino!");
  delay(1000); // Wait for a second
}