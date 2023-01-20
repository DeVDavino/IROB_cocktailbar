/*
  Stepper Motor Demonstration 4
  Stepper-Demo4.ino
  Demonstrates NEMA 17 Bipolar Stepper with A4988 Driver
 
  DroneBot Workshop 2018
  https://dronebotworkshop.com
*/
 
// Define Constants
 
// Connections to A4988

// Motor steps per rotation
const int STEPS_PER_REV = 360;
const int dirPin = 2;  // Direction
const int stepPin = 3; // Step
const int startPoint = 0;
const int bottles = 6;
int bottlePositionInDegrees = (STEPS_PER_REV / bottles); 
int stepPosition;


 
void setup() {
  Serial.begin(9600);
  // Setup the pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
}
void loop() {
  int fullRotate = 512;
  int degSixty = 85;
  // makeSteps(degSixty);
  rotateClockwize();
  // Set motor direction clockwise
  digitalWrite(dirPin,HIGH); 
  
  Serial.println(stepPosition);
  
}

void rotateClockwize(){
    // Spin motor one rotation slowly ()
    for(int x = 0; x < (STEPS_PER_REV); x++) {
      // Creates a pulse that drives the STEP pin on the module.
      digitalWrite(stepPin,HIGH); 
      generatePulse();
      if(x == bottlePositionInDegrees){
        delay(1000);
      }
    } 
}

// void makeSteps(int steps){
//    for(int y = 0; y <= steps; y ++){
//       digitalWrite(stepPin,HIGH); 
//       delayMicroseconds(500); 
//       digitalWrite(stepPin,LOW); 
//       delayMicroseconds(500);
//    }
// }

void generatePulse(int pulse){
  delayMicroseconds(pulse); 
  digitalWrite(stepPin,LOW); 
  delayMicroseconds(pulse);
}



