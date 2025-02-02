#include <Servo.h>

Servo servoMotor;  // create a servo object

int angle = 0;     // initialize the angle variable

const int ldrPin = A0;  // LDR connected to analog pin A0
const int secoPin = 9;  // LED connected to digital pin 13

void setup() {
  // pinMode(ledPin, OUTPUT); // Set LED pin as output
  Serial.begin(9600); // Start serial communication for debugging
  servoMotor.attach(servoPin);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  int lightLevel = analogRead(ldrPin); // Read the value from the LDR
  
  Serial.print("Light Level: ");
  Serial.println(lightLevel); // Print the light level to Serial Monitor for debugging
  
  if (lightLevel > 60) { // You may need to adjust this threshold based on your ambient light conditions
    // digitalWrite(ledPin, HIGH); // Turn on the LED
    for (angle = 0; angle <= 180; angle += 1) {
      // if (angle = 180) {
      //   continue;
      // }
      servoMotor.write(angle);   // tell servo to go to the specified angle
      delay(15);                 // waits 15ms for the servo to reach the position
    }
  } else {
    // digitalWrite(ledPin, LOW); // Turn off the LED
    for (angle = 180; angle >= 0; angle -= 1) {
      // if (angle = 0) {
      //   continue;
      // }
      servoMotor.write(angle);   // tell servo to go to the specified angle
      delay(15);                 // waits 15ms for the servo to reach the position
    }
  }

  Serial.print("Angle: ");
  Serial.println(angle);
  
  // delay(100); // Delay for stability
}
