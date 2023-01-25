#include <Servo.h>

#define BUTTON_PIN 7
#define POSITION_PIN A0
#define CALIBRATE_PIN A1
#define STEPS_PER_REV 360
#define STEPS_TO_DELAY 200
#define CLOCKWIZEROTATION HIGH
#define PUMP_RELAIS_PIN 11
#define MOTOR_RELAIS_PIN 12

Servo myservo;  

const int dirPin = 2;  // Direction
const int stepPin = 3; // Step

bool calibrateState = false;
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
  digitalWrite(dirPin, CLOCKWIZEROTATION); 
  
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(POSITION_PIN, INPUT);
  pinMode(CALIBRATE_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  // motor
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(MOTOR_RELAIS_PIN, OUTPUT);
  pinMode(PUMP_RELAIS_PIN, OUTPUT);

  
  digitalWrite(MOTOR_RELAIS_PIN, HIGH);
  digitalWrite(PUMP_RELAIS_PIN, HIGH);

  myservo.write(pos);
  
  

  // if (!calibrateState){
  //   calibrate();
  // }

  // delay(5000);

  // movePump(5);

  moveStep(3);
}

void loop() {
  // Serial.println(calibrateState);

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

  // if(analogRead(POSITION_PIN) > 5) {
  //   Serial.println("magneetje");
  // }

  // Serial.println(analogRead(POSITION_PIN));
}

 
void movePump(int amount) {
  for(int i = 0; i < amount; i++){
     for (pos = 0; pos <= 160; pos += 1) { 
    myservo.write(pos);              
    delay(3);      
  }

  delay(100);

  for (pos = 160; pos >= 0; pos -= 1) { 
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

  digitalWrite(MOTOR_RELAIS_PIN, LOW);
  do{
    for(int x = 0; x < (STEPS_PER_REV); x++) {
      generatePulse(1000);
      if(analogRead(CALIBRATE_PIN) < 10){
          calibrateState = true;
          break;
        }
    }
  } while(!calibrateState);

  digitalWrite(MOTOR_RELAIS_PIN, HIGH);
  Serial.write(1);
}


// x Zetje geven plus delay (delay later verwijderen)
// x Blijven draaien
// x Magneten herkennen
// x Stoppen wanneer magneet herkent wordt
// x Amount forloep toepasen


// Amount saat voor aantal posities opschuiven vanaf het calibratie punt.
void moveStep(int amount) {
  // Bereid de motoren voor
  Serial.println("Move");
  Serial.println(amount);
  digitalWrite(MOTOR_RELAIS_PIN, LOW);

  // Zorgt dat de do while blijft doorgaan.
  moveMotor = true;

  // Herhaald de onderstaande code "amount" aantal keer 
  for(int i = 0; i < amount; i++) {
    Serial.println("Zetje");

    // Geeft een zetje
    for(int x = 0; x < STEPS_PER_REV; x++) {
      generatePulse(1000);
    } 

    // delay(2000);

    Serial.println(i);

    // Blijft draaien tot dat er een magneet gedetecteerd wordt
    do{
      for(int x = 0; x < STEPS_PER_REV; x++) {
        if(analogRead(POSITION_PIN) < 100){
          moveMotor = false;
          break;
        }
        generatePulse(1000);
      }
    } while(moveMotor);
    // Zet motor weer op true zodat deze eventueel door kan draaien naar de volgende magneet
    moveMotor = true;
  }

  Serial.println("Done");
  digitalWrite(MOTOR_RELAIS_PIN, HIGH);
}

// Rood - blauw
// Zwart - groen
