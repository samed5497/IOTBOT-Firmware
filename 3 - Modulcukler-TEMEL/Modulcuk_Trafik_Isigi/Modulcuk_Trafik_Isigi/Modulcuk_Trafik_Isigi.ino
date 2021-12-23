/*
                                  ///////////////////////////////////////////////////////
                                  /////////   IoT BOT Test Yazılımları Serisi   /////////
                                  ///////////////////////////////////////////////////////
                                                   TRAFİK IŞIĞI MODÜLCÜĞÜ
*/

//---------------------------------------          HADİ KODLAYALIM...       ----------------------------------------------------------------

//---------------------------------------   // İLK TANIMLAMALAR VE KÜTÜPHANE EKLEME   ------------------------------------------------------

#define UYGULAMA "Trafik Isigi Testi"

int i = 0;                                            // Gidip gelen yazının animasyonu için oluşturulan değişken.

#include <Wire.h>                                     // I2C iletişim protokolünü kullanabilmek için gerekli kütüphaneyi ekliyoruz. 
#include <LiquidCrystal_I2C.h>                        // LCD ekran için gerekli olan kütüphaneyi ekliyoruz. 
LiquidCrystal_I2C lcd(0x27, 20, 4);                   // LCD ekranımızın özelliklerini giriyoruz.
                                                      // Bizim ekranımız 20 satır, 4 sütun karakter destekliyor.
int KIRMIZI = 32;                           // Kırmızı ledin bağlı olduğu pini tanımladık.
int SARI    = 26;                           // Sarı ledin bağlı olduğu pini tanımladık.
int YESIL   = 25;                           // Yeşil ledin bağlı olduğu pini tanımladık.

//---------------------------------------   // SADECE İLK AÇILIŞTA BİR KERE ÇALIŞACAK KISIM   ---------------------------------------------

void setup()
{
  Serial.begin(115200);                               // Seri haberleşmeyi "115200" bandında başlattık.
  lcd.init();                                         // LCD ekranı başlatma komutu gönderiyoruz.
  lcd.backlight();                                    // LCD ekranın arka plan aydınlatma ışığını açıyoruz.
  
  giris_animasyon();

  Serial.println("     IoT BOT    ");                 // Seri ekrana bilgilendirme mesajı gönderdik.
  Serial.println(UYGULAMA);

  pinMode(KIRMIZI, OUTPUT);                 // Ledimizi sonuç vediği için çıkış olarak belirledik.
  pinMode(SARI,  OUTPUT);                   // Ledimizi sonuç vediği için çıkış olarak belirledik.
  pinMode(YESIL,  OUTPUT);                  // Ledimizi sonuç vediği için çıkış olarak belirledik.
}

//---------------------------------------   // SÜREKLİ ÇALIŞACAK DÖNGÜ İÇİNDEKİ KISIM   ---------------------------------------------------

void loop()
{
  digitalWrite(KIRMIZI, HIGH);                  // "Dur" komutumuz olan kırmızı ile işe başlayalım.
  Serial.println("Kırmızı Yanıyor. Durunuz.");  // Seri ekrana bilgilendirme mesajı gönderdik.
  lcd.setCursor(0, 3);                                              // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
  lcd.print("DUR                 ");
  delay(2500);                                  // Bekleme süresi ekledik.

  digitalWrite(KIRMIZI, LOW);                   // Kırmızı  ışığı tekrardan söndürüyoruz.
  digitalWrite(SARI, HIGH);                     // Şimdi de "Bekle" komutu olan sarıyı yakalım.
  Serial.println("Sarı Yanıyor. Bekleyiniz.");  // Seri ekranına bilgilendirme mesajı gönderdik.
  lcd.setCursor(0, 3);                                              // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
  lcd.print("       BEKLE        ");    
  delay(1000);                                  // Bekleme süresi ekledik.

  digitalWrite(SARI, LOW);                      // Sarı ışığı kaptıyoruz.
  digitalWrite(YESIL, HIGH);                    // Son olarak "Geç" komutu olan yeşili yakalım.
  Serial.println("Yeşil Yanıyor. Geçiniz.");    // Seri ekranına bilgilendirme mesajı gönderdik.
  lcd.setCursor(0, 3);                                              // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
  lcd.print("                 GEC");
  delay(2000);                                  // Bekleme süresi ekledik.

  digitalWrite(YESIL, LOW);                     // Yeşil ışığı tekrardan söndürüyoruz. 

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

  lcd.setCursor(1, 1);
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
