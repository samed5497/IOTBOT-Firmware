/*
  IoT BOT TEST VE KALİBRASYON YAZILIMI V2.0
                                  @TEIRA3D

  ~Joystic Y              00
  ~Encoder Buton          02
  ~Butonlar               04
  ~Korna (Buzzer)         12
  ~DHT11                  13
  ~Röle                   14
  ~Touch 3                15
  ~Encoder A              16
  ~Encoder B              17
  ~Pin 25                 25
  ~Pin 26                 26
  ~Pin 27                 27
  ~Pin 32                 32
  ~Pin 33                 33
  ~Joystic X              34
  ~Joystic Buton          35
  ~Potansiyometre         36
  ~LDR                    39
*/


int Joystick_Y      = 15;
int Joystick_X      = 34;
int Joystick_Buton  = 35;
int Encoder_A       = 16;
int Encoder_B       = 17;
int Encoder_Buton   = 13;
int Butonlar        = 04;
int BUZZER          = 12;
int Role            = 14;
int Ldr             = 39;
int PotPini         = 36;

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);


#include <Encoder.h>                        // Encoder kütüphanemizi tanımladık.
Encoder MyEncoder(Encoder_A, Encoder_B);    // Encoder yön Pinlerimizi tanımladık.
long YeniPozisyon;                          // Yönler için en büyük sayılabilecek long veri tipini atadık.
long EskiPozisyon;                          // Yönler için en büyük sayılabilecek long veri tipini atadık.


int Joystick_XDurum;                        // Joystick'in X ekseninden okunan değerleri integer değer atadık.
int Joystick_YDurum;                        // Joystick'in Y ekseninden okunan değerleri integer değer atadık.
int JoystickButonDurum;                     // Butondan okunan değerleri integer değer atadık.


int PotDegeri;                              // Potansiyometreden Okunan Değerleri İnteger (Sayısal) Değer Atadık.

int ButonlarDurum;                          // Butondan okunan değerleri integer değer atadık.

int DokunmatikDegeri;                       // Dokunmatik Sensörden Gelen Verileri int Değer Atadık.

int LdrDegeri;                              // Sensörde Okunan Değerleri İnteger (Sayısal) Değer Atadık.

void setup()
{
  pinMode(BUZZER, OUTPUT);
  pinMode(Role,   OUTPUT);

  pinMode(Joystick_Y,     INPUT);
  pinMode(Joystick_X,     INPUT);
  pinMode(Joystick_Buton, INPUT);
  pinMode(Butonlar,       INPUT);
  pinMode(Encoder_Buton,  INPUT);
  pinMode(PotPini,        INPUT);
  pinMode(Ldr,            INPUT);

  Serial.begin(115200);
  lcd.init();
  lcd.init();
  lcd.backlight();
  
  LCD_BASLANGIC();
}

/////////////////////////////////////////////////////////////////////////////////////////////////

void loop()
{
  ENCODER();
  JOYSTICK();
  POTANSIYOMETRE();
  BUTONLAR();
  KORNA();
  ROLE();
  LDR();
  FINAL();
}

