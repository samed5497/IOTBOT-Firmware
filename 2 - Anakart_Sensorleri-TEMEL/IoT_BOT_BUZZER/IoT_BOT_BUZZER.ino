/*
                               ///////////////////////////////////////////////////////
                               /////////   IoT BOT Test Yazılımları Serisi   /////////
                               ///////////////////////////////////////////////////////
                                                   KORNA ( Buzzer )
*/

//---------------------------------------          HADİ KODLAYALIM...       ----------------------------------------------------------------

//---------------------------------------   // İLK TANIMLAMALAR VE KÜTÜPHANE EKLEME   ------------------------------------------------------

int BUZZER = 12;                                      // Buzzer'ın bağlı olduğu pini tanımladık.
int Buton  = 04;                                      // B1 ve B2 butonlarının bağlı olduğu pini tanımladık. (Analog - Pull DOWN)
int ButonDurum;                                       // 1. Butondan okunan değerleri integer(tam sayı) değer atadık.

int i = 0;                                            // Gidip gelen yazının animasyonu için oluşturulan değişken.

#include <Wire.h>                                     // I2C iletişim protokolünü kullanabilmek için gerekli kütüphaneyi ekliyoruz. 
#include <LiquidCrystal_I2C.h>                        // LCD ekran için gerekli olan kütüphaneyi ekliyoruz. 
LiquidCrystal_I2C lcd(0x27, 20, 4);                   // LCD ekranımızın özelliklerini giriyoruz.
                                                      // Bizim ekranımız 20 satır, 4 sütun karakter destekliyor.

//---------------------------------------   // SADECE İLK AÇILIŞTA BİR KERE ÇALIŞACAK KISIM   ---------------------------------------------

void setup()
{
  Serial.begin(115200);                               // Seri haberleşmeyi "115200" bandında başlattık.
  lcd.init();                                         // LCD ekranı başlatma komutu gönderiyoruz.
  lcd.backlight();                                    // LCD ekranın arka plan aydınlatma ışığını açıyoruz.

  giris_animasyon();

  Serial.println("     IoT BOT    ");                 // Seri ekrana bilgilendirme mesajı gönderdik.
  Serial.println("Buzzer Testi...");

  pinMode(BUZZER,  OUTPUT);                           // Buzzer'ı çıkış olarak belirledik.
  pinMode(Buton,  INPUT);                             // Buton1'i veri aldığı için giriş olarak belirledik.
}

//---------------------------------------   // SÜREKLİ ÇALIŞACAK DÖNGÜ İÇİNDEKİ KISIM   ---------------------------------------------------

void loop()
{

  ButonDurum = analogRead(Buton);                     // Butondan sürekli analog olarak değer okuma komutu veriyoruz.

  while (ButonDurum > 0)                              // Bu butonumuz PULL-DOWN olduğu için bastığımızda ARTI sinyali verir.
                                                      // Fakat analog değer okuduğumuz için, arada bulunan dirençlerden dolayı
                                                      // göreceğimiz sonuçlar analog sonuçlar olur.
  {
    Serial.print("Okunan Değer: ");                   // Seri ekrana bilgilendirme mesajı gönderdik.
    Serial.println(ButonDurum);                      // Okuduğumuz değeri seri ekrana bilgilendirme mesajı olarak gönderdik.

    lcd.setCursor(0, 2);                              // İmleci, yazmak istediğimiz koordinata yönlendiriyoruz.
    lcd.print("    Analog Deger    ");                // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
    lcd.setCursor(0, 3);                              // İmleci, yazmak istediğimiz koordinata yönlendiriyoruz.
    lcd.print("   ");                                 // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
    lcd.setCursor(3, 3);                              // İmleci, yazmak istediğimiz koordinata yönlendiriyoruz.
    lcd.print(ButonDurum);                           // Ekranda yazmasını istediğimiz yazıları yolluyoruz.

    if (ButonDurum < 3000)
    {
      lcd.setCursor(7, 3);                            // İmleci, yazmak istediğimiz koordinata yönlendiriyoruz.
      lcd.print(" - Buton 2  ");                      // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
      digitalWrite(BUZZER, 100);
    }
    else
    {
      lcd.setCursor(7, 3);                            // İmleci, yazmak istediğimiz koordinata yönlendiriyoruz.
      lcd.print(" - Buton 1  ");                      // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
      digitalWrite(BUZZER, 255);
    }
    ButonDurum = analogRead(Buton);                 // Butondan sürekli analog olarak değer okuma komutu veriyoruz.
  }

  if ( ButonDurum < 1000 )
  {
    yan_son_yazi();
    digitalWrite(BUZZER, LOW);
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

  lcd.setCursor(3, 1);
  lcd.print("Buzzer Testi...");
  delay(1000);
}

void yan_son_yazi()                                   // Yanıp sönen bilgilendirme mesajını hazırlıyoruz.
{
  lcd.setCursor(0, 2);                                // İmleci, yazmak istediğimiz koordinata yönlendiriyoruz.
  lcd.print("                     ");                 // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
  i = i + 1;
  if (i < 15)
  {
    lcd.setCursor(0, 3);                              // İmleci, yazmak istediğimiz koordinata yönlendiriyoruz.
    lcd.print("Bir Tusa Basiniz..");                 // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
  }
  if (i >= 15)
  {
    lcd.setCursor(0, 3);                              // İmleci, yazmak istediğimiz koordinata yönlendiriyoruz.
    lcd.print("                     ");               // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
  }
  if (i == 30)
  {
    i = 0;
  }
}
