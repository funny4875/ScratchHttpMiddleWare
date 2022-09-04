#include <ESP8266WiFi.h>
 
//
const char* ssid = "Lee0932";
const char* password = "0932703612";
 
// Socket Server
const char* host = "192.168.1.143";
const int port = 3000;
 
int i = 0;
 
WiFiClient client;
 
void setup() {
  Serial.begin(115200);
  Serial.print( "Start..." );
  //pinMode(5,INPUT_PULLUP);
  pinMode(5,OUTPUT);
  digitalWrite(5,HIGH);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }
}
int state=0;
void loop() {
  if (!client.connected()) {
    client.connect(host, port);
    //client.println("OK");
  }
  if(state==0){
    int v = analogRead(A0)>>2;
    int d5 = digitalRead(5);
    client.print(v);
    client.print(',');
    client.print(d5);
    client.println();
    state=1;
  }
  else
  {
    //if (client.available())
    //{
      String line = client.readStringUntil('\n');
      Serial.println(line);
      state=0;
    //}
  }
 delay(100);
 //Serial.println(state);
}
