/*
                                  ///////////////////////////////////////////////////////
                                  /////////   IoT BOT Test Yazılımları Serisi   /////////
                                  ///////////////////////////////////////////////////////
                                                   RÖLE MODÜLCÜĞÜ
*/

//---------------------------------------          HADİ KODLAYALIM...       ----------------------------------------------------------------

//---------------------------------------   // İLK TANIMLAMALAR VE KÜTÜPHANE EKLEME   ------------------------------------------------------

#define UYGULAMA "Role Testi"

int i = 0;                                            // Gidip gelen yazının animasyonu için oluşturulan değişken.

#include <Wire.h>                                     // I2C iletişim protokolünü kullanabilmek için gerekli kütüphaneyi ekliyoruz. 
#include <LiquidCrystal_I2C.h>                        // LCD ekran için gerekli olan kütüphaneyi ekliyoruz. 
LiquidCrystal_I2C lcd(0x27, 20, 4);                   // LCD ekranımızın özelliklerini giriyoruz.
                                                      // Bizim ekranımız 20 satır, 4 sütun karakter destekliyor.

int ROLE = 26;                              // Röle'nin bağlı olduğu pini 25 olarak ayarladık.
                                            // Uygun olan 25 - 26 - 27 - 32 - 33 numaralı pinlerden 
                                            // herhangi birine bağlanabilir.
                                            
//---------------------------------------   // SADECE İLK AÇILIŞTA BİR KERE ÇALIŞACAK KISIM   ---------------------------------------------

void setup()
{
  Serial.begin(115200);                               // Seri haberleşmeyi "115200" bandında başlattık.
  lcd.init();                                         // LCD ekranı başlatma komutu gönderiyoruz.
  lcd.backlight();                                    // LCD ekranın arka plan aydınlatma ışığını açıyoruz.
  
  giris_animasyon();

  Serial.println("     IoT BOT    ");                 // Seri ekrana bilgilendirme mesajı gönderdik.
  Serial.println(UYGULAMA);

  pinMode(ROLE,  OUTPUT);                   // Röle'yi sonuç verdiği için çıkış olarak belirledik.
}

//---------------------------------------   // SÜREKLİ ÇALIŞACAK DÖNGÜ İÇİNDEKİ KISIM   ---------------------------------------------------

void loop()
{
  Serial.println("Röle Devrede!");          // Seri ekranına bilgilendirme mesajı gönderdik.
  lcd.setCursor(0, 3);
  lcd.print("    Role Devrede    ");
  digitalWrite(ROLE, HIGH);                 // Röle'yi aktifleştirdik.
  delay(1000);                              // 1 saniye kadar bekleme süresi koyduk.
  Serial.println(" Röle Devre Dışı! ");       // Seri ekranına bilgilendirme mesajı gönderdik.
  lcd.setCursor(0, 3);
  lcd.print("  Role Devre Disi!");
  digitalWrite(ROLE, LOW);                  // Röle'yi pasifleştirdik.
  delay(1000);                              // 1 saniye kadar bekleme süresi koyduk.
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

  lcd.setCursor(5, 1);
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
