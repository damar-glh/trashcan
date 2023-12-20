// Define the Blynk template ID and name
#define BLYNK_TEMPLATE_ID "TMPL66UOXJvmx"
#define BLYNK_TEMPLATE_NAME "TRASHCAN"
#define BLYNK_AUTH_TOKEN "2nbYxdWBDUdEDMSNr3v7J5XjxRzd9fhN"

#include <LCD_I2C.h>
#include <Servo.h>
#include <Stepper.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

#define BLYNK_PRINT Serial

// blynk connections
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "damaraaa.";
char pass[] = "damaraaa.";

// Definition pin
#define PROXIMITY_PIN 3  // Pin for sensor proximity
#define MQ4_PIN A0        // Pin for sensor MQ-4
#define SERVO_PIN D7      // Pin for servo motor

// Pin for stepper motor
#define STEPPER_PIN1 D3   
#define STEPPER_PIN2 D4
#define STEPPER_PIN3 D5
#define STEPPER_PIN4 D6

// sensor ultrasonic
#define TRIG_PIN  D8
#define ECHO_PIN  D0

// varibel default blynk
  int metalTrashCount;
  int organicTrashCount;
  int anorganicTrashCount;

// Inisialisasi objek
LCD_I2C lcd(0x27, 16, 2);
Servo servoMotor;
Stepper stepperMotor(200, STEPPER_PIN1, STEPPER_PIN3, STEPPER_PIN2, STEPPER_PIN4);

float X=400/397.63;

void setup() {
  Serial.begin(9600);
  lcd.begin();
  lcd.backlight();
  pinMode(PROXIMITY_PIN, INPUT);
  pinMode(MQ4_PIN, INPUT);
  servoMotor.attach(SERVO_PIN, 500, 2400);
  stepperMotor.setSpeed(100);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
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

void openServo(){
  // open servo motor
  servoMotor.write(20);
  delay(2000);
}

void controlMetalWasteOn() {
  // Control the stopper motor
  stepperMotor.step(500);
  delay(100);
  stepperMotor.step(500);
  delay(100);
  stepperMotor.step(500);
  delay(100);
  stepperMotor.step(500);
  delay(100);
}

void controlMetalWasteCenter() {
  stepperMotor.step(-500);
  delay(100);
  stepperMotor.step(-500);
  delay(100);
  stepperMotor.step(-500);
  delay(100);
  stepperMotor.step(-500);
  delay(100);
}

void controlOrganicWasteOn() {
  stepperMotor.step(-500);
  delay(100);
  stepperMotor.step(-500);
  delay(100);
  stepperMotor.step(-500);
  delay(100);
  stepperMotor.step(-500);
  delay(100);
}

void controlOrganicWasteCenter() {
  stepperMotor.step(500);
  delay(100);
  stepperMotor.step(500);
  delay(100);
  stepperMotor.step(500);
  delay(100);
  stepperMotor.step(500);
  delay(100);
}

void controlInorganicWaste() {
  openServo();
}

void loop(){
  Blynk.run();
  
  // distance initialitation
  //Generate ultrasonic signal
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  //Read ultrasonic signal
  float duration = pulseIn(ECHO_PIN, HIGH);
  float distance = (duration * 0.034 * X) / 2;

  Blynk.virtualWrite(V5, distance);
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(4, 0);
  lcd.print("PLEASE");
  lcd.setCursor(1, 1);
  lcd.print("PUT IN TRASH");
  delay(1000);

  if (distance < 5.00){
    lcd.clear();
    lcd.setCursor(1,0);
    lcd.print("TRASH DETECTED");
    delay(1000);

    if (digitalRead(PROXIMITY_PIN) == LOW && analogRead(MQ4_PIN) < 500) {
      lcd.setCursor(2,1);
      lcd.print("METAL TRASH");
      delay(4000);
        
      // Control the stopper motor, open the servo, and insert it into the metal trash can
      controlMetalWasteOn();
      openServo();
      servoMotor.write(100);
      delay(2000);
      controlMetalWasteCenter();
      for (int i = 0; i < 1; i++) {
        delay(1000);
        metalTrashCount++;
      }
      Blynk.virtualWrite(V0, metalTrashCount);

      int proximityValue = digitalRead(PROXIMITY_PIN);
      int analogValue = map(proximityValue, 0, 1023, 0, 255);
      Blynk.virtualWrite(V4, analogValue);
    } else if (digitalRead(PROXIMITY_PIN) == HIGH && analogRead(MQ4_PIN) > 500) {
      lcd.setCursor(2,1);
      lcd.print("ORGANIC TRASH");
      delay(1000);
        
      // Control the stopper motor, open the servo, and put it in the organic waste bin
      controlOrganicWasteOn();
      openServo();
      servoMotor.write(100);
      delay(2000);
      controlOrganicWasteCenter();
      for (int i = 0; i < 1; i++) {
        delay(1000);
        organicTrashCount++;
      }
      Blynk.virtualWrite(V1, organicTrashCount);
    } else if (distance < 5.00 && digitalRead(PROXIMITY_PIN) == HIGH && analogRead(MQ4_PIN) < 500) {
      lcd.setCursor(1,1);
      lcd.print("ANORGANIC TRASH");
      delay(2000);
        
      // Control the stopper motor, open the servo, and put it into the inorganic trash can
      openServo();
      servoMotor.write(100);
      delay(2000);
      
      for (int i = 0; i < 1; i++) {
        delay(1000);
        anorganicTrashCount++;
      }
      Blynk.virtualWrite(V2, anorganicTrashCount);
    }
  } else {
    lcd.clear();
    lcd.setCursor(4, 0);
    lcd.print("NO TRASH");
    lcd.setCursor(4, 1);
    lcd.print("DETECTED");
    delay(1000);
  }
}