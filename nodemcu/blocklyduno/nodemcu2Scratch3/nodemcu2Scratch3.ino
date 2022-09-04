/*
 * Generated using BlocklyDuino:
 *
 * https://github.com/MediaTek-Labs/BlocklyDuino-for-LinkIt
 *
 * Date: Sun, 04 Sep 2022 14:44:53 GMT
 */
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

char _lwifi_ssid[] = "此處輸入WIFI SSID";
char _lwifi_pass[] = "此處輸入WIFI 密碼";
String res = "";
String P = "";
int D6_ = 12;

String tcp_https_esp32(String type,String domain,String request,int port,int waittime) {
  String getAll="", getBody="";
  WiFiClientSecure client_tcp;
  client_tcp.setInsecure();
  if (client_tcp.connect(domain.c_str(), port)) {
    //Serial.println("Connected to "+domain+" successfully.");
    client_tcp.println(type + " " + request + " HTTP/1.1");
    client_tcp.println("Host: " + domain);
    client_tcp.println("Connection: close");
    client_tcp.println("Content-Length: 0");
    client_tcp.println();
    boolean state = false;
    long startTime = millis();
    while ((startTime + waittime) > millis()) {
      while (client_tcp.available()) {
        char c = client_tcp.read();
        if (c == '\n') {
          if (getAll.length()==0) state=true;
           getAll = "";
        }
        else if (c != '\r')
          getAll += String(c);
          if (state==true) getBody += String(c);
          startTime = millis();
        }
        if (getBody.length()!= 0) break;
      }
      client_tcp.stop();
  }
  else {
    getBody="Connected to "+domain+" failed.";
    Serial.println("Connected to "+domain+" failed.");
  }
  return getBody;
}

void setup()
{
  Serial.begin(9600);

  WiFi.begin(_lwifi_ssid, _lwifi_pass);
  while (WiFi.status() != WL_CONNECTED) { delay(500); }
  delay(300);
  pinMode(D6_, OUTPUT);
}

void loop()
{
  P = String("/")+String(String(analogRead(A0)));
  res = tcp_https_esp32("GET", "此處輸電腦端IP", P, 443, 1000);
  analogWrite(D6_, (res.toInt()));
}
