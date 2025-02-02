const int ldrPin = A0;      // LDR connected to analog pin A0
const int ledPin = 3;       // LED connected to digital pin 3
const int buttonPin = 2;    // Button connected to digital pin 2
int currentState = LOW;     // Current state of the button
int previousState = LOW;    // Previous state of the button
bool lightIntensityIncrease = false; // Flag to indicate LED intensity increase

void setup() {
  pinMode(ledPin, OUTPUT);   // Set LED pin as output
  pinMode(buttonPin, INPUT_PULLUP); // Set button pin as input with internal pull-up resistor
  Serial.begin(9600);        // Start serial communication for debugging
}

void loop() {
  currentState = digitalRead(buttonPin); // Read the state of the button

  Serial.println(currentState);
  
  if (currentState != previousState) {   // If the button state has changed
    if (currentState == LOW) {           // If the button is pressed
      lightIntensityIncrease = !lightIntensityIncrease; // Toggle the flag
      Serial.print("Button pressed. LED intensity ");
      Serial.println(lightIntensityIncrease ? "increasing" : "decreasing");
    }
    delay(50); // Debouncing delay
  }
  previousState = currentState; // Save the current state as the previous state for next iteration
  
  int lightLevel = analogRead(ldrPin); // Read the value from the LDR
  
  Serial.print("Light Level: ");
  Serial.println(lightLevel); // Print the light level to Serial Monitor for debugging
  
  int brightness;
  if (lightIntensityIncrease) {
    brightness = map(lightLevel, 860, 1000, 0, 255); // Map LDR values to LED brightness range
  } else {
    brightness = map(lightLevel, 860, 1000, 255, 0); // Map LDR values to LED brightness range (inverse for decrease)
  }
  
  analogWrite(ledPin, brightness); // Set LED brightness using PWM
  
  delay(100); // Delay for stability
}
