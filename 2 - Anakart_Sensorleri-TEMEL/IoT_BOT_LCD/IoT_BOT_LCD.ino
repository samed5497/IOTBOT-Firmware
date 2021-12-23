/*
                                    ///////////////////////////////////////////////////////
                                    /////////   IoT BOT Test Yazılımları Serisi   /////////
                                    ///////////////////////////////////////////////////////
                                                   LCD (I2C 20x04 LCD Ekran)
*/

//---------------------------------------              HADİ KODLAYALIM...           -------------------------------------------------------

//---------------------------------------  // İLK TANIMLAMALAR VE KÜTÜPHANE EKLEME   ------------------------------------------------------

#include <Wire.h>                                     // I2C iletişim protokolünü kullanabilmek için gerekli kütüphaneyi ekliyoruz. 
#include <LiquidCrystal_I2C.h>                        // LCD ekran için gerekli olan kütüphaneyi ekliyoruz. 
LiquidCrystal_I2C lcd(0x27, 20, 4);                   // LCD ekranımızın özelliklerini giriyoruz.
                                                      // Bizim ekranımız 20 satır, 4 sütun karakter destekliyor.

//---------------------------------------  // SADECE İLK AÇILIŞTA BİR KERE ÇALIŞACAK KISIM   ---------------------------------------------

void setup()
{
  Serial.begin(115200);                               // Seri haberleşmeyi "115200" bandında başlattık.
  lcd.init();                                         // LCD ekranı başlatma komutu gönderiyoruz.
  lcd.backlight();                                    // LCD ekranın arka plan aydınlatma ışığını açıyoruz.

  giris_animasyon();

  lcd.init();                                         // LCD ekranı başlatma komutu gönderiyoruz.
  lcd.backlight();                                    // LCD ekranın arka plan aydınlatma ışığını açıyoruz.
}

//---------------------------------------   // SÜREKLİ ÇALIŞACAK DÖNGÜ İÇİNDEKİ KISIM   ---------------------------------------------------
void loop()
{
  giris_animasyon();
                          
  lcd.setCursor(2, 2);                                // İmleci, yazmak istediğimiz koordinata yönlendiriyoruz.
  lcd.print("www.teira3d.com");                       // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
  delay(3000);                                        // Üç saniye bekleme koyuyoruz.
}

void giris_animasyon()                                // Giriş animasyonunu hazırlıyoruz.
{
  lcd.clear();
  delay(500);
  lcd.setCursor(7, 0);
  lcd.print("I");
  delay(400);
  lcd.setCursor(8, 0);
  lcd.print("O");
  delay(400);
  lcd.setCursor(9, 0);
  lcd.print("T");
  delay(400);
  lcd.setCursor(10, 0);
  lcd.print("B");
  delay(400);
  lcd.setCursor(11, 0);
  lcd.print("O");
  delay(400);
  lcd.setCursor(12, 0);
  lcd.print("T");
  delay(600);

  lcd.setCursor(6, 0);
  lcd.print("-");
  lcd.setCursor(13, 0);
  lcd.print("-");

  delay(1000);
}
