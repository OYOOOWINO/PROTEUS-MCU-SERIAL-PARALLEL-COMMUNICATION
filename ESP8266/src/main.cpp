#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266WebServer.h>
#include <LittleFS.h>

ESP8266WebServer server(80);

// Change The ssid and pwd
String ssid ="root";
String pwd ="root1234";
int led = D2;
int count = 0;

void slider(){
    File file = LittleFS.open("/slider.html", "r");
  if (LittleFS.exists("/slider.html")){
    server.streamFile(file, "text/html");
    file.close();
  }
}

void SET_VAL()
{
  String data = server.arg("plain");
  int sliderVal = data.toInt();
  Serial.write(sliderVal);
}

void setup()
{
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  LittleFS.begin();
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pwd);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting...");
    WiFi.begin(ssid, pwd);
  }
  Serial.println("WIFI OK");
  delay(30000);
  server.on("/setVal", HTTP_POST, SET_VAL);
  server.on("/", slider);
  server.begin();
}

void loop()
{
  server.handleClient();
  int brightness;
  if (Serial.available()) {
    brightness = (int) Serial.read();
    analogWrite(led, brightness*2);
    Serial.write(brightness);
  }
}
