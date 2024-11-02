/*
  Modified sketch to control a 28BYJ-48 stepper motor 
  with ULN2003 driver board and Arduino UNO.
*/

// Include the Arduino Stepper.h library:
#include "Stepper.h"

// Define number of steps per rotation:
const int stepsPerRevolution = 2048;

// Wiring:
// Pin 8 to IN1 on the ULN2003 driver
// Pin 9 to IN2 on the ULN2003 driver
// Pin 10 to IN3 on the ULN2003 driver
// Pin 11 to IN4 on the ULN2003 driver

// Create stepper object called 'myStepper', note the pin order:
Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  // Set the speed to 20 rpm:
  myStepper.setSpeed(20);
  
  // Begin Serial communication at a baud rate of 9600:
  Serial.begin(9600);
}

void loop() {
  // Check if data is available in Serial buffer
  if (Serial.available() > 0) {
    // Read the incoming byte
    char incomingByte = Serial.read();
    
    // If the character '1' is received
    if (incomingByte == '1') {
      Serial.println("Moving to position");
      
      // Move to a specified position (1 full revolution clockwise)
      myStepper.step(stepsPerRevolution);
      
      // Wait for 5 seconds
      delay(5000);
      
      // Return to original position (1 full revolution counterclockwise)
      Serial.println("Returning to original position");
      myStepper.step(-stepsPerRevolution);

      // Clear any remaining Serial data to avoid unwanted moves
      while (Serial.available() > 0) {
        Serial.read();  // Discard incoming characters
      }
    }
  }
}
