/*
                                       ///////////////////////////////////////////////////////
                                       /////////   IoT BOT Test Yazılımları Serisi   /////////
                                       ///////////////////////////////////////////////////////
                                                  RÖLE (Kontrol Edilebilir Anahtar)
*/

//---------------------------------------                HADİ KODLAYALIM...           ------------------------------------------------------

//---------------------------------------   // İLK TANIMLAMALAR VE KÜTÜPHANE EKLEME   ------------------------------------------------------

int ROLE = 14;                                        // Röle'nin bağlı olduğu pini 14. pin olarak tanımladık.
int Buton  = 04;                                      // B1 ve B2 butonlarının bağlı olduğu pini tanımladık. (Analog - Pull DOWN)
int ButonDurum;                                       // 1. Butondan okunan değerleri integer(tam sayı) değer atadık.

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
  Serial.println("Röle Testi...");

  pinMode(ROLE,  OUTPUT);                             // Röle'yi sonuç verdiği için çıkış olarak belirledik.
  pinMode(Buton,  INPUT);                             // Buton1'i veri aldığı için giriş olarak belirledik.
}

//---------------------------------------   // SÜREKLİ ÇALIŞACAK DÖNGÜ İÇİNDEKİ KISIM   ---------------------------------------------------

void loop()
{
  ButonDurum = analogRead(Buton);                     // Butondan sürekli analog olarak değer okuma komutu veriyoruz.

  while (ButonDurum > 500)                              // Bu butonumuz PULL-DOWN olduğu için bastığımızda ARTI sinyali verir.
    // Fakat analog değer okuduğumuz için, arada bulunan dirençlerden dolayı
    // göreceğimiz sonuçlar analog sonuçlar olur.
  {
    Serial.print("Okunan Değer: ");                   // Seri ekrana bilgilendirme mesajı gönderdik.
    Serial.println(ButonDurum);                       // Okuduğumuz değeri seri ekrana bilgilendirme mesajı olarak gönderdik.

    lcd.setCursor(1, 2);                              // İmleci, yazmak istediğimiz koordinata yönlendiriyoruz.
    lcd.print("Analog Deger: ");                      // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
    lcd.print(ButonDurum);                            // Ekranda yazmasını istediğimiz yazıları yolluyoruz.


    Serial.println("Röle Devrede!");          // Seri ekrana bilgilendirme mesajı gönderdik.
    lcd.setCursor(0, 3);                            // İmleci, yazmak istediğimiz koordinata yönlendiriyoruz.
    lcd.print("    Role Devrede!   ");                     // Ekranda yazmasını istediğimiz yazıları yolluyoruz.

    digitalWrite(ROLE, HIGH);

    ButonDurum = analogRead(Buton);                   // Butondan sürekli analog olarak değer okuma komutu veriyoruz.
  }

    Serial.println("Röle Devre Dışı!");       // Seri ekrana bilgilendirme mesajı gönderdik.
    lcd.setCursor(2, 3);                            // İmleci, yazmak istediğimiz koordinata yönlendiriyoruz.
    lcd.print("Role Devre Disi!");                     // Ekranda yazmasını istediğimiz yazıları yolluyoruz.

    yan_son_yazi();
    digitalWrite(ROLE, LOW);
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

  lcd.setCursor(5, 1);
  lcd.print("Role Testi");
  delay(1000);
}

void yan_son_yazi()                                     // Yanıp sönen bilgilendirme mesajını hazırlıyoruz.
{
  i = i + 1;
  if (i < 15)
  {
    lcd.setCursor(4, 2);                                // İmleci, yazmak istediğimiz koordinata yönlendiriyoruz.
    lcd.print("Tusa Basiniz");                    // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
  }
  if (i >= 15)
  {
    lcd.setCursor(1, 2);                                // İmleci, yazmak istediğimiz koordinata yönlendiriyoruz.
    lcd.print("                     ");                 // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
  }
  if (i == 30)
  {
    i = 0;
  }
}