void LCD_BASLANGIC()
{
  lcd.clear();
  lcd.setCursor(6, 1);
  lcd.print("IoT BOT");
  delay(250);

  lcd.setCursor(2, 3);
  lcd.print("www.teira3d.com");
  INTRO_SES();
  delay(5000);

  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Ilk Adim Testine");
  delay(100);
  lcd.setCursor(4, 1);
  lcd.print("HOSGELDINIZ");
  delay(250);

  GECIS_ONAYI();

  ///////////////////////////////////////
  lcd.clear();
  TEK_SES();
  lcd.setCursor(2, 1);
  lcd.print("Kisa Bir Ogretici");
  delay(250);
  lcd.setCursor(4, 2);
  lcd.print("Ile Birlikte");
  delay(2500);
  ///////////////////////////////////////
  lcd.clear();
  TEK_SES();
  lcd.setCursor(7, 0);
  lcd.print("HAYDI !");
  delay(500);
  lcd.setCursor(6, 2);
  lcd.print("IoT BOT'u");
  delay(250);
  lcd.setCursor(6, 3);
  lcd.print("Ogrenelim");
  delay(3000);
  ///////////////////////////////////////
  lcd.clear();
  TEK_SES();
  lcd.setCursor(5, 0);
  lcd.print("Cok Kolay");
  lcd.setCursor(5, 1);
  lcd.print("Oldugunu");
  delay(500);
  lcd.setCursor(1, 3);
  lcd.print("Sizde Goreceksiniz");
  delay(3000);
  ///////////////////////////////////////
  lcd.clear();
  TEK_SES();
  lcd.setCursor(2, 1);
  lcd.print("HAYDI BASLAYALIM");

  GECIS_ONAYI();

  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("TEBRIKLER ! ");
  delay(250);
  lcd.setCursor(7, 1);
  lcd.print("Iste ");
  lcd.setCursor(1, 2);
  lcd.print("Ilk Asamayi Gectin");
  ONAY_SESI();
  delay(3500);
  ///////////////////////////////////////
  lcd.clear();
  TEK_SES();
  lcd.setCursor(4, 0);
  lcd.print("Bundan Sonra");
  delay(250);
  lcd.setCursor(2, 1);
  lcd.print("Bastigin Bu Buton");
  delay(250);
  lcd.setCursor(1, 2);
  lcd.print("IoT BOT'un ");
  lcd.setCursor(1, 2);
  lcd.print("TAMAM Butonu Olacak");
  delay(4000);
}

void ENCODER()
{
  lcd.clear();
  TEK_SES();
  lcd.setCursor(4, 0);
  lcd.print("Simdi Sirada");
  delay(250);
  lcd.setCursor(7, 1);
  lcd.print("ENCODER");
  delay(250);
  lcd.setCursor(4, 2);
  lcd.print("(Adim Sayici)");
  GECIS_ONAYI();

  delay(500);
  lcd.clear();
  lcd.setCursor(0, 3);
  lcd.print("Gecmek Icin -> ");
  lcd.setCursor(15, 3);
  lcd.print("TAMAM");

  lcd.setCursor(1, 0);
  lcd.print("Encoder Pozisyonu:");
  lcd.setCursor(9, 1);
  lcd.print(EskiPozisyon);

  int butonlar_deger = digitalRead(Encoder_Buton);
  while (butonlar_deger == LOW)
  {
    YeniPozisyon = MyEncoder.read();          // Encoderdan sürekli değer okuma komutu veriyoruz.
    if (YeniPozisyon != EskiPozisyon)         // En son okuduğumuz değer, önceki değerden farklı ise;
    {
      lcd.setCursor(9, 1);
      lcd.print(YeniPozisyon);
      EskiPozisyon = YeniPozisyon;            // Yeni değeri, bir sonraki döngüde eski değer olabilmesi için, eski değer olarak atadık.
    }
    butonlar_deger = digitalRead(Encoder_Buton);
  }

  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("TEBRIKLER ! ");
  delay(250);
  lcd.setCursor(7, 2);
  lcd.print("Encoder ");
  lcd.setCursor(2, 3);
  lcd.print("Testini Gectin !");
  ONAY_SESI();
  delay(2500);
}

