#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <LCD_I2C.h>
#include <Servo.h>
#include <Stepper.h>

// definition blink
#define BLYNK_TEMPLATE_ID           "TMPxxxxxx"
#define BLYNK_TEMPLATE_NAME         "Device"
#define BLYNK_AUTH_TOKEN            "YourAuthToken"

#define BLYNK_PRINT Serial

// Definition pin
#define PROXIMITY_PIN D8  // Pin for sensor proximity
#define MQ4_PIN A0        // Pin for sensor MQ-4
#define SERVO_PIN D7      // Pin for servo motor
#define STEPPER_PIN1 D3   // Pin for stepper motor
#define STEPPER_PIN2 D4
#define STEPPER_PIN3 D5
#define STEPPER_PIN4 D6

// Inisialisasi objet
LCD_I2C lcd(0x27, 16, 2);
Servo servoMotor;
Stepper stepperMotor(512, STEPPER_PIN1, STEPPER_PIN3, STEPPER_PIN2, STEPPER_PIN4);

void setup() {
  Serial.begin(9600);
  Serial.println();

  WiFi.begin("network-name", "pass-to-network");

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  lcd.begin();
  lcd.backlight();
  pinMode(PROXIMITY_PIN, INPUT);
  pinMode(MQ4_PIN, INPUT);
  servoMotor.attach(SERVO_PIN);
  stepperMotor.setSpeed(10);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  // You can also specify server:
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, "blynk.cloud", 80);
  //Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop() 
{
    Blynk.run();
    lcd.setCursor(4, 0);
    lcd.print("PLEASE");
    lcd.setCursor(1, 1);
    lcd.print("PUT IN TRASH");
    delay(000);
    lcd.clear();
    if (digitalRead(PROXIMITY_PIN) == HIGH) {
        lcd.clear();
        lcd.print("METAL TRASH");
        delay(1000);
        
        // Control the stopper motor, open the servo, and insert it into the metal trash can
        controlMetalWaste();
        
        lcd.clear();
        lcd.print("METAL TRASH");
        delay(2000);
    } else if (analogRead(MQ4_PIN) > 500) {
        lcd.clear();
        lcd.print("METHANE DETECTED");
        delay(1000);
        
        // Control the stopper motor, open the servo, and put it in the organic waste bin
        controlOrganicWaste();
        
        lcd.clear();
        lcd.print("ORGANIC TRASH");
        delay(2000);
    } else {
        lcd.clear();
        lcd.print("INORGANIC TRASH");
        delay(2000);
        
        // Control the stopper motor, open the servo, and put it into the inorganic trash can
        controlInorganicWaste();
        
        lcd.clear();
        lcd.print("INORGANIC TRASH");
        delay(2000);
    }

    // Return the stepper to the starting position
    stepperMotor.step(-512);
    delay(1000);
}

void openServo(){
  // open servo motor
  servoMotor.write(90);
  delay(5000);
}

void controlMetalWaste() {
  // Control the stopper motor
  openServo();
}

void controlOrganicWaste() {
  openServo();
}

void controlInorganicWaste() {
  openServo();
}