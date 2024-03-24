#define RXp2 16
#define TXp2 17

#include "WiFi.h"
#include <HTTPClient.h>

const char* ssid = "mithunxavior";
const char* password = "Pullazhy@680012";
String server = "http://192.168.225.85:5000/update_duck";
HTTPClient http;
void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);
  initWiFi();
  http.begin(server.c_str());
  
}
void loop() {
    

    
      
    
    String stat=Serial2.readString();
    if(stat!=NULL){
    Serial.println(stat);
    int httpResponseCode = http.GET();
      
      if (httpResponseCode>0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        String payload = http.getString();
        Serial.println(payload);
      }
      else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
      }
      // Free resources
      http.end();
    }
}
