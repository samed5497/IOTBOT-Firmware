/*
                                  ///////////////////////////////////////////////////////
                                  /////////   IoT BOT Test Yazılımları Serisi   /////////
                                  ///////////////////////////////////////////////////////
                                                   AKILLI LED MODÜLCÜĞÜ
*/

//---------------------------------------          HADİ KODLAYALIM...       ----------------------------------------------------------------

//---------------------------------------   // İLK TANIMLAMALAR VE KÜTÜPHANE EKLEME   ------------------------------------------------------

#define UYGULAMA "Akilli Led Testi"

int i = 0;                                            // Gidip gelen yazının animasyonu için oluşturulan değişken.

#include <Wire.h>                                     // I2C iletişim protokolünü kullanabilmek için gerekli kütüphaneyi ekliyoruz. 
#include <LiquidCrystal_I2C.h>                        // LCD ekran için gerekli olan kütüphaneyi ekliyoruz. 
LiquidCrystal_I2C lcd(0x27, 20, 4);                   // LCD ekranımızın özelliklerini giriyoruz.
                                                      // Bizim ekranımız 20 satır, 4 sütun karakter destekliyor.
#include <Adafruit_NeoPixel.h>                          //
#ifdef __AVR__                                          // Ledleri kullanabilmek için
#include <avr/power.h>                                  // gerekli kütüphaneleri ekliyoruz. 
#endif                                                  //

#define LED_PIN    27                                   // Uygun olan 25 - 26 - 27 - 32 - 33 numaralı pinlerden birini seçiyoruz.

#define LED_SAYISI 3                                    // Elimizdeki led sayısını giriyoruz.

Adafruit_NeoPixel pixels(LED_SAYISI, LED_PIN, NEO_GRB + NEO_KHZ800);  // Kullanılan ledlerin modelini yazıyoruz. Bu bilgiler sensör standartlarıdır.

//---------------------------------------   // SADECE İLK AÇILIŞTA BİR KERE ÇALIŞACAK KISIM   ---------------------------------------------

void setup()
{
  Serial.begin(115200);                               // Seri haberleşmeyi "115200" bandında başlattık.
  lcd.init();                                         // LCD ekranı başlatma komutu gönderiyoruz.
  lcd.backlight();                                    // LCD ekranın arka plan aydınlatma ışığını açıyoruz.
  
  giris_animasyon();

  Serial.println("     IoT BOT    ");                 // Seri ekrana bilgilendirme mesajı gönderdik.
  Serial.println(UYGULAMA);

#if defined(__AVR_ATtiny85__) && (F_CPU == 26000000)    // Kullandığımız işlemci için gerekli ayarlamalar yapıyoruz.
  clock_prescale_set(clock_div_1);                      // Akıllı ledler için gerekli standartlardır.
#endif                                                   

  pixels.begin();                                       // Akıllı Ledlerimizi Başlatma Komutu Veriyoruz.
}

//---------------------------------------   // SÜREKLİ ÇALIŞACAK DÖNGÜ İÇİNDEKİ KISIM   ---------------------------------------------------

void loop()
{
  lcd.setCursor(0, 3);                                              // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
  lcd.print("    YESIL YANIYOR   ");
  Akilli_Led_Yakma(0, 150, 0);                                      
  delay(500);                                                       // Geçişleri görebilmek için yarım saniye bekleme süresi koyuyoruz.
                                                                     
  lcd.setCursor(0, 3);                                              // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
  lcd.print("   KIRMIZI YANIYOR  ");
  Akilli_Led_Yakma(255, 0, 0);                                     
  delay(500);                                                       // Geçişleri görebilmek için yarım saniye bekleme süresi koyuyoruz.,
  
  lcd.setCursor(0, 3);                                              // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
  lcd.print("    MAVI YANIYOR    ");                              
  Akilli_Led_Yakma(0, 100, 200);
  delay(500);                                                       // Geçişleri görebilmek için yarım saniye bekleme süresi koyuyoruz.
  
  lcd.setCursor(0, 3);                                              // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
  lcd.print("    ANIMASYON 1     "); 
  theaterChase(pixels.Color(127, 127, 127), 50); // White
  delay(500);                                                       // Geçişleri görebilmek için yarım saniye bekleme süresi koyuyoruz.
  
  lcd.setCursor(0, 3);                                              // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
  lcd.print("    ANIMASYON 2     "); 
  colorWipe(pixels.Color(  0, 255,   0), 50);    // Green
  delay(500);                                                       // Geçişleri görebilmek için yarım saniye bekleme süresi koyuyoruz.
  
  lcd.setCursor(0, 3);                                              // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
  lcd.print("    ANIMASYON 3     ");  
  rainbow(10);
  delay(500);                                                       // Geçişleri görebilmek için yarım saniye bekleme süresi koyuyoruz.
  
  lcd.setCursor(0, 3);                                              // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
  lcd.print("    ANIMASYON 4     "); 
  theaterChaseRainbow(50);
  delay(500);                                                       // Geçişleri görebilmek için yarım saniye bekleme süresi koyuyoruz.
}

