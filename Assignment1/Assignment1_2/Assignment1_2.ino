const int ldrPin = A0;  // LDR connected to analog pin A0
const int ledPin = 13;  // LED connected to digital pin 13

void setup() {
  pinMode(ledPin, OUTPUT); // Set LED pin as output
  Serial.begin(9600); // Start serial communication for debugging
}

void loop() {
  int lightLevel = analogRead(ldrPin); // Read the value from the LDR
  
  Serial.print("Light Level: ");
  Serial.println(lightLevel); // Print the light level to Serial Monitor for debugging
  
  if (lightLevel > 900) { // You may need to adjust this threshold based on your ambient light conditions
    digitalWrite(ledPin, HIGH); // Turn on the LED
  } else {
    digitalWrite(ledPin, LOW); // Turn off the LED
  }
  
  delay(100); // Delay for stability
}