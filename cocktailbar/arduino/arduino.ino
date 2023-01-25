#include <Servo.h>

#define BUTTON_PIN 7
#define POSITION_PIN A0
#define CALIBRATE_PIN A1
#define STEPS_PER_REV 360
#define STEPS_TO_DELAY 200
#define CLOCKWIZEROTATION HIGH
#define PUMP_1_RELAIS_PIN 11
#define PUMP_2_RELAIS_PIN 12
#define MOTOR_RELAIS_PIN 10

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

void setup() {
  Serial.begin(9600);
  myservo.attach(9);
  myservo.write(pos);

  delay(500);
  
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(POSITION_PIN, INPUT);
  pinMode(CALIBRATE_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  // motor
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
  pinMode(MOTOR_RELAIS_PIN, OUTPUT);
  pinMode(PUMP_1_RELAIS_PIN, OUTPUT);
  pinMode(PUMP_2_RELAIS_PIN, OUTPUT);

  digitalWrite(dirPin, CLOCKWIZEROTATION); 
  digitalWrite(MOTOR_RELAIS_PIN, HIGH);
  digitalWrite(PUMP_1_RELAIS_PIN, HIGH);
  digitalWrite(PUMP_2_RELAIS_PIN, HIGH);

  if (!calibrateState){
    calibrate();
  }

  vodkaCola();  
}

void loop() {
  currentState = digitalRead(BUTTON_PIN);

  if (!calibrateState){
    calibrate();
  }

  // Handeld het verzochte drankje van de esp af
  if(Serial.available()){
    receive = Serial.read();
    switch(receive) {
      case 0:
        Serial.println("Water");
        water();
        break;
      case 1:
        Serial.println("Vodka Cola");
        vodkaCola();
        break;
      case 2:
        Serial.println("Blue moon");
        blueMoon(); 
        break;
      case 3:
        Serial.println("Chardonnay");
        chardonnay();
        break;
      case 4:
        Serial.println("Rosé");
        rose();
        break;
      case 5:
      Serial.println("Cola");
        cola();
        break;
      case 6:
        Serial.println("Clean");
        clean();
        break;
    }
    Serial.write(1);
  }   

  // TIJDELIJK OF ALS RESET KNOP
  // Reset button -> volgend drankje kan gemaakt worden.
  if(lastState == LOW && currentState == HIGH){
    clean();   
  }

  lastState = currentState;
}

 
void movePressPump(int amount) {
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


void colaPump(int time){
  digitalWrite(PUMP_1_RELAIS_PIN, LOW);
  delay(time);
  digitalWrite(PUMP_1_RELAIS_PIN, HIGH);
}

void spritePump(int time){
  digitalWrite(PUMP_1_RELAIS_PIN, LOW);
  delay(time);
  digitalWrite(PUMP_1_RELAIS_PIN, HIGH);
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
      if(analogRead(CALIBRATE_PIN) < 100){
          calibrateState = true;
          break;
        }
    }
  } while(!calibrateState);

  digitalWrite(MOTOR_RELAIS_PIN, HIGH);
  Serial.write(1);
}


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
    for(int x = 0; x < 200; x++) {
      generatePulse(1000);
    } 

    // delay(2000);

    Serial.println(i);

    // Blijft draaien tot dat er een magneet gedetecteerd wordt
    do{
      for(int x = 0; x < STEPS_PER_REV; x++) {
        if(analogRead(POSITION_PIN) < 200){
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

void water(){
  movePressPump(20);
}

void vodkaCola(){
  moveStep(1);
  delay(1000);
  movePressPump(10);
  delay(1000);
  colaPump(10000);
  calibrateState = false;
}

void blueMoon(){
  moveStep(4);
  delay(1000);
  movePressPump(10);
  delay(1000);
  // Sprite pump
  // spritePump(10000);
  calibrateState = false;
}

void chardonnay(){
  moveStep(2);
  delay(1000);
  movePressPump(20);
  calibrateState = false;
}

void rose(){
  moveStep(5);
  delay(1000);
  movePressPump(20);
  calibrateState = false;
}

void cola(){
  colaPump(10000);
}


void clean() {
  Serial.println("clean");
  for(int i = 0; i < 5; i++){
    movePressPump(12);
  moveStep(1);
  }
}

// Rood - blauw
// Zwart - groen
