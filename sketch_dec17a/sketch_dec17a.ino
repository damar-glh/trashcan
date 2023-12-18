#define BLYNK_TEMPLATE_ID "TMPL66UOXJvmx"
#define BLYNK_TEMPLATE_NAME "TRASHCAN"
#define BLYNK_AUTH_TOKEN "2nbYxdWBDUdEDMSNr3v7J5XjxRzd9fhN"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <LCD_I2C.h>

// Define the Blynk template ID and name

#define BLYNK_PRINT Serial

LCD_I2C lcd(0x27, 16, 2);

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Flamboyan";
char pass[] = "Berastagi9090";

void setup() {
  // put your setup code here, to run once:
  lcd.begin();
  lcd.backlight();
  Serial.begin(9600);
  //connectWiFi();
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
}

void connectWiFi(){
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) 
  {
     delay(500);
     Serial.print("*");
  }
  
  Serial.println("");
  Serial.println("WiFi connection Successful");
  Serial.print("The IP Address of ESP8266 Module is: ");
  Serial.print(WiFi.localIP());// Print the IP address
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();

}

BLYNK_WRITE (V3){
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("PLEASE");
    lcd.setCursor(1, 1);
    lcd.print("PUT IN TRASH");
    delay(1000);
  }