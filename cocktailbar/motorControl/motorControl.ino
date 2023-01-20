#define STEPS_PER_REV 360
#define STEPS_TO_DELAY 900

const int dirPin = 2;  // Direction
const int stepPin = 3; // Step
const int startPoint = 0;

// testing
int counterInsideLoop;

void generatePulse(int pulse){
  digitalWrite(stepPin,HIGH); 
  delayMicroseconds(pulse); 
  digitalWrite(stepPin,LOW); 
  delayMicroseconds(pulse);
}

void setup() {
  Serial.begin(9600);
  // Setup the pins as Outputs
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
}

void loop() {
  //Set the motors to HIGH in order for them to rotate clockwize
  digitalWrite(dirPin,HIGH); 
  // Function that handles rotating in a specific degree
  rotateClockwizeAndStopEach60Degrees();

}

void rotateClockwizeAndStopEach60Degrees(){ 

  for(int x = 0; x < (STEPS_PER_REV); x++) {
    // Creates a pulse that drives the STEP pin on the module.
    generatePulse(1000);
    counterInsideLoop++;
    if(counterInsideLoop % STEPS_TO_DELAY == 0){
      delay(1000);
    }
  }
  Serial.println(counterInsideLoop);

}





