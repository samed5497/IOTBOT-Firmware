/*
                                  ///////////////////////////////////////////////////////
                                  /////////   IoT BOT Test Yazılımları Serisi   /////////
                                  ///////////////////////////////////////////////////////
                                                   DC MOTOR MODÜLCÜĞÜ
*/

//---------------------------------------          HADİ KODLAYALIM...       ----------------------------------------------------------------

//---------------------------------------   // İLK TANIMLAMALAR VE KÜTÜPHANE EKLEME   ------------------------------------------------------

#define UYGULAMA "DC Motor Testi"

int i = 0;                                            // Gidip gelen yazının animasyonu için oluşturulan değişken.

#include <Wire.h>                                     // I2C iletişim protokolünü kullanabilmek için gerekli kütüphaneyi ekliyoruz. 
#include <LiquidCrystal_I2C.h>                        // LCD ekran için gerekli olan kütüphaneyi ekliyoruz. 
LiquidCrystal_I2C lcd(0x27, 20, 4);                   // LCD ekranımızın özelliklerini giriyoruz.
                                                      // Bizim ekranımız 20 satır, 4 sütun karakter destekliyor.
int motorPin1  = 26;                                  // Uygun olan 26 - 27 - 32 - 33 numaralı pinlerden
                                                      // herhangi birine bağlanabilir.
int motorPin2  = 27;                                  // Motor sürücüye giden 1. ve 2. sinyal pinini tanımlıyoruz.

//---------------------------------------   // SADECE İLK AÇILIŞTA BİR KERE ÇALIŞACAK KISIM   ---------------------------------------------

void setup()
{
  Serial.begin(115200);                               // Seri haberleşmeyi "115200" bandında başlattık.
  lcd.init();                                         // LCD ekranı başlatma komutu gönderiyoruz.
  lcd.backlight();                                    // LCD ekranın arka plan aydınlatma ışığını açıyoruz.
  
  giris_animasyon();

  Serial.println("     IoT BOT    ");                 // Seri ekrana bilgilendirme mesajı gönderdik.
  Serial.println(UYGULAMA);

  pinMode(motorPin1, OUTPUT);                         // Motor pinimizi bir sonuç verdiği için çıkış olarak ayarladık.
  pinMode(motorPin2, OUTPUT);                         // Motor pinimizi bir sonuç verdiği için çıkış olarak ayarladık.
  
}

//---------------------------------------   // SÜREKLİ ÇALIŞACAK DÖNGÜ İÇİNDEKİ KISIM   ---------------------------------------------------

void loop()
{
  Serial.println("Sağa Dönüyor..");
  lcd.setCursor(0, 3);
  lcd.print("  Saga Donuyor..  ");
  digitalWrite(motorPin1, HIGH);            // Motorumuzun birinci pinine güç vererek devreye sokuyoruz.
  digitalWrite(motorPin2, LOW);             // Motorumuzun diğer pinini devre dışı bırakarak bir taraftan ilerlemesini sağlıyoruz.
  delay(2000);

  Serial.println("Duruyor!");
  lcd.setCursor(0, 3);
  lcd.print("      DURUYOR       ");
  digitalWrite(motorPin1, LOW);             // Motorları durduruyoruz.
  digitalWrite(motorPin2, LOW);             // Motorları durduruyoruz.
  delay(3000);

  Serial.println("Sola Dönüyor..");
  lcd.setCursor(0, 3);
  lcd.print("  Sola Donuyor..  ");
  digitalWrite(motorPin1, LOW);             // Motorumuzun birinci pinini devre dışı bırakıyoruz.
  digitalWrite(motorPin2, HIGH);            // Motorumuzun diğer pinini devreye sokarak bir taraftan ilerlemesini sağlıyoruz.
  delay(2000);

  Serial.println("Duruyor!");
  lcd.setCursor(0, 3);
  lcd.print("      DURUYOR       ");
  digitalWrite(motorPin1, LOW);             // Motorları durduruyoruz.
  digitalWrite(motorPin2, LOW);             // Motorları durduruyoruz.
  delay(3000);                              

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

  lcd.setCursor(3, 1);
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
