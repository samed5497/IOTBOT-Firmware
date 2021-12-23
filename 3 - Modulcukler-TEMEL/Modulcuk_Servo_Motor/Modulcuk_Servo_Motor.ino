/*
                                  ///////////////////////////////////////////////////////
                                  /////////   IoT BOT Test Yazılımları Serisi   /////////
                                  ///////////////////////////////////////////////////////
                                                   Servo Motor MODÜLCÜĞÜ
*/

//---------------------------------------          HADİ KODLAYALIM...       ----------------------------------------------------------------

//---------------------------------------   // İLK TANIMLAMALAR VE KÜTÜPHANE EKLEME   ------------------------------------------------------

#define UYGULAMA "Servo Motor Testi"

int i = 0;                                            // Gidip gelen yazının animasyonu için oluşturulan değişken.

#include <Wire.h>                                     // I2C iletişim protokolünü kullanabilmek için gerekli kütüphaneyi ekliyoruz. 
#include <LiquidCrystal_I2C.h>                        // LCD ekran için gerekli olan kütüphaneyi ekliyoruz. 
LiquidCrystal_I2C lcd(0x27, 20, 4);                   // LCD ekranımızın özelliklerini giriyoruz.
                                                      // Bizim ekranımız 20 satır, 4 sütun karakter destekliyor.

#include <ESP32Servo.h>                     // Motor Kontrolü İçin Gerekli Olan Kütüphaneyi Çağırıyoruz. 

int Servo_PIN = 26;                         // Motorun Bağlı Olduğu Pini 26. Pin Tanımladık.
                                            // 25 - 26 - 27 - 32 - 33 Numaralı Pinlerden
                                            // Herhangi Birine Bağlanabilir.

Servo Servo_Motorum;                        // Servo Motorumuza Bir İsim Veriyoruz. Biz "Servo_Motorum" Dedik.

//---------------------------------------   // SADECE İLK AÇILIŞTA BİR KERE ÇALIŞACAK KISIM   ---------------------------------------------

void setup()
{
  Serial.begin(115200);                               // Seri haberleşmeyi "115200" bandında başlattık.
  lcd.init();                                         // LCD ekranı başlatma komutu gönderiyoruz.
  lcd.backlight();                                    // LCD ekranın arka plan aydınlatma ışığını açıyoruz.
  
  giris_animasyon();

  Serial.println("     IoT BOT    ");                 // Seri ekrana bilgilendirme mesajı gönderdik.
  Serial.println(UYGULAMA);

  Servo_Motorum.attach(Servo_PIN);          // İsimlendiğimiz Motoru, Tanımladığımız Pine Bağladık.
  
}

//---------------------------------------   // SÜREKLİ ÇALIŞACAK DÖNGÜ İÇİNDEKİ KISIM   ---------------------------------------------------

void loop()
{
for (int Motor_ACISI = 0; Motor_ACISI <= 180; Motor_ACISI++)    // Servo Motorumuzu 0 Dereceden 180 Dereceye,
  {                                                               // Birer Açı Şeklinde Hareket Ettiriyoruz.
    Servo_Motorum.write(Motor_ACISI);                             // Motorumuzun Hareketi Yapması İçin Onay Veriyoruz.
    Serial.print("Motor Açısı: ");                                // Bunu Seri Ekrana Bilgi Mesajı Olarak Gönder Komutu Veriyoruz.
    lcd.setCursor(2, 3);
    lcd.print("Motor Acisi: ");
    lcd.print(Motor_ACISI);
    lcd.print((char)223);
    Serial.println(Motor_ACISI);                                  // Bunu Seri Ekrana Bilgi Mesajı Olarak Gönder Komutu Veriyoruz.
    delay(20);                                                    // Her Açı Hareketinden Sonra, Herhangi Bir Sıkışma
  }                                                               // Olmaması İçin Minik Bir Bekleme Süresi Koyuyoruz.

  for (int Motor_ACISI = 180; Motor_ACISI >= 0; Motor_ACISI--)    // Servo Motorumuzu 180 Dereceden 0 Dereceye,
  {                                                               // Birer Açı Şeklinde Hareket Ettiriyoruz.
    Servo_Motorum.write(Motor_ACISI);                             // Motorumuzun Hareketi Yapması İçin Onay Veriyoruz.
    Serial.print("Motor Açısı: ");                                // Bunu Seri Ekrana Bilgi Mesajı Olarak Gönder Komutu Veriyoruz.
    lcd.setCursor(2, 3);
    lcd.print("Motor Acisi: ");
    lcd.print(Motor_ACISI);
    lcd.print((char)223);
    Serial.println(Motor_ACISI);                                  // Bunu Seri Ekrana Bilgi Mesajı Olarak Gönder Komutu Veriyoruz.
        lcd.print(" ");
    delay(20);                                                    // Her Açı Hareketinden Sonra, Herhangi Bir Sıkışma
  }       
}


void giris_animasyon()                               // Giriş animasyonunu hazırlıyoruz.
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

  lcd.setCursor(2, 1);
  lcd.print(UYGULAMA);
  delay(1000);
}

void yan_son_yazi()                                    // Yanıp sönen bilgilendirme mesajını hazırlıyoruz. 
{
  lcd.setCursor(1, 2);                                // İmleci, yazmak istediğimiz koordinata yönlendiriyoruz.
    lcd.print("                     ");               // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
    i = i + 1;
    if (i < 15)
    {
      lcd.setCursor(1, 3);                            // İmleci, yazmak istediğimiz koordinata yönlendiriyoruz.
      lcd.print("Bir Tusa Basiniz..");                // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
    }
    if (i >= 15)
    {
      lcd.setCursor(1, 3);                            // İmleci, yazmak istediğimiz koordinata yönlendiriyoruz.
      lcd.print("                     ");             // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
    }
    if (i == 30)
    {
      i = 0;
    }
}
