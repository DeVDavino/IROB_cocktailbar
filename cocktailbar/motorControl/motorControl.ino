#define STEPS_PER_REV 360
#define STEPS_TO_DELAY 900
#define BACO 900
#define MALIBUCOLA 1800
#define RUMFATNA 2700
#define MALIBUFANTA 3600
#define CLOCKWIZEROTATION HIGH
#define COUNTERCLOCKWIZEROTATION LOW

const int dirPin = 2;  // Direction
const int stepPin = 3; // Step
// row of leds
const int ledPinOne = 4;
const int ledPinTwo = 5;
const int ledPinThree = 6;
const int ledPinFour = 7;
// -----------------------
const int buttonPin = 8; // pushbutton pin
int buttonState;
int buttonCounter;
// -----------------------
int counterInsideLoop; //  counter that increments on each itteration of the forloop


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

  // Baco pin -> testing with LEDS
  pinMode(ledPinOne, OUTPUT);
  // Malibu Cola -> testing with LEDS
  pinMode(ledPinTwo, OUTPUT);
  // Rum Fanta -> testing with LEDS
  pinMode(ledPinThree, OUTPUT);
  // Malibu Fanta -> testing with LEDS
  pinMode(ledPinFour, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
}

void loop() {
  //Set the motors to HIGH in order for them to rotate clockwize
  digitalWrite(dirPin,HIGH); 
  // Function that handles rotating in a specific degree
  // rotateClockwizeAndStopEach60Degrees();
  buttonState = digitalRead(buttonPin);

  // if(buttonState == HIGH){
  //   digitalWrite(ledPinOne, HIGH);
  //   digitalWrite(ledPinTwo, HIGH);
  //   digitalWrite(ledPinThree, HIGH);
  //   digitalWrite(ledPinFour, HIGH);
  // } else{
  //   digitalWrite(ledPinOne, LOW);
  //   digitalWrite(ledPinTwo, LOW);
  //   digitalWrite(ledPinThree, LOW);
  //   digitalWrite(ledPinFour, LOW);
  //   buttonCounter++;
  //   Serial.println(buttonCounter);
  // }

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

//rotates motors to first position which is Bacardi Cola
void rotateToBaco(){

  digitalWrite(dirPin,HIGH); 
  for(int x = 0; x < (STEPS_PER_REV); x++){
  generatePulse(1000);
  counterInsideLoop++;
  }
  Serial.println(counterInsideLoop);
  
}

//rotates motors to first position which is Malibu Cola
void rotateToMalibuCola(){
  for(int x = 0; x < (STEPS_PER_REV); x++){
    digitalWrite(dirPin,CLOCKWIZEROTATION); 
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








