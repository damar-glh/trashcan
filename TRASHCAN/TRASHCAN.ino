#include <Wire.h>
#include <LCD_I2C.h>
#include <Servo.h>
#include <Stepper.h>

// Definisi pin
#define PROXIMITY_PIN D1 // Pin untuk sensor proximity
#define MQ4_PIN A0       // Pin untuk sensor MQ-4
#define SERVO_PIN D2      // Pin untuk servo motor
#define STEPPER_PIN1 D3   // Pin untuk stepper motor
#define STEPPER_PIN2 D4
#define STEPPER_PIN3 D5
#define STEPPER_PIN4 D6

// Inisialisasi objek
LCD_I2C lcd(0x27, 16, 2);
Servo servoMotor;
Stepper stepperMotor(512, STEPPER_PIN1, STEPPER_PIN3, STEPPER_PIN2, STEPPER_PIN4);

void setup() {
  Serial.begin(115200);
  lcd.begin();
  lcd.backlight();
  pinMode(PROXIMITY_PIN, INPUT);
  pinMode(MQ4_PIN, INPUT);
  servoMotor.attach(SERVO_PIN);
  stepperMotor.setSpeed(10);
}

void loop() {
  lcd.setCursor(4, 0);
  lcd.print("SILAHKAN");
  lcd.setCursor(1, 1);
  lcd.print("MASUKAN SAMPAH");
  delay(1000);
  lcd.clear();
  // if (digitalRead(PROXIMITY_PIN) == HIGH) {
  //   lcd.clear();
  //   lcd.print("Deteksi logam");
  //   delay(1000);
    
  //   // Kendalikan motor stopper, buka servo, dan masukkan ke tong sampah logam
  //   controlMetalWaste();
    
  //   lcd.clear();
  //   lcd.print("Sampah logam masuk");
  //   delay(2000);
  // } else if (analogRead(MQ4_PIN) > 500) {
    
  //   lcd.clear();
  //   lcd.print("Deteksi methane");
  //   delay(1000);
    
  //   // Kendalikan motor stopper, buka servo, dan masukkan ke tong sampah organik
  //   controlOrganicWaste();
    
  //   lcd.clear();
  //   lcd.print("Sampah organik masuk");
  //   delay(2000);
  // } else {
  //   lcd.clear();
  //   lcd.print("Sampah anorganik masuk");
  //   delay(2000);
    
  //   // Kendalikan motor stopper, buka servo, dan masukkan ke tong sampah anorganik
  //   controlInorganicWaste();
    
  //   lcd.clear();
  //   lcd.print("Sampah anorganik masuk");
  //   delay(2000);
  // }

  // // Kembalikan stepper ke posisi awal
  // stepperMotor.step(-512);
  // delay(1000);
}

// void controlMetalWaste() {
//   // Kendalikan motor stopper dan buka servo
//   // Sesuaikan kode ini dengan kebutuhan perangkat keras Anda
// }

// void controlOrganicWaste() {
//   // Kendalikan motor stopper dan buka servo
//   // Sesuaikan kode ini dengan kebutuhan perangkat keras Anda
// }

// void controlInorganicWaste() {
//   // Kendalikan motor stopper dan buka servo
//   // Sesuaikan kode ini dengan kebutuhan perangkat keras Anda
// }
