const int BUTTON_PIN = 7;

int lastState = HIGH; // the previous state from the input pin
int currentState;

int receive = 0;

// 0 baco
// 1 malibu cola
// 2 rum fanta
// 3 malibu fanta

void setup() {
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  if(Serial.available()){
    receive = Serial.read();
    switch(receive) {
      case 0:
        Serial.println("Baco");
        break;
      case 1:
        Serial.println("Malibu Cola");
        break;
      case 2:
        Serial.println("Rum Fanta");
        break;
      case 3:
        Serial.println("Malibu Fanta");
        break;
    }
  }   

  currentState = digitalRead(BUTTON_PIN);
  if(lastState == LOW && currentState == HIGH){
    Serial.write(1);    
  }
  
  lastState = currentState;
}