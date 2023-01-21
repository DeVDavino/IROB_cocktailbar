#define STEPS_PER_REV 360
#define STEPS_TO_DELAY 200
#define BACO 900
#define MALIBUCOLA 1800
#define RUMFATNA 2700
#define MALIBUFANTA 3600

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
  // rotateClockwizeAndStopEach60Degrees();
  // Serial.println("Hello World");

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

//rotates motors to first position which is Bacardi Cola
void rotateToBaco(){
  for(int x = 0; x < (STEPS_PER_REV); x++){
    generatePulse(1000);
    if(counterInsideLoop % BACO == 0){
      break;
    }
  }
  Serial.println("Bacardi Cola positie is bereikt");
}

//rotates motors to first position which is Malibu Cola
void rotateToMalibuCola(){
  for(int x = 0; x < (STEPS_PER_REV); x++){
    generatePulse(1000);
    counterInsideLoop++;
    if(counterInsideLoop % MALIBUCOLA == 0){
      break;
    }
  }
  Serial.println("Malibu Cola positie is bereikt");
}

//rotates motors to first position which is Rum Fanta
void rotateToRumFanta(){
  for(int x = 0; x < (STEPS_PER_REV); x++){
    generatePulse(1000);
    counterInsideLoop++;
    if(counterInsideLoop % RUMFATNA == 0){
      break;
    }
  }
  Serial.println("Rum Fanta positie is bereikt");
}

//rotates motors to first position which is Malibu Fanta
void rotateToMalibuFanta(){
  for(int x = 0; x < (STEPS_PER_REV); x++){
    generatePulse(1000);
    counterInsideLoop++;
    if(counterInsideLoop % MALIBUFANTA == 0){
      break;
    }
  }
  Serial.println("Malibu Fanta positie is bereikt");
}








