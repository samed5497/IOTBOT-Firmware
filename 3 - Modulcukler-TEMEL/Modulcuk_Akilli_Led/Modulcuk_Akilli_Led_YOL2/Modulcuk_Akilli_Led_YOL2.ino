/*
                                        ///////////////////////////////////////////////////////
                                        /////////   IoT BOT Test Yazılımları Serisi   /////////
                                        //////////////   MODÜLCÜK TESTLERİ   //////////////////
                                                     NEOPİXEL (Akıllı Ledler)
*/

//---------------------------------------        // HAYDİ ORTAMI RENKLENDİRELİM!       -----------------------------------------------------

//---------------------------------------   // İLK TANIMLAMALAR VE KÜTÜPHANE EKLEME   ------------------------------------------------------

#include <Adafruit_NeoPixel.h>                          //
#ifdef __AVR__                                          // Ledleri kullanabilmek için
#include <avr/power.h>                                  // gerekli kütüphaneleri ekliyoruz. 
#endif                                                  //

#define LED_PIN    26                                   // Uygun olan 25 - 26 - 27 - 32 - 33 numaralı pinlerden birini seçiyoruz.

#define LED_SAYISI 3                                    // Elimizdeki led sayısını giriyoruz.

Adafruit_NeoPixel pixels(LED_SAYISI, LED_PIN, NEO_GRB + NEO_KHZ800);  // Kullanılan ledlerin modelini yazıyoruz. Bu bilgiler sensör standartlarıdır.


//---------------------------------------   // SADECE İLK AÇILIŞTA BİR KERE ÇALIŞACAK KISIM   ---------------------------------------------

void setup()
{
  Serial.begin(115200);                                 // Seri haberleşmeyi "115200" bandında başlattık.
  Serial.println("     IoT BOT    ");                   // Seri ekrana bilgilendirme mesajı gönderdik.
  Serial.println("Akıllı Led Testi..");

#if defined(__AVR_ATtiny85__) && (F_CPU == 26000000)    // Kullandığımız işlemci için gerekli ayarlamalar yapıyoruz.
  clock_prescale_set(clock_div_1);                      // Akıllı ledler için gerekli standartlardır.
#endif                                                   

  pixels.begin();                                       // Akıllı ledlerimizi başlatma komutu veriyoruz.
}

//---------------------------------------   // SÜREKLİ ÇALIŞACAK DÖNGÜ İÇİNDEKİ KISIM   ---------------------------------------------------

void loop()
{
  pixels.clear();                                       // Tüm ledleri söndürme komutu veriyoruz.

  for (int i = 0; i < LED_SAYISI; i++)                  // Daha sonra herbir led için sırasıyla yanma komutu veriyoruz.
  {
    pixels.setPixelColor(i, pixels.Color(0, 150, 0));   // İlk önce sırayla yeşil yanma komutu yolluyoruz.
    //                                  (K,  Y,  M)     // Parantez içindeki değerler sırasıyla; KIRMIZI, YEŞİL ve MAVİ değerlerine denk gelmektedir.
    //                                                  // Bunlar en fazla "255" (8 bit), en az "0" değeri alabilir.
    pixels.show();                                      // Yolladığımız sinyallerin çalıştırılması için ledlere komut yolluyoruz.
    Serial.println("Yeşil Yanıyor..");                  // Seri ekrana bilgilendirme mesajı gönderdik.
    delay(500);                                         // Geçişleri görebilmek için yarım saniye bekleme süresi koyuyoruz.
  }

  pixels.clear();                                       // Tüm ledleri söndürme komutu veriyoruz.

  for (int i = 0; i < LED_SAYISI; i++)                  // Daha sonra herbir led için sırasıyla yanma komutu veriyoruz.
  {
    pixels.setPixelColor(i, pixels.Color(255, 0, 0));   // Sırayla kırmızı yanma komutu yolluyoruz.
    //                                  (K,  Y,  M)     // Parantez içindeki değerler sırasıyla; KIRMIZI, YEŞİL ve MAVİ değerlerine denk gelmektedir.
    //                                                  // Bunlar en fazla "255" (8 bit), en az "0" değeri alabilir.
    pixels.show();                                      // Yolladığımız sinyallerin çalıştırılması için ledlere komut yolluyoruz.
    Serial.println("Kırmızı Yanıyor..");                // Seri Ekrana Bilgilendirme Mesajı Gönderdik.
    delay(500);                                         // Geçişleri görebilmek için yarım saniye bekleme süresi koyuyoruz.
  }

  pixels.clear();                                       // Tüm ledleri söndürme komutu veriyoruz.

  for (int i = 0; i < LED_SAYISI; i++)                  // Daha sonra herbir led için sırasıyla yanma komutu veriyoruz.
  {
    pixels.setPixelColor(i, pixels.Color(0, 100, 200)); // Sırayla  Yanma Komutu Yolluyoruz.
    //                                  (K,  Y,  M)     // Parantez içindeki değerler sırasıyla; KIRMIZI, YEŞİL ve MAVİ değerlerine denk gelmektedir.
    //                                                  // Bunlar en fazla "255" (8 bit), en az "0" değeri alabilir.
    pixels.show();                                      // Yolladığımız sinyallerin çalıştırılması için ledlere komut yolluyoruz.
    Serial.println("Mavi Yanıyor..");                   // Seri Ekrana Bilgilendirme Mesajı Gönderdik.
    delay(500);                                         // Geçişleri görebilmek için yarım saniye bekleme süresi koyuyoruz.
  }

  pixels.clear();                                       // Tüm ledleri söndürme komutu veriyoruz.
  Serial.println("BAŞTAN BAŞLANILIYOR.");               // Seri ekrana bilgilendirme mesajı gönderdik.
  
  delay(500);                                           // Döngünün başa sardığını anlamak için
                                                        // küçük bir bekleme süresi koyuyoruz.
}