void JOYSTICK()
{
  lcd.clear();
  TEK_SES();
  lcd.setCursor(4, 0);
  lcd.print("2 - JOYSTICK");
  delay(250);
  lcd.setCursor(3, 1);
  lcd.print("(2 Eksenli POT)");
  GECIS_ONAYI();

  lcd.clear();
  lcd.setCursor(0, 3);
  lcd.print("Siradaki -> JOYSTICK");

  lcd.setCursor(1, 0);
  lcd.print("X Pozisyonu : ");
  lcd.print(Joystick_XDurum);
  lcd.setCursor(1, 1);
  lcd.print("Y Pozisyonu : ");
  lcd.print(Joystick_YDurum);
  lcd.setCursor(1, 2);
  /*
  lcd.print("Buton Durum : ");
  lcd.print(JoystickButonDurum);
  */
  JoystickButonDurum = digitalRead(JoystickButonDurum);
  while (JoystickButonDurum == LOW)
  {
    Joystick_XDurum = analogRead(Joystick_X);           // X Ekseninden analog olarak değer okuma komutu veriyoruz.
    Joystick_YDurum = analogRead(Joystick_Y);           // Y Ekseninden analog olarak değer okuma komutu veriyoruz.
    JoystickButonDurum = digitalRead(Joystick_Buton);   // Butondan sürekli dijital olarak değer okuma komutu veriyoruz.

    lcd.setCursor(15, 0);
    lcd.print(Joystick_XDurum);
    lcd.setCursor(15, 1);
    lcd.print(Joystick_YDurum);
    /*
    lcd.setCursor(15, 2);
    lcd.print(JoystickButonDurum);
    */
    JoystickButonDurum = digitalRead(JoystickButonDurum);
    delay(50);
  }
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("TEBRIKLER ! ");
  delay(250);
  lcd.setCursor(6, 2);
  lcd.print("Joystick ");
  lcd.setCursor(2, 3);
  lcd.print("Testini Gectin !");
  ONAY_SESI();
  delay(2500);
}

void POTANSIYOMETRE()
{
  lcd.clear();
  TEK_SES();
  lcd.setCursor(1, 0);
  lcd.print("3 - Potansiyometre");
  delay(250);
  lcd.setCursor(0, 1);
  lcd.print("(Ayarli Direnc -POT)");
  GECIS_ONAYI();

  lcd.clear();
  lcd.setCursor(0, 3);
  lcd.print("Siradaki -> JOYSTICK");

  lcd.setCursor(5, 0);
  lcd.print("POT KONUMU");

  JoystickButonDurum = digitalRead(Joystick_Buton);
  while (butonlar_deger == LOW)
  {
    PotDegeri = analogRead(PotPini);          // Encoderdan Sürekli Analog Olarak Değer Okuma Komutu Veriyoruz.

    lcd.setCursor(8, 1);
    lcd.print(PotDegeri);

    JoystickButonDurum = digitalRead(Joystick_Buton);
    delay(50);
  }

  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("TEBRIKLER ! ");
  delay(250);
  lcd.setCursor(3, 2);
  lcd.print("Potansiyometre");
  lcd.setCursor(2, 3);
  lcd.print("Testini Gectin !");
  ONAY_SESI();
  delay(2500);
}

void BUTONLAR()
{
  lcd.clear();
  TEK_SES();
  lcd.setCursor(4, 0);
  lcd.print("4 - BUTONLAR");
  delay(250);
  lcd.setCursor(1, 1);
  lcd.print("(Dijital - Analog)");
  GECIS_ONAYI();

  lcd.clear();
  lcd.setCursor(0, 3);
  lcd.print("Siradaki -> JOYSTICK");

  lcd.setCursor(0, 0);
  lcd.print("DIJITAL  II  ANALOG");
  lcd.setCursor(9, 1);
  lcd.print("II");
  lcd.setCursor(9, 2);
  lcd.print("II");

  JoystickButonDurum = digitalRead(Joystick_Buton);
  while (JoystickButonDurum == LOW)
  {
    ButonlarDurum        = analogRead(Butonlar);          // Butondan sürekli analog olarak değer okuma komutu veriyoruz.
    EncoderButonDurum;   = digitalRead(Encoder_Buton);    // Butondan sürekli dijital olarak değer okuma komutu veriyoruz.

    if (EncoderButonDurum == HIGH)
    {
      lcd.setCursor(0, 2);
      lcd.print("Encoder ");
    }
    else
    {
      lcd.setCursor(0, 2);
      lcd.print("         ");
    }

    if (ButonlarDurum < 1000)
    {
      ButonlarDurum = 0;
    }

    lcd.setCursor(3, 1);
    lcd.print(EncoderButonDurum);

    if (ButonlarDurum < 3500 and ButonlarDurum > 2500)
    {
      lcd.setCursor(14, 1);
      lcd.print(ButonlarDurum);
      lcd.setCursor(15, 2);
      lcd.print("B2");
    }
    else if (ButonlarDurum > 3500)
    {
      lcd.setCursor(14, 1);
      lcd.print(ButonlarDurum);
      lcd.setCursor(15, 2);
      lcd.print("B1");
    }
    else
    {
      lcd.setCursor(15, 2);
      lcd.print("    ");
      lcd.setCursor(14, 1);
      lcd.print("      ");
      lcd.setCursor(15, 1);
      lcd.print(ButonlarDurum);
    }

    JoystickButonDurum = digitalRead(Joystick_Buton);
    delay(100);
  }

  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("TEBRIKLER ! ");
  delay(250);
  lcd.setCursor(8, 2);
  lcd.print("Buton");
  lcd.setCursor(2, 3);
  lcd.print("Testini Gectin !");
  ONAY_SESI();
  delay(2500);
}

