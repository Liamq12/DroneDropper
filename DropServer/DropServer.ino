/*
 Liam Homburger

 This is the server code for the Drone Dropper
 
 https://github.com/Liamq12
 */

// Import required libraries
#include "WiFi.h"
#include "ESPAsyncWebServer.h"

// Set your access point network credentials
const char* ssid = "myDroneDropper";
const char* password = "sErV0";

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);

String dropPayload() {
  // Servo code here to open the payload area and release content
  return String("Payload Released"); //Confirmation message to be sent to client
}

void setup(){
  // Serial port for debugging purposes
  Serial.begin(115200);
  Serial.println();
  
  // Setting the ESP as an access point
  Serial.print("Setting AP…");
  // Configure wifi SSID and Password
  WiFi.softAP(ssid, password);

  // Print the server IP in the serial moniter
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);

  // Request Handlers
  // Parameters: endpoint, HTTP Method, Request
  server.on("/drop", HTTP_GET, [](AsyncWebServerRequest *request){
    // Parameters: HTTP RC, Content-Type, Response Body
    request->send_P(200, "text/plain", dropPayload().c_str());
  });

  // Start server
  server.begin();
}
 
void loop(){
  
}
