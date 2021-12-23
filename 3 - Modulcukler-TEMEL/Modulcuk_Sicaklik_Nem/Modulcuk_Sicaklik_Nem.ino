/*
                                  ///////////////////////////////////////////////////////
                                  /////////   IoT BOT Test Yazılımları Serisi   /////////
                                  ///////////////////////////////////////////////////////
                                                   DHT11 (Sıcaklık ve Nem Sensörü) MODÜLCÜĞÜ
*/

//---------------------------------------          HADİ KODLAYALIM...       ----------------------------------------------------------------

//---------------------------------------   // İLK TANIMLAMALAR VE KÜTÜPHANE EKLEME   ------------------------------------------------------

#define UYGULAMA "Sicaklik & Nem Testi"

int i = 0;                                            // Gidip gelen yazının animasyonu için oluşturulan değişken.

#include <Wire.h>                                     // I2C iletişim protokolünü kullanabilmek için gerekli kütüphaneyi ekliyoruz. 
#include <LiquidCrystal_I2C.h>                        // LCD ekran için gerekli olan kütüphaneyi ekliyoruz. 
LiquidCrystal_I2C lcd(0x27, 20, 4);                   // LCD ekranımızın özelliklerini giriyoruz.
                                                      // Bizim ekranımız 20 satır, 4 sütun karakter destekliyor.

#include "DHT.h"                            // DHT kütüphanemizi tanımladık.
DHT dht(27, DHT11);                         // Uygun olan 25 - 26 - 27 - 32 - 33 numaralı pinlerden birini seçiyoruz.

float NEM;                                  //
float SICAKLIK_C;                           // Modülcükten aldığımız bütün verilere FLOAT veri tipini atadık.
float SICAKLIK_F;                           // Bu veri tipi, diğer veri tiplerine göre daha fazla yer kaplasa da,
float ISI_INDEKS_C;                         // üzerinde en fazla bilgiyi tutabilen veri tipidir.
float ISI_INDEKS_F;                         //

//---------------------------------------   // SADECE İLK AÇILIŞTA BİR KERE ÇALIŞACAK KISIM   ---------------------------------------------

void setup()
{
  Serial.begin(115200);                               // Seri haberleşmeyi "115200" bandında başlattık.
  lcd.init();                                         // LCD ekranı başlatma komutu gönderiyoruz.
  lcd.backlight();                                    // LCD ekranın arka plan aydınlatma ışığını açıyoruz.
  
  giris_animasyon();

  Serial.println("     IoT BOT    ");                 // Seri ekrana bilgilendirme mesajı gönderdik.
  Serial.println(UYGULAMA);

  dht.begin();                              // Sensörümüzü çalıştırma komutu veriyoruz.
  delay(2000);                              // İlk açılışta sensörün ölçüm yapabilmesi için 2 saniye bekletme komutu verdik.
  
}

//---------------------------------------   // SÜREKLİ ÇALIŞACAK DÖNGÜ İÇİNDEKİ KISIM   ---------------------------------------------------

void loop()
{
  NEM        = dht.readHumidity();          // Nem değerini ölçmek için komut yolladık.
  SICAKLIK_C = dht.readTemperature();       // Sıcaklık değerini Santigrat  cinsinden ölçmek için komut yolladık.
  SICAKLIK_F = dht.readTemperature(true);   // Sıcaklık değerini Fahrenheit cinsinden ölçmek için komut yolladık.

  if (isnan(NEM) || isnan(SICAKLIK_C) || isnan(SICAKLIK_F))     // Ölçülen değerleri kontrol ediyoruz. Eğer sensörde
  {                                                             // hata var ise bize bunu seri ekranda bildirme komutu veriyoruz.
    Serial.println("Sensör Okuma Hatası!");                     // Seri ekrana bilgilendirme mesajı gönderdik.
    lcd.setCursor(0, 3);
    lcd.print("Sensor Okuma Hatasi!");
    return;                                                     // Bir defa uyarı gönderdikten sonra tekrar baştan başlama komutu verdik.
  }

  ISI_INDEKS_F = dht.computeHeatIndex(SICAKLIK_F, NEM);         // Ortamdaki nem ve sıcaklığa göre, Fahrenheit cinsinden ısı indeksini hesaplıyoruz.
  ISI_INDEKS_C = dht.computeHeatIndex(SICAKLIK_C, NEM, false);  // Ortamdaki nem ve sıcaklığa göre, Santigrat  cinsinden ısı indeksini hesaplıyoruz.

  Serial.print(" Nem: ");                     //
  Serial.print(NEM);                          //
  Serial.print("%  Sıcaklık: ");              //
  Serial.print(SICAKLIK_C);                   //
  Serial.print("°C / ");                      // Sensörden aldığımız bütün verileri
  Serial.print(SICAKLIK_F);                   //
  Serial.print("°F ");                        // seri ekrana bilgilendirme mesajı olarak gönderdik.
  Serial.print("  Isı İndeksi: ");            //
  Serial.print(ISI_INDEKS_C);                 //
  Serial.print("°C / ");                      //
  Serial.print(ISI_INDEKS_F);                 //
  Serial.println("°F ");                      //

  lcd.setCursor(0, 3);
  lcd.print("Nem: %");
  lcd.print(NEM);
  lcd.setCursor(8, 3);
  lcd.print(" ");
  lcd.setCursor(9, 3);
  lcd.print("Sic: ");
  lcd.print(SICAKLIK_C);
  lcd.setCursor(18, 3);
  lcd.print((char)223);
  lcd.print("C");
  
  delay(2000);                                // Daha kesin bir ölçüm yapabilmek için,
                                              // her okumadan sonra saniyenin onda biri kadar
                                              // bekleme süresi ekledik.



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

  lcd.setCursor(0, 1);
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