void KORNA()
{
  lcd.clear();
  TEK_SES();
  lcd.setCursor(5, 0);
  lcd.print("5 - BUZZER");
  delay(250);
  lcd.setCursor(7, 2);
  lcd.print("(Korna)");
  
  GECIS_ONAYI();

  lcd.clear();
  lcd.setCursor(0, 3);
  lcd.print("Siradaki -> JOYSTICK");
  lcd.setCursor(3, 0);
  lcd.print("Denemek Icin B1");
  lcd.setCursor(1, 1);
  lcd.print("Butonuna Basiniz..");

  JoystickButonDurum = digitalRead(Joystick_Buton);
  while (butonlar_deger == LOW)
  {
    ButonlarDurum        = analogRead(Butonlar);          // Butondan sürekli analog olarak değer okuma komutu veriyoruz.

    if (ButonlarDurum > 3500)
    {
      digitalWrite(BUZZER, HIGH);

      lcd.setCursor(3, 2);
      lcd.print("Buzzer Devrede");
    }
    else
    {
      digitalWrite(BUZZER, LOW);
      lcd.setCursor(0, 2);
      lcd.print("                  ");
    }
    JoystickButonDurum = digitalRead(Joystick_Buton);
    delay(100);
  }

  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("TEBRIKLER ! ");
  delay(250);
  lcd.setCursor(7, 2);
  lcd.print("Buzzer");
  lcd.setCursor(2, 3);
  lcd.print("Testini Gectin !");
  
  ONAY_SESI();
  delay(2500);
}

void ROLE()
{
  lcd.clear();
  TEK_SES();
  lcd.setCursor(6, 0);
  lcd.print("6 - ROLE");
  delay(250);
  lcd.setCursor(1, 1);
  lcd.print("(Kontrollu Anahtar)");
  
  GECIS_ONAYI();

  lcd.clear();
  lcd.setCursor(0, 3);
  lcd.print("Siradaki -> JOYSTICK");
  lcd.setCursor(3, 0);
  lcd.print("Denemek Icin B1");
  lcd.setCursor(1, 1);
  lcd.print("Butonuna Basiniz..");

  JoystickButonDurum = digitalRead(Joystick_Buton);
  while (JoystickButonDurum == LOW)
  {
    ButonlarDurum        = analogRead(Butonlar);          // Butondan sürekli analog olarak değer okuma komutu veriyoruz.

    if (ButonlarDurum > 3500)
    {
      digitalWrite(Role, HIGH);

      lcd.setCursor(4, 2);
      lcd.print("Role Devrede");
    }
    else
    {
      digitalWrite(Role, LOW);

      lcd.setCursor(0, 2);
      lcd.print("                  ");
    }
    JoystickButonDurum = digitalRead(Joystick_Buton);
    delay(50);
  }

  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("TEBRIKLER ! ");
  delay(250);
  lcd.setCursor(8, 2);
  lcd.print("Role");
  lcd.setCursor(2, 3);
  lcd.print("Testini Gectin !");
  ONAY_SESI();
  delay(2500);
}

