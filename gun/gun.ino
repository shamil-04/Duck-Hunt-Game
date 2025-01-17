#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
//#include <WiFiClient.h>

const char* ssid = "mithunxavior"; //Enter SSID
const char* password = ""; //Enter Password

String server = "http://192.168.225.85:5000/update_shot";

// constants won't change. They're used here to set pin numbers:
const int buttonPin = 1;    // the number of the pushbutton pin
const int ledPin = 5;      // the number of the LED pin
const int vibe = 4; 
// Variables will change:
int ledState = HIGH;         // the current state of the output pin
int buttonState;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

// the following variables are unsigned longs because the time, measured in
// milliseconds, will quickly become a bigger number than can be stored in an int.
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 25;    // the debounce time; increase if the output flickers
      WiFiClient client;
      HTTPClient http;
void setup() {
  Serial.begin(115200);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(vibe, OUTPUT);


  // set initial LED state
  digitalWrite(ledPin, 0);


WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) 
  {
     delay(500);
     Serial.print("*");
  }
  
  Serial.println("");
  Serial.println("WiFi connection Successful");
  Serial.print("The IP Address of ESP8266 Module is: ");
  Serial.print(WiFi.localIP());// Print the IP address

  http.begin(client, server.c_str());
}

void loop() {
  // read the state of the switch into a local variable:
  int reading = digitalRead(buttonPin);


  // check to see if you just pressed the button
  // (i.e. the input went from LOW to HIGH), and you've waited long enough
  // since the last press to ignore any noise:

  // If the switch changed, due to noise or pressing:
  if (reading != lastButtonState) {
    // reset the debouncing timer
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:

    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;

      // only toggle the LED if the new button state is HIGH
      if (buttonState == LOW) {
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
        digitalWrite(ledPin, 0);
        digitalWrite(vibe, 1);
        

        delay(100);
         digitalWrite(ledPin, 1);
         digitalWrite(vibe, 0);

        
      }
    }
  }

  // set the LED:
  

  // save the reading. Next time through the loop, it'll be the lastButtonState:
  lastButtonState = reading;
}
