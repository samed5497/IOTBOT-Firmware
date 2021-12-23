/*
                                        ///////////////////////////////////////////////////////
                                        /////////   IoT BOT Test Yazılımları Serisi   /////////
                                        ///////////////////////////////////////////////////////
                                                 JOYSTICK (2 Potansiyometre + 1 Buton)
*/

//---------------------------------------                HADİ KODLAYALIM...               --------------------------------------------------

//---------------------------------------   // İLK TANIMLAMALAR VE KÜTÜPHANE EKLEME   ------------------------------------------------------

int Joystick_X = 34;                                  // Joystick'in X eksenine bağlı olduğu pini tanımladık.
int Joystick_Y = 15;                                  // Joystick'in Y eksenine bağlı olduğu pini tanımladık.
int Buton1     = 35;                                  // Joystick'in butonuna bağlı olduğu pini tanımladık.

int Joystick_XDurum;                                  // Joystick'in X ekseninden okunan değerleri integer(tam sayı) olarak tanımladık.
int Joystick_YDurum;                                  // Joystick'in Y ekseninden okunan değerleri integer(tam sayı) olarak tanımladık.
int Buton1Durum;                                      // Butondan okunan değerleri integer(tam sayı) olarak tanımladık.

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
  Serial.println("Joystick Testi...");

  pinMode(Joystick_X,  INPUT);                        // Joystick X Eksenini giriş olarak belirledik.
  pinMode(Joystick_Y,  INPUT);                        // Joystick Y Eksenini giriş olarak belirledik.
  pinMode(Buton1,      INPUT);                        // Buton1'i giriş olarak belirledik.
}

//---------------------------------------   // SÜREKLİ ÇALIŞACAK DÖNGÜ İÇİNDEKİ KISIM   ----------------------------------------------------

void loop()
{
  Joystick_XDurum = analogRead(Joystick_X);           // X Ekseninden analog olarak değer okuma komutu veriyoruz.
  Serial.print("X Ekseni: ");
  Serial.print(Joystick_XDurum);                      // Okuduğumuz değeri seri ekrana bilgilendirme mesajı olarak gönderdik.
  lcd.setCursor(0, 3);                                // İmleci, yazmak istediğimiz koordinata yönlendiriyoruz.
  lcd.print("X:");                                    // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
  lcd.print(Joystick_XDurum);                         // Ekranda yazmasını istediğimiz yazıları yolluyoruz.

  Joystick_YDurum = analogRead(Joystick_Y);           // Y Ekseninden analog olarak değer okuma komutu veriyoruz.
  Serial.print("Y Ekseni: ");
  Serial.print(Joystick_YDurum);                      // Okuduğumuz değeri seri ekrana bilgilendirme mesajı olarak gönderdik.
  lcd.setCursor(8, 3);                                // İmleci, yazmak istediğimiz koordinata yönlendiriyoruz.
  lcd.print("Y:");                                    // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
  lcd.print(Joystick_YDurum);                         // Ekranda yazmasını istediğimiz yazıları yolluyoruz.

  Buton1Durum = digitalRead(Buton1);                  // Butondan sürekli dijital olarak değer okuma komutu veriyoruz.
  if (Buton1Durum == HIGH)                            // Bu butonumuz PULL-DOWN olduğu için bastığımızda ARTI sinyali verir.
  {
  Serial.print("Joystick'in Butonuna Basıldı!");
  }
  lcd.setCursor(16, 3);                               // İmleci, yazmak istediğimiz koordinata yönlendiriyoruz.
  lcd.print("B:");                                    // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
  lcd.print(Buton1Durum);                             // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
  Serial.println("");                                 // Her okumadan sonra seri ekranda alt tarafa geçmesi için boş metin yolladık.

  delay(100);                                         // Daha kesin bir ölçüm yapabilmek için,
                                                      // her okumadan sonra saniyenin onda biri kadar
                                                      // bekleme süresi ekledik.
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

  lcd.setCursor(0, 1);
  lcd.print("Joystick Okuma Testi");
  delay(1000);
}