void LDR()
{
  lcd.clear();
  TEK_SES();
  lcd.setCursor(4, 0);
  lcd.print("Simdi Sirada");
  delay(250);
  lcd.setCursor(8, 1);
  lcd.print("LDR");
  delay(250);
  lcd.setCursor(3, 2);
  lcd.print("(Isik Sensoru)");
  GECIS_ONAYI();

  delay(500);
  lcd.clear();
  lcd.setCursor(0, 3);
  lcd.print("Gecmek Icin -> ");
  lcd.setCursor(15, 3);
  lcd.print("TAMAM");

  lcd.setCursor(4, 0);
  lcd.print("OKUNAN DEGER");


  int butonlar_deger = digitalRead(Encoder_Buton);
  while (butonlar_deger == HIGH)
  {
    LdrDegeri        = analogRead(Ldr);             // Sensörden sürekli analog olarak değer okuma komutu veriyoruz.

    lcd.setCursor(8, 1);
    lcd.print(LdrDegeri);

    if (LdrDegeri > 2200)
    {
      lcd.setCursor(1, 2);
      lcd.print("Parmak Yakinlastir!");
    }
    else
    {
      lcd.setCursor(1, 2);
      lcd.print("Parmak Uzaklastir!");
    }
    butonlar_deger = digitalRead(Encoder_Buton);
    delay(100);
  }

  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("TEBRIKLER ! ");
  delay(250);
  lcd.setCursor(9, 2);
  lcd.print("LDR");
  lcd.setCursor(2, 3);
  lcd.print("Testini Gectin !");
  ONAY_SESI();
  delay(2500);
}
/*
void SICAKLIKNEM()
{
  lcd.clear();
  TEK_SES();
  lcd.setCursor(4, 0);
  lcd.print("Simdi Sirada");
  delay(250);
  lcd.setCursor(8, 1);
  lcd.print("DHT11");
  delay(250);
  lcd.setCursor(2, 2);
  lcd.print("(Sicaklik - Nem)");
  GECIS_ONAYI();

  delay(500);
  lcd.clear();
  lcd.setCursor(0, 3);
  lcd.print("Gecmek Icin -> ");
  lcd.setCursor(15, 3);
  lcd.print("TAMAM");

  lcd.setCursor(3, 0);
  lcd.print("ISI : ");
  lcd.setCursor(3, 1);
  lcd.print("NEM :  ");

  int butonlar_deger = digitalRead(Encoder_Buton);
  while (butonlar_deger == HIGH)
  {
    for (int a = 0; a = 20; a++)
    {
      NEM        = dht.readHumidity();          // Nem Değerini Ölçmek İçin Komut Yolladık.
      SICAKLIK_C = dht.readTemperature();       // Sıcaklık Değerini Santigrat  Cinsinden Ölçmek İçin Komut Yolladık.
    }

    if (isnan(NEM) || isnan(SICAKLIK_C))                        // Ölçülen Değerleri Kontrol Ediyoruz. Eğer Sensörde
    {
      int butonlar_deger = digitalRead(Encoder_Buton);
      while (butonlar_deger == HIGH)
      {
        Serial.println("Sensör Okuma Hatası!");                 // Seri ekrana bilgilendirme mesajı gönderdik.
        lcd.clear();
        lcd.setCursor(4, 1);
        lcd.print("SENSOR OKUMA");
        lcd.setCursor(7, 2);
        lcd.print("HATASI");                                    // Bir Defa Uyarı Gönderdikten Sonra Tekrar Baştan Başlama Komutu Verdik.
        butonlar_deger = digitalRead(Encoder_Buton);
        delay(100);
      }
      TEK_SES();
      delay(1000);
    }

    lcd.setCursor(9, 0);
    lcd.print(SICAKLIK_C);
    lcd.print((char)223);
    lcd.print("C");
    lcd.setCursor(9, 1);
    lcd.print(NEM);
    lcd.print(" %");

    butonlar_deger = digitalRead(Encoder_Buton);
    delay(100);
  }

  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("TEBRIKLER ! ");
  delay(250);
  lcd.setCursor(4, 2);
  lcd.print("DHT11 Sensor");
  lcd.setCursor(2, 3);
  lcd.print("Testini Gectin !");
  ONAY_SESI();
  delay(2500);
}
*/
void FINAL()
{
  ONAY_SESI();
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("TEBRIKLER ! ");
  delay(250);
  lcd.setCursor(1, 2);
  lcd.print("Ilk Egitimi Basari");
  lcd.setCursor(3, 3);
  lcd.print("Ile Gectiniz.");
  KUTLAMA_SESI();
  delay(4000);

  lcd.clear();
  TEK_SES();
  lcd.setCursor(3, 0);
  lcd.print("Artik IoT BOT'u");
  delay(250);
  TEK_SES();
  lcd.setCursor(2, 1);
  lcd.print("Dilediginiz Gibi");
  lcd.setCursor(2, 2);
  lcd.print("Kullanabilirsiniz.");
  delay(4000);

  lcd.clear();
  TEK_SES();
  lcd.setCursor(2, 0);
  lcd.print("Egitime Tekrardan");
  delay(250);
  TEK_SES();
  lcd.setCursor(0, 1);
  lcd.print("Baslamak Isterseniz,");
  TEK_SES();
  lcd.setCursor(5, 2);
  lcd.print("Hemen Simdi");
  lcd.setCursor(0, 3);
  lcd.print("Butona Basin -> ");

  int butonlar_deger = digitalRead(Encoder_Buton);
  while (butonlar_deger == LOW)
  {
    lcd.setCursor(15, 3);
    lcd.print("RESET");
    lcd.setCursor(15, 3);
    lcd.print("     ");
    delay(400);
    lcd.setCursor(15, 3);
    lcd.print("     ");
    lcd.setCursor(15, 3);
    lcd.print("RESET");
    delay(400);
    Serial.println(butonlar_deger);
  }
}