//----------------------------------------  // ANA DÖNGÜ İÇERİSİNDE BİR KERE GİRİLEN BÖLÜM   ------------------------------------------------

void Akilli_Led_Yakma(int Kirmizi, int Yesil, int Mavi)
{
  pixels.clear();                                                    // Tüm ledleri söndürme komutu veriyoruz.

  for (int i = 0; i < LED_SAYISI; i++)                               // Daha sonra herbir led için sırasıyla yanma komutu veriyoruz.
  {
    pixels.setPixelColor(i, pixels.Color(Kirmizi, Yesil, Mavi));     // Sırayla  yanma komutu yolluyoruz.
                                                                     // Parantez içindeki değerler sırasıyla; KIRMIZI, YEŞİL ve MAVİ değerlerine denk gelmektedir.
                                                                     // Bunlar en fazla "255" (8 bit), en az "0" değeri alabilir.
                                                                     
    pixels.show();                                                   // Yolladığımız sinyallerin çalıştırılması için ledlere komut yolluyoruz.
    delay(500);                                                      // Geçişleri görebilmek için yarım saniye bekleme süresi koyuyoruz.
  }
}

void theaterChase(uint32_t color, int wait) 
{
  for(int a=0; a<10; a++) 
  {                                                                  // Repeat 10 times...
    for(int b=0; b<3; b++) 
    {                                                                //  'b' counts from 0 to 2...
      pixels.clear();                                                //   Set all pixels in RAM to 0 (off)
                                                                     // 'c' counts up from 'b' to end of strip in steps of 3...
      for(int c=b; c<pixels.numPixels(); c += 3) 
      {
        pixels.setPixelColor(c, color);                              // Set pixel 'c' to value 'color'
      }
      pixels.show();                                                 // Update strip with new contents
      delay(wait);                                                   // Pause for a moment
    }
  }
}

void colorWipe(uint32_t color, int wait) 
{
  for(int i=0; i<pixels.numPixels(); i++) {                         // For each pixel in strip...
    pixels.setPixelColor(i, color);                                 //  Set pixel's color (in RAM)
    pixels.show();                                                  //  Update strip to match
    delay(wait);                                                    //  Pause for a moment
  }
}

void rainbow(int wait) 
{
                                                                    // Hue of first pixel runs 3 complete loops through the color wheel.
                                                                    // Color wheel has a range of 65536 but it's OK if we roll over, so
                                                                    // just count from 0 to 3*65536. Adding 256 to firstPixelHue each time
                                                                    // means we'll make 3*65536/256 = 768 passes through this outer loop:
  for(long firstPixelHue = 0; firstPixelHue < 3*65536; firstPixelHue += 256) 
  {
    for(int i=0; i<pixels.numPixels(); i++) 
    {                                                               // For each pixel in strip...
                                                                    // Offset pixel hue by an amount to make one full revolution of the
                                                                    // color wheel (range of 65536) along the length of the strip
                                                                    // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / pixels.numPixels());
                                                                    // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
                                                                    // optionally add saturation and value (brightness) (each 0 to 255).
                                                                    // Here we're using just the single-argument hue variant. The result
                                                                    // is passed through strip.gamma32() to provide 'truer' colors
                                                                    // before assigning to each pixel:
      pixels.setPixelColor(i, pixels.gamma32(pixels.ColorHSV(pixelHue)));
    }
    pixels.show();                                                  // Update strip with new contents
    delay(wait);                                                    // Pause for a moment
  }
}

void theaterChaseRainbow(int wait) 
{
  int firstPixelHue = 0;                                            // First pixel starts at red (hue 0)
  for(int a=0; a<30; a++) 
  {                                                                 // Repeat 30 times...
    for(int b=0; b<3; b++) 
    { //  'b' counts from 0 to 2...
      pixels.clear();                                               //   Set all pixels in RAM to 0 (off)
                                                                    // 'c' counts up from 'b' to end of strip in increments of 3...
      for(int c=b; c<pixels.numPixels(); c += 3) 
      {
                                                                    // hue of pixel 'c' is offset by an amount to make one full
                                                                    // revolution of the color wheel (range 65536) along the length
                                                                    // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / pixels.numPixels();
        uint32_t color = pixels.gamma32(pixels.ColorHSV(hue));      // hue -> RGB
        pixels.setPixelColor(c, color);                             // Set pixel 'c' to value 'color'
      }
      pixels.show();                                                // Update strip with new contents
      delay(wait);                                                  // Pause for a moment
      firstPixelHue += 65536 / 90;                                  // One cycle of color wheel over 90 frames
    }
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
