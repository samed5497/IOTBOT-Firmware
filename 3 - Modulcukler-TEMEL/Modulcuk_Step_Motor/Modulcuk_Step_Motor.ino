/*
                                  ///////////////////////////////////////////////////////
                                  /////////   IoT BOT Test Yazılımları Serisi   /////////
                                  ///////////////////////////////////////////////////////
                                                   XXXXXXX MODÜLCÜĞÜ
*/

//---------------------------------------          HADİ KODLAYALIM...       ----------------------------------------------------------------

//---------------------------------------   // İLK TANIMLAMALAR VE KÜTÜPHANE EKLEME   ------------------------------------------------------

#define UYGULAMA "Step Motor Testi"

int i = 0;                                            // Gidip gelen yazının animasyonu için oluşturulan değişken.

#include <Wire.h>                                     // I2C iletişim protokolünü kullanabilmek için gerekli kütüphaneyi ekliyoruz. 
#include <LiquidCrystal_I2C.h>                        // LCD ekran için gerekli olan kütüphaneyi ekliyoruz. 
LiquidCrystal_I2C lcd(0x27, 20, 4);                   // LCD ekranımızın özelliklerini giriyoruz. Bizim ekranımız 20 satır, 4 sütun karakter destekliyor.

#include <Stepper.h>                                  // Step Motor Kütüphanemizi Ekliyoruz. 

int ADIM_SAYISI = 48;                                 // Motorun Desteklediği Adım Sayısını Giriyoruz.

Stepper Step_Motorum(ADIM_SAYISI, 26, 33, 32, 27);    // Anakart Üzerinde Motor Sürücüye Bağlı Olan Pinlerimizi Tanımlıyoruz.

//---------------------------------------   // SADECE İLK AÇILIŞTA BİR KERE ÇALIŞACAK KISIM   ---------------------------------------------

void setup()
{
  Serial.begin(115200);                               // Seri haberleşmeyi "115200" bandında başlattık.
  lcd.init();                                         // LCD ekranı başlatma komutu gönderiyoruz.
  lcd.backlight();                                    // LCD ekranın arka plan aydınlatma ışığını açıyoruz.

  giris_animasyon();

  Serial.println("     IoT BOT    ");                 // Seri ekrana bilgilendirme mesajı gönderdik.
  Serial.println(UYGULAMA);

  Step_Motorum.setSpeed(100);                          // Motorun İlerleme Hızını Belirliyoruz.
}

//---------------------------------------   // SÜREKLİ ÇALIŞACAK DÖNGÜ İÇİNDEKİ KISIM   ---------------------------------------------------

void loop()
{
  Serial.println("Saat Yönünde İlerliyor");           // Seri Ekrana Bilgilendirme Mesajı Gönderdik.
  lcd.setCursor(0, 2);                                // İmleci, yazmak istediğimiz koordinata yönlendiriyoruz.
  lcd.print("Saat Yonunde Donuyor");                  // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
  lcd.setCursor(2, 3);                                // İmleci, yazmak istediğimiz koordinata yönlendiriyoruz.
  lcd.print("Ilerleme: 10/ ");                        // Ekranda yazmasını istediğimiz yazıları yolluyoruz.

  for (int i = 0; i < 10; i++)                        // 20 Tur Saat Yönünde Hareket Etmesi İçin Komut Veriyoruz.
  {
    Step_Motorum.step(ADIM_SAYISI);                   // Bu Hareket Miktarı Motorun Desteklediği Adım Sayısı Kadar Olması Gerekiyor.
    lcd.setCursor(16, 3);                             // İmleci, yazmak istediğimiz koordinata yönlendiriyoruz.
    lcd.print(i);                                     // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
    lcd.print("");                                    // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
  }
  delay(500);                                         // Durduğunu Anlamak İçin Hareket Sonunda Yarım Saniye Bekleme Süresi Ekliyoruz.


  Serial.println("Saat Yönünün Tersine İlerliyor");   // Seri Ekrana Bilgilendirme Mesajı Gönderdik.
  lcd.setCursor(0, 2);                                // İmleci, yazmak istediğimiz koordinata yönlendiriyoruz.
  lcd.print(" Ters Yonde Donuyor ");                  // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
  lcd.setCursor(2, 3);                                // İmleci, yazmak istediğimiz koordinata yönlendiriyoruz.
  lcd.print("Ilerleme: 10/ ");                        // Ekranda yazmasını istediğimiz yazıları yolluyoruz.

  for (int i = 0; i < 10; i++)                        // 10 Tur Saat Yönünün Tersinde Hareket Etmesi İçin Komut Veriyoruz.
  {
    Step_Motorum.step(-ADIM_SAYISI);                  // Bu Hareket Miktarı Motorun Desteklediği Adım Sayısı Kadar Olması Gerekiyor.
    lcd.setCursor(16, 3);                             // İmleci, yazmak istediğimiz koordinata yönlendiriyoruz.
    lcd.print(i);                                     // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
    lcd.print("");                                    // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
  }
  delay(500);                                         // Durduğunu Anlamak İçin Hareket Sonunda Yarım Saniye Bekleme Süresi Ekliyoruz.
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

  lcd.setCursor(2, 1);
  lcd.print(UYGULAMA);
  delay(1000);
}

void yan_son_yazi()                                     // Yanıp sönen bilgilendirme mesajını hazırlıyoruz.
{
  lcd.setCursor(1, 2);                                  // İmleci, yazmak istediğimiz koordinata yönlendiriyoruz.
  lcd.print("                     ");                   // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
  i = i + 1;
  if (i < 15)
  {
    lcd.setCursor(1, 3);                                // İmleci, yazmak istediğimiz koordinata yönlendiriyoruz.
    lcd.print("Bir Tusa Basiniz..");                    // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
  }
  if (i >= 15)
  {
    lcd.setCursor(1, 3);                                // İmleci, yazmak istediğimiz koordinata yönlendiriyoruz.
    lcd.print("                     ");                 // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
  }
  if (i == 30)
  {
    i = 0;
  }
}
