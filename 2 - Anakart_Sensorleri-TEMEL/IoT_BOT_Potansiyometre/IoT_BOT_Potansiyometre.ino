/* 
                                    ///////////////////////////////////////////////////////
                                    /////////   IoT BOT Test Yazılımları Serisi   /////////
                                    ///////////////////////////////////////////////////////
                                             POTANSIYOMETRE (Ayarlanabilir Direnç)
*/ 

//---------------------------------------                HADİ KODLAYALIM...           ------------------------------------------------------

//---------------------------------------   // İLK TANIMLAMALAR VE KÜTÜPHANE EKLEME   ------------------------------------------------------

int PotPini = 36;                                     // Potansiyometremizin bağlı olduğu pini tanımladık.
int PotDegeri;                                        // Potansiyometreden okunan değerleri integer(Tam sayı) olarak tanımladık.

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
  Serial.println("Potansiyometre Testi...");
  
  pinMode(PotPini,  INPUT);                           // Potansiyometreyi veri aldığı için giriş olarak belirledik.
}

//---------------------------------------   // SÜREKLİ ÇALIŞACAK DÖNGÜ İÇİNDEKİ KISIM   ----------------------------------------------------

void loop()
{
  PotDegeri = analogRead(PotPini);          // Encoderdan sürekli analog olarak değer okuma komutu veriyoruz.
  
  Serial.print("Okunan Değer: ");                     // Seri ekrana bilgilendirme mesajı gönderdik.
  Serial.println(PotDegeri);                          // Okuduğumuz değeri seri ekrana bilgilendirme mesajı olarak gönderdik.

  lcd.setCursor(2, 3);                                // İmleci, yazmak istediğimiz koordinata yönlendiriyoruz.
  lcd.print("POT Degeri: ");                          // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
  lcd.print(PotDegeri);                             // Ekranda yazmasını istediğimiz yazıları yolluyoruz.

  yan_son_yazi();
  
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

  lcd.setCursor(3, 1);
  lcd.print("POT Okuma Testi");
  delay(1000);
}

void yan_son_yazi()                                     // Yanıp sönen bilgilendirme mesajını hazırlıyoruz.
{
  i = i + 1;
  if (i < 15)
  {
    lcd.setCursor(1, 2);                                // İmleci, yazmak istediğimiz koordinata yönlendiriyoruz.
    lcd.print("Aciyi Degistiriniz");                    // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
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
