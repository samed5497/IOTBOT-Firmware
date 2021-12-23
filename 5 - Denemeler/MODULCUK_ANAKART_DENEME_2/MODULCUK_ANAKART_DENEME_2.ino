
#include <Wire.h>                          
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include <Servo.h> 
             
LiquidCrystal_I2C lcd(0x27, 20, 4);                             
DHT dht(27, DHT11);

int Servo_PIN = 27  
int SICAKLIK_C;

Servo Havalandırma;

void setup() {
  Serial.begin(115200);                     
  lcd.println("     IoT BOT    ");       
  lcd.println("  Sicaklik Kontrol  ");

  lcd.init();                              
  lcd.backlight();
  delay(2000);
  dht.begin();                              
  delay(2000);

  Havalandırma.attach(Servo_PIN);
}

void loop() {
  
  SICAKLIK_C = dht.readTemperature();

  lcd.setCursor(2, 1);
  lcd.println("Sıcaklık Degeri: ");

  lcd.setCursor(6, 1);           
  lcd.print(SICAKLIK_C);
  lcd.println(" °C");
  delay(2000);

  if ( SICAKLIK_C > 40 ){
    for (int Motor_ACISI = 0; Motor_ACISI <= 180; Motor_ACISI++)    
  {                                                               
    Havalandırma.write(Motor_ACISI);                             
    lcd.setCursor(0, 1);
    lcd.println("Havalandırma Devrede");
    delay(20);                                                    
  }                                                               

  for (int Motor_ACISI = 180; Motor_ACISI >= 0; Motor_ACISI--)    
  {                                                              
    Havalandırma.write(Motor_ACISI);                             
    lcd.setCursor(0, 1);
    lcd.println("Havalandırma Devrede");                                  
    delay(20);                                                    
  }                                 
  }
  
}
