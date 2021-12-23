/*
                                  ///////////////////////////////////////////////////////
                                  /////////   IoT BOT Test Yazılımları Serisi   /////////
                                  ///////////////////////////////////////////////////////
                                       NTC Sensörü ( Sıcaklık Sensörü ) MODÜLCÜĞÜ
*/

//---------------------------------------          HADİ KODLAYALIM...       ----------------------------------------------------------------

//---------------------------------------   // İLK TANIMLAMALAR VE KÜTÜPHANE EKLEME   ------------------------------------------------------

#define UYGULAMA "NTC Sensor Testi"

int i = 0;                                            // Gidip gelen yazının animasyonu için oluşturulan değişken.

#include <Wire.h>                                     // I2C iletişim protokolünü kullanabilmek için gerekli kütüphaneyi ekliyoruz. 
#include <LiquidCrystal_I2C.h>                        // LCD ekran için gerekli olan kütüphaneyi ekliyoruz. 
LiquidCrystal_I2C lcd(0x27, 20, 4);                   // LCD ekranımızın özelliklerini giriyoruz.
                                                      // Bizim ekranımız 20 satır, 4 sütun karakter destekliyor.

#include <math.h>                           // Hesaplamalar için matematik kütüphanemizi tanımlıyoruz.
 
int NTC = 27;                               // Uygun olan 25 - 26 - 27 - 32 - 33 numaralı pinlerden birini seçiyoruz.

//---------------------------------------   // SADECE İLK AÇILIŞTA BİR KERE ÇALIŞACAK KISIM   ---------------------------------------------

void setup()
{
  Serial.begin(115200);                               // Seri haberleşmeyi "115200" bandında başlattık.
  lcd.init();                                         // LCD ekranı başlatma komutu gönderiyoruz.
  lcd.backlight();                                    // LCD ekranın arka plan aydınlatma ışığını açıyoruz.
  
  giris_animasyon();

  Serial.println("     IoT BOT    ");                 // Seri ekrana bilgilendirme mesajı gönderdik.
  Serial.println(UYGULAMA);

  Serial.println("     IoT BOT    ");       // Seri ekrana bilgilendirme mesajı gönderdik.
  Serial.println("NTC Sıcaklık Sensör Testi..");

  pinMode(NTC,  INPUT);                     // Sensöre veri alacağımız için giriş olarak belirledik.
  
}

//---------------------------------------   // SÜREKLİ ÇALIŞACAK DÖNGÜ İÇİNDEKİ KISIM   ---------------------------------------------------

void loop()
{
  int sicaklik_degeri = analogRead(NTC);                             // Başlangıçta sensörden bilgi okumak için komut veriyoruz.
  hesaplama(sicaklik_degeri);                                        // NTC sensörü ile aldığımız değeri santigrat derecesinden hesaplayabileceğimiz
                                                                     // bir fonksiyona iletiyoru
  delay(500);                                                        // Her sıcaklık ölçümü sonrasında, herhangi bir sıkışma
                                                                     // olmaması için minik bir bekleme süresi koyuyoruz.                                           
}

void hesaplama(int analogOkuma) 
{
    float sicaklik;                                                                                       
    sicaklik = log(((10240000 / analogOkuma) - 10000));                                                   //
    sicaklik = 1 / (0.001129148 + (0.000234125 + (0.0000000876741 * sicaklik * sicaklik)) * sicaklik);
    sicaklik = sicaklik - 273.15;
    delay(200);
    
    Serial.print("Sıcaklık Değeri: ");                                                                    // Seri ekranına bilgilendirme mesajı gönderdik.
    Serial.println(sicaklik); 

    lcd.setCursor(0, 3);
    lcd.print("Sicaklik: ");
    lcd.setCursor(10, 3);
    lcd.print(sicaklik);
    lcd.print((char)223);
    lcd.print("   ");
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
