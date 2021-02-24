/*
 Liam Homburger

 This is the client code for the Drone Dropper
 
 https://github.com/Liamq12
 */

//Import Libraries
#include <WiFi.h>
#include <HTTPClient.h>

//Digital button pin
#define buttonPin 6

//Same SSID and Password as on server
const char* ssid = "myDroneDropper";
const char* password = "sErV0";

//Your IP address or domain name with URL path. Server IP will always be 192.168.4.1
const char* serverNameDrop = "http://192.168.4.1/drop";

void setup() {
  //Serial moniter startup
  Serial.begin(115200);
  //Set button pin to read input
  pinMode(buttonPin, INPUT);
  //Enable and set WIFI
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
    //Request drop from server if button is pressed
    if(digitalRead(buttonPin) == HIGH){ 
      String HTTPDrop = httpGETRequest(serverNameDrop);
      Serial.println("Reponse: " + HTTPDrop);
  }
}

String httpGETRequest(const char* serverName) {
  HTTPClient http;
    
  // IP Adress of server with endpoint
  http.begin(serverName);
  
  // Send HTTP GET request to server
  int httpResponseCode = http.GET();

  // Use empty payload
  String payload = "--"; 

  //Report response and any error
  if (httpResponseCode>0) {
    Serial.print("HTTP Response code: ");
    Serial.println(httpResponseCode);
    payload = http.getString();
  } else {
    Serial.print("Error code: ");
    Serial.println(httpResponseCode);
  }
  // Free resources
  http.end();

  return payload;
}
