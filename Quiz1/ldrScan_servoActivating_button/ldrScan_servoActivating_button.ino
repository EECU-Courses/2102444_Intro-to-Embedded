#include <Servo.h>

Servo servoMotor;  // create a servo object

int angle = 0;     // initialize the angle variable

const int ldrPin = A0;  // LDR connected to analog pin A0
const int ledPin = 11;  // LDR connected to analog pin 11
const int servoPin = 9;  // Servo connected to digital pin 9
const int buttonPin = 2;  // the number of the pushbutton pin

// variables will change:
bool isMachineOn = false;  // variable for reading the pushbutton status

// Define a variable to store the state of the button
int buttonState = 0;
// Define a variable to store the previous state of the button
int prevButtonState = LOW;

void setup() {
  Serial.begin(9600); // Start serial communication for debugging
  pinMode(ledPin, OUTPUT);  // initialize the LED pin as an output
  pinMode(buttonPin, INPUT);  // initialize the pushbutton pin as an input
  servoMotor.attach(servoPin);  // attaches the servo on pin 9 to the servo object
}

void loop() {

  // read the state of the pushbutton value:
  buttonState = digitalRead(buttonPin);

  // Check Button is pressed or not
  if (buttonState == HIGH && prevButtonState == LOW) {
    isMachineOn =  !isMachineOn;  // Toggle State of Machine
  }

  if (isMachineOn) {
    float lightLevel = analogRead(ldrPin); // Read the value from the LDR
    lightLevel = map(lightLevel,60, 200, 0, 100); // Map LDR values to Useful Range

    if (lightLevel <= 0) lightLevel = 0;
    if (lightLevel > 100) lightLevel = 100;

    float brightness;
    brightness = map(lightLevel, 0, 50, 50, 0); // Map LDR values to LED brightness range
    if (brightness <= 0) brightness = 0; 
    
    Serial.print("Light Level: ");
    Serial.println(lightLevel); // Print the light level to Serial Monitor for debugging
    
    if (lightLevel < 15) { // You may need to adjust this threshold based on your ambient light conditions
      for (angle = 180; angle >= 0; angle -= 1) {
        analogWrite(ledPin, brightness); // Set LED brightness using PWM
        servoMotor.write(angle);   // tell servo to go to the specified angle
        delay(5);                 // waits 5ms for the servo to reach the position

        if (angle == 180) {
          delay(700);            // waits 0.7s for the servo to reach the position
        } else if (angle == 0) {
          delay(300);             // waits 0.3s for the servo to reach the position
        }
      }
    } else {
      analogWrite(ledPin, brightness); // Set LED brightness using PWM
      if (angle != 0) {
        angle = 0;  // Set Servo Angle at 0
        servoMotor.write(angle);  // tell servo to go to the specified angle
      }
      delay(500);                  // waits 0.5s for the servo to reach the position
    }

    Serial.print("Angle: ");
    Serial.println(angle);    // Print Angle of Servo at Serial
  } 
  
  else {
    Serial.println("Machine is sleeping...");
    analogWrite(ledPin, 0); // Set LED off
    delay(500);
  }

  prevButtonState = buttonState;  // Update the previous button state

}
