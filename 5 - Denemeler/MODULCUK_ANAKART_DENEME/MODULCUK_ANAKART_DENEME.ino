
#include <Wire.h>                          
#include <LiquidCrystal_I2C.h>             
LiquidCrystal_I2C lcd(0x27, 20, 4); 

int KIRMIZI = 32;                           
int SARI    = 26;                           
int YESIL   = 25; 

int BUZZER = 12;

void setup() 
{
  Serial.begin(115200);                   
  lcd.println();                        
  lcd.println("     IoT BOT    ");     
  lcd.println("  TRAFIK KONTROL  ");

  

  pinMode(KIRMIZI, OUTPUT);                
  pinMode(SARI,    OUTPUT);                   
  pinMode(YESIL,   OUTPUT);
  pinMode(BUZZER,  OUTPUT);  
 
}

void loop() {
  
     TrafikKontrol(KIRMIZI);
     TrafikKontrol(SARI);
     TrafikKontrol(YESIL);

}

void TrafikKontrol(int a){
  digitalWrite(a, HIGH);                                                                     
  if(a==25){ 
    lcd.setCursor(0, 2);                                                                                 
    lcd.println("Kirmizi Yandi.DURUN");
  }
  else if(a==26){
    lcd.setCursor(0, 2);
    lcd.println("Sari Yandi.DIKKAT");
  }
  else{
    lcd.setCursor(0, 2);
    lcd.println("Yesil Yandi.GECIN");
  }
  digitalWrite(BUZZER, HIGH);               
  delay(500);                              
  digitalWrite(BUZZER, LOW);                
  delay(2000);
  delay(2000);                                                                               
  digitalWrite(a, LOW); 
}
