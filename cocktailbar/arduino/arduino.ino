#include <Servo.h>

bool calibrated = false;

const int BUTTON_PIN = 7;
const int HALL_PIN = A0;

int lastState = HIGH;
int currentState;

int receive = 0;

Servo myservo;  
int pos = 0;  

// 0 baco
// 1 malibu cola
// 2 rum fanta
// 3 malibu fanta

void setup() {
  Serial.begin(9600);
  myservo.attach(9);  

  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(HALL_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
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
        movePump(2); 
        break;
      case 2:
        Serial.println("Rum Fanta");
        movePump(3); 
        break;
      case 3:
        Serial.println("Malibu Fanta");
        movePump(4); 
        break;
    }
  }   

  // Reset button -> volgend drankje kan gemaakt worden.
  if(lastState == LOW && currentState == HIGH){
    Serial.write(1);   
  }
  lastState = currentState;

  // Neemt de calibrate magneet weer. 
  if (analogRead(HALL_PIN) == 0) {
    Serial.write(1);
    calibrated = true;
    Serial.println("magneet");
  } 
  
  
  // Kan later weg, is te zien of de magneet gedetecteerd wordt.
  if(!calibrated) {
    digitalWrite(LED_BUILTIN, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }
}

// 
void movePump(int amount) {
  calibrated = false;

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