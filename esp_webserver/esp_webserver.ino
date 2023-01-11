#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h> 
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>   

ESP8266WiFiMulti wifiMulti;     

ESP8266WebServer server(80);   

void handleRoot();              // function prototypes for HTTP handlers
void handleNotFound();

void setup(void){
  Serial.begin(115200);         // Start the Serial communication to send messages to the computer
  delay(10);
  Serial.println('\n');

  wifiMulti.addAP("Schwifty", "$%sw_!ift%,.");
  wifiMulti.addAP("ssid_from_AP_2", "your_password_for_AP_2");
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
  server.onNotFound(handleNotFound);        

  server.begin();                           
  Serial.println("HTTP server started");
}

void loop(void){
  MDNS.update();
  server.handleClient();                   
}

void handleRoot() {
  server.send(200, "text/plain", "Hallo, welk drankje wil je?"); 
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found"); 
}