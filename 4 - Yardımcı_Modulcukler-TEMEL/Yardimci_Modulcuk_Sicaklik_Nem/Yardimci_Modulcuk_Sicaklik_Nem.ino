/*
                                  ///////////////////////////////////////////////////////
                                  /////////   IoT BOT Test Yazılımları Serisi   /////////
                                  ///////////////////////////////////////////////////////
                                                  YARDIMCI MODÜLCÜK
*/

//---------------------------------------          HADİ KODLAYALIM...       ----------------------------------------------------------------

/*
  NOT: 
        1 - Karta yükleme yapmadan önce kart  yöneticisinden işlemciyi "ESP8266 Generic Module" seçiyoruz.
        2 - Kartın üzerindeki "BOOT" tuşuna basılı tutarken "RESET" tuşuna bir kere basıp butonları bırakıyoruz ve cihazımı yükleme moduna alıyoruz.
        3 - BOOT modunda bekleyen kartımızın uygun yükleme portunu seçtikten sonra yükle butonuna basıyoruz.
        4 - Yükleme işlemi bittikten sonra reset tuşuna basarak işlemcimizi yükleme modundan çıkartarak kodumuzun çalışmasını sağlıyoruz.
*/

//---------------------------------------   // İLK TANIMLAMALAR VE KÜTÜPHANE EKLEME   ------------------------------------------------------

#define UYGULAMA "YARDIMCI MODULCUK - Sicaklik & Nem Testi"
                                   

#include "DHT.h"                                                // DHT kütüphanemizi tanımladık.
DHT dht(4, DHT11);                                              // Uygun olan 4 - 5 - 12 - 13 - 14 Numaralı Pinlerden Herhangi Birine Bağlanabilir.

float NEM;                                                      //
float SICAKLIK_C;                                               // Modülcükten aldığımız bütün verilere FLOAT veri tipini atadık.
float SICAKLIK_F;                                               // Bu veri tipi, diğer veri tiplerine göre daha fazla yer kaplasa da,
float ISI_INDEKS_C;                                             // üzerinde en fazla bilgiyi tutabilen veri tipidir.
float ISI_INDEKS_F;                                             //

//---------------------------------------   // SADECE İLK AÇILIŞTA BİR KERE ÇALIŞACAK KISIM   ---------------------------------------------

void setup()
{
  Serial.begin(115200);                                         // Seri haberleşmeyi "115200" bandında başlattık.
 
  Serial.println("     IoT BOT    ");                           // Seri ekrana bilgilendirme mesajı gönderdik.
  Serial.println(UYGULAMA);

  dht.begin();                                                  // Sensörümüzü çalıştırma komutu veriyoruz.
  delay(2000);                                                  // İlk açılışta sensörün ölçüm yapabilmesi için 2 saniye bekletme komutu verdik.
}

//---------------------------------------   // SÜREKLİ ÇALIŞACAK DÖNGÜ İÇİNDEKİ KISIM   ---------------------------------------------------

void loop()
{
  NEM        = dht.readHumidity();                              // Nem değerini ölçmek için komut yolladık.
  SICAKLIK_C = dht.readTemperature();                           // Sıcaklık değerini Santigrat  cinsinden ölçmek için komut yolladık.
  SICAKLIK_F = dht.readTemperature(true);                       // Sıcaklık değerini Fahrenheit cinsinden ölçmek için komut yolladık.

  if (isnan(NEM) || isnan(SICAKLIK_C) || isnan(SICAKLIK_F))     // Ölçülen değerleri kontrol ediyoruz. Eğer sensörde
  {                                                             // hata var ise bize bunu seri ekranda bildirme komutu veriyoruz.
    Serial.println("Sensör Okuma Hatası!");                     // Seri ekrana bilgilendirme mesajı gönderdik.
    return;                                                     // Bir defa uyarı gönderdikten sonra tekrar baştan başlama komutu verdik.
  }

  ISI_INDEKS_F = dht.computeHeatIndex(SICAKLIK_F, NEM);         // Ortamdaki nem ve sıcaklığa göre, Fahrenheit cinsinden ısı indeksini hesaplıyoruz.
  ISI_INDEKS_C = dht.computeHeatIndex(SICAKLIK_C, NEM, false);  // Ortamdaki nem ve sıcaklığa göre, Santigrat  cinsinden ısı indeksini hesaplıyoruz.

  Serial.print(" Nem: ");                                       //
  Serial.print(NEM);                                            //
  Serial.print("%  Sıcaklık: ");                                //
  Serial.print(SICAKLIK_C);                                     //
  Serial.print("°C / ");                                        // Sensörden aldığımız bütün verileri
  Serial.print(SICAKLIK_F);                                     //
  Serial.print("°F ");                                          // seri ekrana bilgilendirme mesajı olarak gönderdik.
  Serial.print("  Isı İndeksi: ");                              //
  Serial.print(ISI_INDEKS_C);                                   //
  Serial.print("°C / ");                                        //
  Serial.print(ISI_INDEKS_F);                                   //
  Serial.println("°F ");                                        //

  delay(2000);                                                  // Daha kesin bir ölçüm yapabilmek için, her okumadan sonra saniyenin onda biri kadar bekleme süresi ekledik.
}
