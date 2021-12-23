/*
                                  ///////////////////////////////////////////////////////
                                  /////////   IoT BOT Test Yazılımları Serisi   /////////
                                  ///////////////////////////////////////////////////////
                                              ULTRASONİK SENSÖR (Park Sensörü)
*/

//---------------------------------------          HADİ KODLAYALIM...       ----------------------------------------------------------------

//---------------------------------------   // İLK TANIMLAMALAR VE KÜTÜPHANE EKLEME   ------------------------------------------------------

#define UYGULAMA "Mesafe Sensoru Testi"

int i = 0;                                            // Gidip gelen yazının animasyonu için oluşturulan değişken.

#include <Wire.h>                                     // I2C iletişim protokolünü kullanabilmek için gerekli kütüphaneyi ekliyoruz. 
#include <LiquidCrystal_I2C.h>                        // LCD ekran için gerekli olan kütüphaneyi ekliyoruz. 
LiquidCrystal_I2C lcd(0x27, 20, 4);                   // LCD ekranımızın özelliklerini giriyoruz.
                                                      // Bizim ekranımız 20 satır, 4 sütun karakter destekliyor.


int trigPin = 27;                           // HC-SR04 sensörün Trigger pininin bağlı olduğu pini tanımladık. 
int echoPin = 32;                           // HC-SR04 sensörün Echo pininin bağlı olduğu pini tanımladık. 

float SURE;                                 // Gönderilen ve alınan sinyalin arasındaki süreyi Float(Büyük Sayısal) veri olarak tanımladık. 
float MESAFE;                               // Ölçeceğimiz mesafeyi Float(Büyük Sayısal) veri olarak tanımladık. 

//---------------------------------------   // SADECE İLK AÇILIŞTA BİR KERE ÇALIŞACAK KISIM   ---------------------------------------------

void setup()
{
  Serial.begin(115200);                               // Seri haberleşmeyi "115200" bandında başlattık.
  lcd.init();                                         // LCD ekranı başlatma komutu gönderiyoruz.
  lcd.backlight();                                    // LCD ekranın arka plan aydınlatma ışığını açıyoruz.
  
  giris_animasyon();

  Serial.println("     IoT BOT    ");                 // Seri ekrana bilgilendirme mesajı gönderdik.
  Serial.println(UYGULAMA);

  pinMode(trigPin, OUTPUT);                 // Sensörümüzün Trig ve echo pinlerini çıkış olarak ayarladık.
  pinMode(echoPin, INPUT); 
}

//---------------------------------------   // SÜREKLİ ÇALIŞACAK DÖNGÜ İÇİNDEKİ KISIM   ---------------------------------------------------

void loop()
{
  digitalWrite(echoPin, LOW);               // Alıcı kısmını, sinyal kalmayacak şekilde topraklıyoruz. 
  digitalWrite(trigPin, LOW);               // Verici kısmınıda aynı şekilde topraklıyoruz. 
  delayMicroseconds(2);                     // Sinyallerin yerine oturması için 2 mikro saniye bekliyoruz. 
  digitalWrite(trigPin, HIGH);              // Gönderici kısmını açıyoruz.
  delayMicroseconds(10);                    // 10 mikro saniye bekleme veriyoruz.
  digitalWrite(trigPin, LOW);               // Kapatıyoruz. 

  SURE = pulseIn(echoPin, HIGH);            // Gönderilen sinyalin geri gelme süresini ölçüyoruz. 
  MESAFE = (SURE / 2.0) * 0.0343;           // Giden ve gelen sesin arasındaki süreden faydalanarak, cismin uzaklığını hesaplıyoruz. 

 if (MESAFE >= 400 || MESAFE <= 3)           // Ölçülen mesafe menzil dışında kalıyor ise;
  {
    Serial.println(" - Menzil Dışı!");         // Seri ekrana bilgilendirme mesajı gönderdik.
    lcd.setCursor(0, 3);
    lcd.print("    Menzil Disi!    ");
  }
  else  if (MESAFE < 400 || MESAFE > 3)            // Eğer menzil içerisinde ise;
  {                                   

    Serial.print("Mesafe: ");               // Seri ekrana ölçülen mesafe için bilgilendirme mesajı gönderdik.
    Serial.print(MESAFE, 1);                // Ölçülen mesafeyi, virgülden sonra bir basamak yazdırmak için sınırlandırıyoruz. 
    Serial.println(" cm");                  // Ölçülen değerin birimini seri ekranda yazıyoruz. 
    lcd.setCursor(2, 3);
    lcd.print("Mesafe: ");
    lcd.print(MESAFE);
    lcd.setCursor(16, 3);
    lcd.print(" cm");
    delay(100);
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

  lcd.setCursor(0, 1);
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
