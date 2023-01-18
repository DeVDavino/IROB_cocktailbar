#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h> 
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h> 

#include "index.h"

ESP8266WiFiMulti wifiMulti; 

ESP8266WebServer server(80);   

int receive = 0;

void handleRoot();              // function prototypes for HTTP handlers
void handleNotFound();

bool busy = false;

void setup(void){
  Serial.begin(9600);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');

  wifiMulti.addAP("Hi", "deCocktailbar2023");
  wifiMulti.addAP("ssid_from_AP_3", "your_password_for_AP_3");
  wifiMulti.addAP("ssid_from_AP_3", "your_password_for_AP_3");

  Serial.println("Connecting ...");
  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED) { // Wait for the Wi-Fi to connect: scan for Wi-Fi networks, and connect to the strongest of the networks above
    delay(250);
    Serial.print('.');
  }

  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());           
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());          

  if (MDNS.begin("cocktailbar")) {              
    Serial.println("mDNS responder started");
  } else {
    Serial.println("Error setting up MDNS responder!");
  }

  server.on("/", handleRoot);  
  server.on("/baco", handleBaco);
  server.on("/malibu-cola", handleMalibuCola);
  server.on("/rum-fanta", handleRumFanta); 
  server.on("/malibu-fanta", handleMalibuFanta);
  server.onNotFound(handleNotFound);        

  server.begin();                           
  Serial.println("HTTP server started");
}

void loop(void){
  MDNS.update();
  server.handleClient();   

  if(Serial.available()){
    receive = Serial.read();
    if(receive == 1) {
      Serial.println("Done");
      busy = false;
    }
  } 
}

void handleRoot() {
  String index = MAIN_PAGE;
  server.send(200, "text/html", index); 
}

void handleBaco() {
  Serial.println("Baco");
  request(0);
}

void handleMalibuCola() {
  Serial.println("Malibu Cola");
  request(1);
}

void handleRumFanta() {
  Serial.println("Rum Fanta");
  request(2);
}

void handleMalibuFanta() {
  Serial.println("Malibu Fanta");
  request(3);
}

void request(int drink) {
  if(busy) {
    server.send(200, "text/plain", "De cocktailbar is bezig. probeer het later nog eens.");  
    server.send(303); 
  } else {
    Serial.write(drink);
    busy = true;
    server.send(200, "text/plain", "Uw drankje wordt gemaakt"); 
    server.send(303); 
  }  
}


void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); 
}