// Copyright Nat Weerawan 2015-2016
// MIT License
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiConnector.h>

#ifndef WIFI_SSID
  #define WIFI_SSID       "Flamboyan"
  #define WIFI_PASSPHRASE "Berastagi9090"
#endif

WiFiConnector wifi(WIFI_SSID, WIFI_PASSPHRASE);

void init_hardware()
{
  Serial.begin(9600);
  WiFi.disconnect(true);
  delay(1000);
  Serial.flush();
  Serial.println();
  Serial.println();
  Serial.println("will be started in 500ms..");
}

void init_wifi() {
  wifi.init();
  wifi.on_connected([&](const void* message)
  {
    Serial.print("WIFI CONNECTED WITH IP: ");
    Serial.println(WiFi.localIP());
  });

  wifi.on_connecting([&](const void* message)
  {
    Serial.print("Connecting to ");
    Serial.println(wifi.get("ssid") + ", " + wifi.get("password"));
    delay(200);
  });
}

void setup()
{
  init_hardware();
  init_wifi();
  wifi.connect();
}

void loop()
{
  wifi.loop();
}