void GECIS_ONAYI()
{
  int butonlar_deger = digitalRead(Joystick_Buton);
  while (butonlar_deger == LOW)
  {
    i = i + 1;
    if (i < 15)
    {
      lcd.setCursor(0, 3);                            // İmleci, yazmak istediğimiz koordinata yönlendiriyoruz.
      lcd.print(" JOYSTICK'e Basiniz..");                // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
    }
    if (i >= 15)
    {
      lcd.setCursor(0, 3);                            // İmleci, yazmak istediğimiz koordinata yönlendiriyoruz.
      lcd.print("                      ");             // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
    }
    if (i == 30)
    {
      i = 0;
    }
    
    butonlar_deger = digitalRead(Encoder_Buton);
  }
  TEK_SES();
}

void ONAY_SESI()
{
  digitalWrite(BUZZER, HIGH);
  delay(100);
  digitalWrite(BUZZER, LOW);
  delay(50);
  digitalWrite(BUZZER, HIGH);
  delay(100);
  digitalWrite(BUZZER, LOW);
  delay(50);

}

void KUTLAMA_SESI()
{
  digitalWrite(BUZZER, HIGH);
  delay(100);
  digitalWrite(BUZZER, LOW);
  delay(50);
  digitalWrite(BUZZER, HIGH);
  delay(100);
  digitalWrite(BUZZER, LOW);
  delay(50);
  digitalWrite(BUZZER, HIGH);
  delay(500);
  digitalWrite(BUZZER, LOW);
  delay(50);
  digitalWrite(BUZZER, HIGH);
  delay(200);
  digitalWrite(BUZZER, LOW);
  delay(50);

}
void TEK_SES()
{
  digitalWrite(BUZZER, HIGH);
  delay(50);
  digitalWrite(BUZZER, LOW);
}

void INTRO_SES()
{
  digitalWrite(BUZZER, HIGH);
  delay(100);
  digitalWrite(BUZZER, LOW);
  delay(50);
  digitalWrite(BUZZER, HIGH);
  delay(150);
  digitalWrite(BUZZER, LOW);
  delay(50);
  digitalWrite(BUZZER, HIGH);
  delay(75);
  digitalWrite(BUZZER, LOW);
  delay(150);
  digitalWrite(BUZZER, HIGH);
  delay(200);
  digitalWrite(BUZZER, LOW);
  delay(100);
  digitalWrite(BUZZER, HIGH);
  delay(100);
  digitalWrite(BUZZER, LOW);
  delay(100);
}
