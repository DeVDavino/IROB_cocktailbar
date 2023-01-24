#include <Servo.h>

#define BUTTON_PIN 7
#define POSITION_PIN A0
#define CALIBRATE_PIN A1
#define STEPS_PER_REV 360
#define STEPS_TO_DELAY 200
#define CLOCKWIZEROTATION HIGH
#define COUNTERCLOCKWIZEROTATION LOW
#define MOTOR_RELAIS_PIN 12

Servo myservo;  

const int dirPin = 2;  // Direction
const int stepPin = 3; // Step

bool calibrateState = true;
bool moveMotor = true;
int counterInsideLoop; //  counter that increments on each itteration of the forloop
int lastState = HIGH;
int currentState;
int receive = 0;
int pos = 0;  

// 0 baco
// 1 malibu cola
// 2 rum fanta
// 3 malibu fanta

void setup() {
  Serial.begin(9600);
  myservo.attach(9);  

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(POSITION_PIN, INPUT);
  pinMode(CALIBRATE_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  // motor
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(MOTOR_RELAIS_PIN, OUTPUT);

  digitalWrite(MOTOR_RELAIS_PIN, LOW);

  myservo.write(pos);
  
  if (!calibrateState){
    calibrate();
  }

  delay(5000);

  moveStep(2);


  
}

void loop() {
  currentState = digitalRead(BUTTON_PIN);

  // Handeld het verzochte drankje van de esp af
  if(Serial.available()){
    receive = Serial.read();
    switch(receive) {
      case 0:
        Serial.println("Baco");
        movePump(1); 
        break;
      case 1:
        Serial.println("Malibu Cola");
        movePump(20); 
        break;
      case 2:
        Serial.println("Rum Fanta");
        movePump(20); 
        break;
      case 3:
        Serial.println("Malibu Fanta");
        movePump(20); 
        break;
    }
  }   

  // TIJDELIJK OF ALS RESET KNOP
  // Reset button -> volgend drankje kan gemaakt worden.
  if(lastState == LOW && currentState == HIGH){
    Serial.write(1);   
  }

  lastState = currentState;

  if(analogRead(POSITION_PIN) > 5) {
    Serial.println("magneetje");
  }

  Serial.println(analogRead(POSITION_PIN));
}

 
void movePump(int amount) {
  for(int i = 0; i < amount; i++){
     for (pos = 0; pos <= 100; pos += 1) { 
    myservo.write(pos);              
    delay(3);      
  }

  delay(100);

  for (pos = 100; pos >= 0; pos -= 1) { 
    myservo.write(pos);              
    delay(3);                 
  }

  delay(500);

  Serial.println("pomp");
  }
}


void generatePulse(int pulse){
  digitalWrite(stepPin,HIGH); 
  delayMicroseconds(pulse); 
  digitalWrite(stepPin,LOW); 
  delayMicroseconds(pulse);
}


void calibrate(){
  Serial.println("calibrate");
  digitalWrite(MOTOR_RELAIS_PIN, HIGH);
  do{
    for(int x = 0; x < (STEPS_PER_REV); x++) {
      generatePulse(1000);
      counterInsideLoop++;
    }
    Serial.println(counterInsideLoop);

  } while(analogRead(CALIBRATE_PIN) > 10);
  digitalWrite(MOTOR_RELAIS_PIN, LOW);
  Serial.write(1);
  calibrateState = true;
}


void moveStep(int amount) {
  digitalWrite(MOTOR_RELAIS_PIN, HIGH);

  for(int x = 0; x < STEPS_PER_REV; x++) {
    generatePulse(1000);
  }
  for(int i = 0; i < amount; i++) {
    do{
      for(int x = 0; x < STEPS_PER_REV; x++) {
        if(analogRead(POSITION_PIN) < 5){
          moveMotor = false;
          break;
        }
        generatePulse(1000);
      }
    } while(moveMotor);
  }
  digitalWrite(MOTOR_RELAIS_PIN, LOW);
}


