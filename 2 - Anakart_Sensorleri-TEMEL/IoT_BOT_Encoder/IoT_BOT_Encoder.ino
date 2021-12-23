/*
                                      ///////////////////////////////////////////////////////
                                      /////////   IoT BOT Test Yazılımları Serisi   /////////
                                      ///////////////////////////////////////////////////////
                                                       ENCODER (Adım Sayıcı)
*/

//---------------------------------------                HADİ KODLAYALIM...           ------------------------------------------------------

//---------------------------------------   // İLK TANIMLAMALAR VE KÜTÜPHANE EKLEME   ------------------------------------------------------

#include <Encoder.h>                                  // Encoder kütüphanemizi tanımladık.
Encoder MyEncoder(16, 17);                            // Encoder yön pinini tanımladık.
int Encoder_Buton   = 13;                             // Encoder buton pinini tanımladık.

long YeniPozisyon;                                    // Yönler için en büyük sayılabilecek long veri tipi ile tanımladık.
long EskiPozisyon;                                    // Yönler için en büyük sayılabilecek long veri tipi ile tanımladık.
int  ButonDurumu;                                     // Buton için integer değer atadık.

int i = 0;                                            // Gidip gelen yazının animasyonu için oluşturulan değişken.

#include <Wire.h>                                     // I2C iletişim protokolünü kullanabilmek için gerekli kütüphaneyi ekliyoruz. 
#include <LiquidCrystal_I2C.h>                        // LCD ekran için gerekli olan kütüphaneyi ekliyoruz. 
LiquidCrystal_I2C lcd(0x27, 20, 4);                   // LCD ekranımızın özelliklerini giriyoruz.


//---------------------------------------   // SADECE İLK AÇILIŞTA BİR KERE ÇALIŞACAK KISIM   ---------------------------------------------

void setup()
{
  Serial.begin(115200);                               // Seri haberleşmeyi "115200" bandında başlattık.
  lcd.init();                                         // LCD ekranı başlatma komutu gönderiyoruz.
  lcd.backlight();                                    // LCD ekranın arka plan aydınlatma ışığını açıyoruz.

  giris_animasyon();
  
  Serial.println("     IoT BOT    ");                 // Seri ekrana bilgilendirme mesajı gönderdik.
  Serial.println("Encoder Testi...");

  pinMode(Encoder_Buton,  INPUT);                     // Encoder buton pinini giriş olarak belirledik.
}

//---------------------------------------   // SÜREKLİ ÇALIŞACAK DÖNGÜ İÇİNDEKİ KISIM   ----------------------------------------------------

void loop()
{
  YeniPozisyon = MyEncoder.read();                    // Encoderdan sürekli değer okuma komutu veriyoruz.
  if (YeniPozisyon != EskiPozisyon)                   // En son okuduğumuz değer, önceki değerden farklı ise;
  {
    EskiPozisyon = YeniPozisyon;                      // Yeni değeri, bir sonraki döngüde eski değer olabilmesi için, eski değer olarak atadık.
    Serial.println(EskiPozisyon);                     // En son okunan değeri seri ekranda bize göster.
    
    lcd.setCursor(0, 3);                              // İmleci, yazmak istediğimiz koordinata yönlendiriyoruz.
    lcd.print("   Pozisyon: ");                       // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
    lcd.print(EskiPozisyon);                          // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
    lcd.print("      ");                              // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
  }

  ButonDurumu = digitalRead(Encoder_Buton);           // Butondan sürekli dijital olarak değer okuma komutu veriyoruz.
  if (ButonDurumu == HIGH)                            // Burada bulunan buton PULL-UP olduğu için, bastığımızda 0(EKSİ) olacaktır.
  {
    Serial.println("Butona Basıldı !");               // Butona basılırsa seri ekrana bilgilendirme mesajı gönderdik.
    delay(200); 

    lcd.setCursor(2, 3);                              // İmleci, yazmak istediğimiz koordinata yönlendiriyoruz.
    lcd.print("Butona Basildi !");                    // Ekranda yazmasını istediğimiz yazıları yolluyoruz.

  }

  else
  {
    yan_son_yazi();
  }
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

  lcd.setCursor(1, 1);
  lcd.print("Encoder Okuma Testi");
  delay(1000);
}

void yan_son_yazi()                                     // Yanıp sönen bilgilendirme mesajını hazırlıyoruz.
{
  i = i + 1;
  if (i < 30)
  {
    lcd.setCursor(0, 2);                                // İmleci, yazmak istediğimiz koordinata yönlendiriyoruz.
    lcd.print("Encoder'i Ceviriniz.");                  // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
  }
  if (i >= 30)
  {
    lcd.setCursor(0, 2);                                // İmleci, yazmak istediğimiz koordinata yönlendiriyoruz.
    lcd.print("                     ");                 // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
  }
  if (i == 60)
  {
    i = 0;
  }
}
