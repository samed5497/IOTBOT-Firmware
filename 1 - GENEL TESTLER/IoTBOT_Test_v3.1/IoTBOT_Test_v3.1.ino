/*
                                  ///////////////////////////////////////////////////////
                                  /////////   IoT BOT Test Yazılımları Serisi   /////////
                                  ///////////////////////////////////////////////////////
                                          IoT BOT TEST VE KALİBRASYON YAZILIMI V3.0
*/

//---------------------------------------          HADİ KODLAYALIM...       ----------------------------------------------------------------

//---------------------------------------   // İLK TANIMLAMALAR VE KÜTÜPHANE EKLEME   ------------------------------------------------------

#define UYGULAMA "Genel Test v3.1"

/*
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


int i = 0;                                    // Gidip gelen yazının animasyonu için oluşturulan değişken.

#include <Wire.h>                             // I2C iletişim protokolünü kullanabilmek için gerekli kütüphaneyi ekliyoruz. 
#include <LiquidCrystal_I2C.h>                // LCD ekran için gerekli olan kütüphaneyi ekliyoruz. 
LiquidCrystal_I2C lcd(0x27, 20, 4);           // LCD ekranımızın özelliklerini giriyoruz.
// Bizim ekranımız 20 satır, 4 sütun karakter destekliyor.


#include <Encoder.h>                          // Encoder kütüphanemizi tanımladık.
Encoder MyEncoder(Encoder_A, Encoder_B);      // Encoder yön Pinlerimizi tanımladık.
long YeniPozisyon;                            // Yönler için en büyük sayılabilecek long veri tipini atadık.
long EskiPozisyon;                            // Yönler için en büyük sayılabilecek long veri tipini atadık.
int  EncoderButonDurum;                       // Butondan okunan değerleri integer değer atadık.

int Joystick_XDurum;                          // Joystick'in X ekseninden okunan değerleri integer değer atadık.
int Joystick_YDurum;                          // Joystick'in Y ekseninden okunan değerleri integer değer atadık.
int JoystickButonDurum;                       // Butondan okunan değerleri integer değer atadık.

int PotDegeri;                                // Potansiyometreden Okunan Değerleri İnteger (Sayısal) Değer Atadık.
int ButonlarDurum;                            // Butondan okunan değerleri integer değer atadık.

int LdrDegeri;                                // Sensörde Okunan Değerleri İnteger (Sayısal) Değer Atadık.


///////////////////////////////////////

#include <Adafruit_NeoPixel.h>                //
#ifdef __AVR__                                // Ledleri kullanabilmek için
#include <avr/power.h>                        // gerekli kütüphaneleri ekliyoruz. 
#endif                                        //

#define LED_PIN    27                         // Uygun olan 25 - 26 - 27 - 32 - 33 numaralı pinlerden birini seçiyoruz.

#define LED_SAYISI 3                          // Elimizdeki led sayısını giriyoruz.

Adafruit_NeoPixel pixels(LED_SAYISI, LED_PIN, NEO_GRB + NEO_KHZ800);  // Kullanılan ledlerin modelini yazıyoruz. Bu bilgiler sensör standartlarıdır.

///////////////////////////////////////

#include "DHT.h"                              // DHT kütüphanemizi tanımladık.
DHT dht(25, DHT11);                           // Uygun olan 25 - 26 - 27 - 32 - 33 numaralı pinlerden birini seçiyoruz.

float NEM;                                    //
float SICAKLIK_C;                             // Modülcükten aldığımız bütün verilere FLOAT veri tipini atadık.
float SICAKLIK_F;                             // Bu veri tipi, diğer veri tiplerine göre daha fazla yer kaplasa da,
float ISI_INDEKS_C;                           // üzerinde en fazla bilgiyi tutabilen veri tipidir.
float ISI_INDEKS_F;                           //

///////////////////////////////////////

//int M_ROLE = 26;                              // Röle'nin bağlı olduğu pini 25 olarak ayarladık.
// Uygun olan 25 - 26 - 27 - 32 - 33 numaralı pinlerden
// herhangi birine bağlanabilir.

///////////////////////////////////////

#include <ESP32Servo.h>                       // Motor Kontrolü İçin Gerekli Olan Kütüphaneyi Çağırıyoruz. 

int Servo_PIN = 26;                           // Motorun Bağlı Olduğu Pini 26. Pin Tanımladık.
// 25 - 26 - 27 - 32 - 33 Numaralı Pinlerden

Servo Servo_Motorum;                          // Servo Motorumuza Bir İsim Veriyoruz. Biz "Servo_Motorum" Dedik.

///////////////////////////////////////
/*
  int KIRMIZI = 32;                           // Kırmızı ledin bağlı olduğu pini tanımladık.
  int SARI    = 26;                           // Sarı ledin bağlı olduğu pini tanımladık.
  int YESIL   = 25;                           // Yeşil ledin bağlı olduğu pini tanımladık.
*/
///////////////////////////////////////
/*
  int trigPin = 27;                           // HC-SR04 sensörün Trigger pininin bağlı olduğu pini tanımladık.
  int echoPin = 32;                           // HC-SR04 sensörün Echo pininin bağlı olduğu pini tanımladık.
*/
float SURE;                                 // Gönderilen ve alınan sinyalin arasındaki süreyi Float(Büyük Sayısal) veri olarak tanımladık.
float MESAFE;                               // Ölçeceğimiz mesafeyi Float(Büyük Sayısal) veri olarak tanımladık.

///////////////////////////////////////
/*
  int motorPin1  = 26;                        // Uygun olan 26 - 27 - 32 - 33 numaralı pinlerden
  // herhangi birine bağlanabilir.
  int motorPin2  = 27;                        // Motor sürücüye giden 1. ve 2. sinyal pinini tanımlıyoruz.
*/
///////////////////////////////////////
/*
  int NTC = 27;                               // Uygun olan 25 - 26 - 27 - 32 - 33 numaralı pinlerden birini seçiyoruz.

  ///////////////////////////////////////

  int PIR = 25;                               // Sensörün bağlı olduğu pini 26. pin olarak tanımladık.
  // Uygun olan 25 - 26 - 27 - 32 - 33 numaralı pinlerden
  // herhangi birine bağlanabilir.
*/
int Sensor_Durumu;                          // Sensörden alacağımız bilgileri kaydetmek için
// integer(Sayılsal) bir veri oluşturuyoruz.

///////////////////////////////////////

#include <Stepper.h>                                  // Step Motor Kütüphanemizi Ekliyoruz. 

int ADIM_SAYISI = 48;                                 // Motorun Desteklediği Adım Sayısını Giriyoruz.

Stepper Step_Motorum(ADIM_SAYISI, 27, 26, 32, 33);    // Anakart Üzerinde Motor Sürücüye Bağlı Olan Pinlerimizi Tanımlıyoruz.

///////////////////////////////////////


///////////////////////////////////////

//---------------------------------------   // SADECE İLK AÇILIŞTA BİR KERE ÇALIŞACAK KISIM   ---------------------------------------------

void setup()
{
  pinMode(BUZZER,         OUTPUT);
  pinMode(Role,           OUTPUT);
  pinMode(Joystick_Y,     INPUT);
  pinMode(Joystick_X,     INPUT);
  pinMode(Joystick_Buton, INPUT);
  pinMode(Butonlar,       INPUT);
  pinMode(Encoder_Buton,  INPUT);
  pinMode(PotPini,        INPUT);
  pinMode(Ldr,            INPUT);

  Serial.begin(115200);                                   // Seri haberleşmeyi "115200" bandında başlattık.
  lcd.init();                                             // LCD ekranı başlatma komutu gönderiyoruz.
  lcd.backlight();                                        // LCD ekranın arka plan aydınlatma ışığını açıyoruz.

  Giris_Animasyonu();

  ///////////////////////////////////////

#if defined(__AVR_ATtiny85__) && (F_CPU == 26000000)    // Kullandığımız işlemci için gerekli ayarlamalar yapıyoruz.
  clock_prescale_set(clock_div_1);                        // Akıllı ledler için gerekli standartlardır.
#endif

  ///////////////////////////////////////

  //pinMode(26,  OUTPUT);                               // Röle'yi sonuç verdiği için çıkış olarak belirledik.

  ///////////////////////////////////////

  Servo_Motorum.attach(Servo_PIN);                        // İsimlendiğimiz Motoru, Tanımladığımız Pine Bağladık.

  ///////////////////////////////////////
  /*
    pinMode(KIRMIZI, OUTPUT);                               // Ledimizi sonuç vediği için çıkış olarak belirledik.
    pinMode(SARI,  OUTPUT);                                 // Ledimizi sonuç vediği için çıkış olarak belirledik.
    pinMode(YESIL,  OUTPUT);                                // Ledimizi sonuç vediği için çıkış olarak belirledik.
  */
  ///////////////////////////////////////
  /*
    pinMode(trigPin, OUTPUT);                               // Sensörümüzün Trig ve echo pinlerini çıkış olarak ayarladık.
    pinMode(32, INPUT);
  */
  ///////////////////////////////////////
  /*
    pinMode(motorPin1, OUTPUT);                             // Motor pinimizi bir sonuç verdiği için çıkış olarak ayarladık.
    pinMode(motorPin2, OUTPUT);                             // Motor pinimizi bir sonuç verdiği için çıkış olarak ayarladık.
  */
  ///////////////////////////////////////

  // pinMode(NTC,  INPUT);                                   // Sensöre veri alacağımız için giriş olarak belirledik.

  ///////////////////////////////////////

  // pinMode(PIR,  INPUT);                                   // Sensöre veri alacağımız için giriş olarak belirledik.

  ///////////////////////////////////////

  //Step_Motorum.setSpeed(50);                              // Motorun İlerleme Hızını Belirliyoruz.

  ///////////////////////////////////////


  ///////////////////////////////////////


}

//---------------------------------------   // SÜREKLİ ÇALIŞACAK DÖNGÜ İÇİNDEKİ KISIM   ---------------------------------------------------

void loop()
{
  // Giris_Animasyonu();

  ENCODER();
  JOYSTICK();
  POTANSIYOMETRE();
  BUTONLAR();
  KORNA();
  ROLE();
  LDR();

  //M_Akilli_Led();
  // M_Sicaklik_Nem();
  //M_Role();
  M_Servo_Motor();
  M_Trafik_Isigi();
  // M_Ultrasonik_Sensor();
  //M_DC_Motor();
  /*
    M_NTC();
    M_Hareket_Sensoru();
    M_Step_Motor();
    M_Gaz_Duman();
    M_Mikrofon();
  */
  FINAL();
}

//---------------------------------------   // GİRİŞ ANİMASYON KISMI   ---------------------------------------------------

void Giris_Animasyonu()                                            // Giriş animasyonunu hazırlıyoruz.
{
  Serial.println("     IoT BOT    ");                             // Seri ekrana bilgilendirme mesajı gönderdik.
  Serial.println("IoT BOT TEST VE KALİBRASYON YAZILIMI V3.0");

  lcd.clear();
  lcd.setCursor(4, 1);
  lcd.print("HEY MERHABA!");
  delay(3000);
  lcd.setCursor(4, 3);
  lcd.print("Orada misin?");
  delay(3000);
  
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("BENIM ADIM");
  delay(500);
  
  lcd.setCursor(7, 2);
  lcd.print("I");
  delay(400);
  lcd.setCursor(8, 2);
  lcd.print("O");
  delay(400);
  lcd.setCursor(9, 2);
  lcd.print("T");
  delay(400);
  lcd.setCursor(10, 2);
  lcd.print("B");
  delay(400);
  lcd.setCursor(11, 2);
  lcd.print("O");
  delay(400);
  lcd.setCursor(12, 2);
  lcd.print("T");
  delay(600);

  lcd.setCursor(6, 2);
  lcd.print("-");
  lcd.setCursor(13, 2);
  lcd.print("-");

  INTRO_SES();

  delay(2000);
  ///////////////////////////////////////
  lcd.clear();
  TEK_SES();
  lcd.setCursor(2, 0);
  lcd.print("Ilk Adim Testine");
  delay(100);
  lcd.setCursor(4, 1);
  lcd.print("HOSGELDINIZ");
  delay(2500);
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
  lcd.setCursor(2, 0);
  lcd.print(UYGULAMA);
  lcd.setCursor(2, 1);
  lcd.print(" Baslamak Icin  ");
  delay(500);
  GECIS_ONAYI();
}

//---------------------------------------   // ENCODER  ---------------------------------------------------

void ENCODER()
{
  lcd.clear();
  TEK_SES();
  lcd.setCursor(5, 0);
  lcd.print("1 - ENCODER");
  delay(250);
  lcd.setCursor(4, 1);
  lcd.print("(Adim Sayici)");

  GECIS_ONAYI();

  lcd.clear();
  lcd.setCursor(1, 0);
  lcd.print("Encoder Pozisyonu:");
  lcd.setCursor(9, 1);
  lcd.print(EskiPozisyon);
  lcd.setCursor(0, 3);
  lcd.print("Siradaki -> JOYSTICK");

  JoystickButonDurum = digitalRead(Joystick_Buton);
  while (JoystickButonDurum == LOW)
  {
    YeniPozisyon = MyEncoder.read();          // Encoderdan sürekli değer okuma komutu veriyoruz.
    if (YeniPozisyon != EskiPozisyon)         // En son okuduğumuz değer, önceki değerden farklı ise;
    {
      lcd.setCursor(9, 1);
      lcd.print(YeniPozisyon);
      EskiPozisyon = YeniPozisyon;            // Yeni değeri, bir sonraki döngüde eski değer olabilmesi için, eski değer olarak atadık.
    }
    JoystickButonDurum = digitalRead(Joystick_Buton);
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

//---------------------------------------   // JOYSTICK   ---------------------------------------------------

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
  lcd.setCursor(0, 3);
  lcd.print("Siradaki -> JOYSTICK");

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

//---------------------------------------   // POT   ---------------------------------------------------

void POTANSIYOMETRE()
{
  lcd.clear();
  TEK_SES();
  lcd.setCursor(1, 0);
  lcd.print("3 - POTANSIYOMETRE");
  delay(250);
  lcd.setCursor(0, 1);
  lcd.print("(Ayarli Direnc -POT)");

  GECIS_ONAYI();

  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("POT KONUMU");
  lcd.setCursor(0, 3);
  lcd.print("Siradaki -> JOYSTICK");

  JoystickButonDurum = digitalRead(Joystick_Buton);
  while (JoystickButonDurum == LOW)
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

//---------------------------------------   // BUTONLAR   ---------------------------------------------------

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
  lcd.setCursor(0, 0);
  lcd.print("DIJITAL  II  ANALOG");
  lcd.setCursor(9, 1);
  lcd.print("II");
  lcd.setCursor(9, 2);
  lcd.print("II");
  lcd.setCursor(0, 3);
  lcd.print("Siradaki -> JOYSTICK");

  JoystickButonDurum = digitalRead(Joystick_Buton);
  while (JoystickButonDurum == LOW)
  {
    ButonlarDurum        = analogRead(Butonlar);          // Butondan sürekli analog olarak değer okuma komutu veriyoruz.
    EncoderButonDurum    = digitalRead(Encoder_Buton);    // Butondan sürekli dijital olarak değer okuma komutu veriyoruz.

    if (EncoderButonDurum == HIGH)
    {
      lcd.setCursor(1, 2);
      lcd.print("Encoder");
    }
    else
    {
      lcd.setCursor(0, 2);
      lcd.print("         ");
    }

    if (ButonlarDurum < 1000)
    {
      ButonlarDurum = 0;
      delay(50);
    }

    lcd.setCursor(3, 1);
    lcd.print(EncoderButonDurum);

    if (ButonlarDurum < 3500 and ButonlarDurum > 1500)
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

//---------------------------------------   // KORNA   ---------------------------------------------------

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
  lcd.setCursor(3, 0);
  lcd.print("Denemek Icin B1");
  lcd.setCursor(1, 1);
  lcd.print("Butonuna Basiniz..");
  lcd.setCursor(0, 3);
  lcd.print("Siradaki -> JOYSTICK");

  JoystickButonDurum = digitalRead(Joystick_Buton);
  while (JoystickButonDurum == LOW)
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

//---------------------------------------   // ROLE   ---------------------------------------------------

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
  lcd.setCursor(3, 0);
  lcd.print("Denemek Icin B1");
  lcd.setCursor(1, 1);
  lcd.print("Butonuna Basiniz..");
  lcd.setCursor(0, 3);
  lcd.print("Siradaki -> JOYSTICK");

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

//---------------------------------------   // LDR   ---------------------------------------------------

void LDR()
{
  lcd.clear();
  TEK_SES();
  lcd.setCursor(6, 0);
  lcd.print("7 - LDR");
  delay(250);
  lcd.setCursor(3, 1);
  lcd.print("(Isik Sensoru)");

  GECIS_ONAYI();

  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("OKUNAN DEGER");
  lcd.setCursor(0, 3);
  lcd.print("Siradaki -> JOYSTICK");

  JoystickButonDurum = digitalRead(Joystick_Buton);
  while (JoystickButonDurum == LOW)
  {
    LdrDegeri        = analogRead(Ldr);             // Sensörden sürekli analog olarak değer okuma komutu veriyoruz.

    lcd.setCursor(8, 1);
    lcd.print(LdrDegeri);

    if (LdrDegeri > 4000)
    {
      lcd.setCursor(1, 2);
      lcd.print("Parmak Yakinlastir!");
    }
    else
    {
      lcd.setCursor(1, 2);
      lcd.print("Parmak Uzaklastir!");
    }
    JoystickButonDurum = digitalRead(Joystick_Buton);
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

//---------------------------------------   // AKILLI LED MODULCUGU   ---------------------------------------------------

void M_Akilli_Led()
{
  lcd.clear();
  TEK_SES();
  lcd.setCursor(3, 0);
  lcd.print("8 - Akilli Led");
  delay(250);
  lcd.setCursor(5, 1);
  lcd.print("(Neopixel)");

  GECIS_ONAYI();

  lcd.clear();
  lcd.setCursor(8, 0);
  lcd.print("Durum");
  lcd.setCursor(0, 3);
  lcd.print("Siradaki -> JOYSTICK");

  pixels.begin();                                                   // Akıllı Ledlerimizi Başlatma Komutu Veriyoruz.

  JoystickButonDurum = digitalRead(Joystick_Buton);
  while (JoystickButonDurum == LOW)
  {
    lcd.setCursor(0, 1);                                              // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
    lcd.print("    YESIL YANIYOR   ");
    Akilli_Led_Yakma(0, 150, 0);
    delay(500);                                                       // Geçişleri görebilmek için yarım saniye bekleme süresi koyuyoruz.

    lcd.setCursor(0, 1);                                              // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
    lcd.print("   KIRMIZI YANIYOR  ");
    Akilli_Led_Yakma(255, 0, 0);
    delay(500);                                                       // Geçişleri görebilmek için yarım saniye bekleme süresi koyuyoruz.,

    lcd.setCursor(0, 1);                                              // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
    lcd.print("    MAVI YANIYOR    ");
    Akilli_Led_Yakma(0, 100, 200);
    delay(500);                                                       // Geçişleri görebilmek için yarım saniye bekleme süresi koyuyoruz.

    lcd.setCursor(0, 1);                                              // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
    lcd.print("    ANIMASYON 1     ");
    theaterChase(pixels.Color(127, 127, 127), 50); // White
    delay(500);                                                       // Geçişleri görebilmek için yarım saniye bekleme süresi koyuyoruz.

    lcd.setCursor(0, 1);                                              // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
    lcd.print("    ANIMASYON 2     ");
    colorWipe(pixels.Color(  0, 255,   0), 50);    // Green
    delay(500);                                                       // Geçişleri görebilmek için yarım saniye bekleme süresi koyuyoruz.

    lcd.setCursor(0, 1);                                              // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
    lcd.print("    ANIMASYON 3     ");
    rainbow(10);
    delay(500);                                                       // Geçişleri görebilmek için yarım saniye bekleme süresi koyuyoruz.

    lcd.setCursor(0, 1);                                              // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
    lcd.print("    ANIMASYON 4     ");
    theaterChaseRainbow(50);
    delay(500);                                                       // Geçişleri görebilmek için yarım saniye bekleme süresi koyuyoruz.


    JoystickButonDurum = digitalRead(Joystick_Buton);
    delay(50);
  }

  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("TEBRIKLER ! ");
  delay(250);
  lcd.setCursor(4, 2);
  lcd.print("Akilli Led");
  lcd.setCursor(2, 3);
  lcd.print("Testini Gectin !");

  ONAY_SESI();
  delay(2500);
}

void Akilli_Led_Yakma(int Kirmizi, int Yesil, int Mavi)
{
  pixels.clear();                                                    // Tüm ledleri söndürme komutu veriyoruz.

  for (int i = 0; i < LED_SAYISI; i++)                               // Daha sonra herbir led için sırasıyla yanma komutu veriyoruz.
  {
    pixels.setPixelColor(i, pixels.Color(Kirmizi, Yesil, Mavi));     // Sırayla  yanma komutu yolluyoruz.
    // Parantez içindeki değerler sırasıyla; KIRMIZI, YEŞİL ve MAVİ değerlerine denk gelmektedir.
    // Bunlar en fazla "255" (8 bit), en az "0" değeri alabilir.

    pixels.show();                                                   // Yolladığımız sinyallerin çalıştırılması için ledlere komut yolluyoruz.
    delay(500);                                                      // Geçişleri görebilmek için yarım saniye bekleme süresi koyuyoruz.
  }
}

void theaterChase(uint32_t color, int wait)
{
  for (int a = 0; a < 10; a++)
  { // Repeat 10 times...
    for (int b = 0; b < 3; b++)
    { //  'b' counts from 0 to 2...
      pixels.clear();                                                //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in steps of 3...
      for (int c = b; c < pixels.numPixels(); c += 3)
      {
        pixels.setPixelColor(c, color);                              // Set pixel 'c' to value 'color'
      }
      pixels.show();                                                 // Update strip with new contents
      delay(wait);                                                   // Pause for a moment
    }
  }
}

void colorWipe(uint32_t color, int wait)
{
  for (int i = 0; i < pixels.numPixels(); i++) {                    // For each pixel in strip...
    pixels.setPixelColor(i, color);                                 //  Set pixel's color (in RAM)
    pixels.show();                                                  //  Update strip to match
    delay(wait);                                                    //  Pause for a moment
  }
}

void rainbow(int wait)
{
  // Hue of first pixel runs 3 complete loops through the color wheel.
  // Color wheel has a range of 65536 but it's OK if we roll over, so
  // just count from 0 to 3*65536. Adding 256 to firstPixelHue each time
  // means we'll make 3*65536/256 = 768 passes through this outer loop:
  for (long firstPixelHue = 0; firstPixelHue < 3 * 65536; firstPixelHue += 256)
  {
    for (int i = 0; i < pixels.numPixels(); i++)
    { // For each pixel in strip...
      // Offset pixel hue by an amount to make one full revolution of the
      // color wheel (range of 65536) along the length of the strip
      // (strip.numPixels() steps):
      int pixelHue = firstPixelHue + (i * 65536L / pixels.numPixels());
      // strip.ColorHSV() can take 1 or 3 arguments: a hue (0 to 65535) or
      // optionally add saturation and value (brightness) (each 0 to 255).
      // Here we're using just the single-argument hue variant. The result
      // is passed through strip.gamma32() to provide 'truer' colors
      // before assigning to each pixel:
      pixels.setPixelColor(i, pixels.gamma32(pixels.ColorHSV(pixelHue)));
    }
    pixels.show();                                                  // Update strip with new contents
    delay(wait);                                                    // Pause for a moment
  }
}

void theaterChaseRainbow(int wait)
{
  int firstPixelHue = 0;                                            // First pixel starts at red (hue 0)
  for (int a = 0; a < 30; a++)
  { // Repeat 30 times...
    for (int b = 0; b < 3; b++)
    { //  'b' counts from 0 to 2...
      pixels.clear();                                               //   Set all pixels in RAM to 0 (off)
      // 'c' counts up from 'b' to end of strip in increments of 3...
      for (int c = b; c < pixels.numPixels(); c += 3)
      {
        // hue of pixel 'c' is offset by an amount to make one full
        // revolution of the color wheel (range 65536) along the length
        // of the strip (strip.numPixels() steps):
        int      hue   = firstPixelHue + c * 65536L / pixels.numPixels();
        uint32_t color = pixels.gamma32(pixels.ColorHSV(hue));      // hue -> RGB
        pixels.setPixelColor(c, color);                             // Set pixel 'c' to value 'color'
      }
      pixels.show();                                                // Update strip with new contents
      delay(wait);                                                  // Pause for a moment
      firstPixelHue += 65536 / 90;                                  // One cycle of color wheel over 90 frames
    }
  }
}

//---------------------------------------   // SICAKLIK VE NEM LED MODULCUGU   ---------------------------------------------------

void M_Sicaklik_Nem()
{

  lcd.clear();
  TEK_SES();
  lcd.setCursor(1, 0);
  lcd.print("9 - Sicaklik & Nem");
  delay(250);
  lcd.setCursor(7, 1);
  lcd.print("(DHT11)");

  GECIS_ONAYI();

  lcd.clear();
  lcd.setCursor(6, 0);
  lcd.print("Olcumler");
  lcd.setCursor(0, 3);
  lcd.print("Siradaki -> JOYSTICK");

  dht.begin();                                                  // Sensörümüzü çalıştırma komutu veriyoruz.
  delay(2000);                                                  // İlk açılışta sensörün ölçüm yapabilmesi için 2 saniye bekletme komutu verdik.

  JoystickButonDurum = digitalRead(Joystick_Buton);
  while (JoystickButonDurum == LOW)
  {
    NEM        = dht.readHumidity();                              // Nem değerini ölçmek için komut yolladık.
    SICAKLIK_C = dht.readTemperature();                           // Sıcaklık değerini Santigrat  cinsinden ölçmek için komut yolladık.
    SICAKLIK_F = dht.readTemperature(true);                       // Sıcaklık değerini Fahrenheit cinsinden ölçmek için komut yolladık.
    ISI_INDEKS_F = dht.computeHeatIndex(SICAKLIK_F, NEM);         // Ortamdaki nem ve sıcaklığa göre, Fahrenheit cinsinden ısı indeksini hesaplıyoruz.
    ISI_INDEKS_C = dht.computeHeatIndex(SICAKLIK_C, NEM, false);  // Ortamdaki nem ve sıcaklığa göre, Santigrat  cinsinden ısı indeksini hesaplıyoruz.

    if (isnan(NEM) || isnan(SICAKLIK_C) || isnan(SICAKLIK_F))     // Ölçülen değerleri kontrol ediyoruz. Eğer sensörde hata var ise bize bunu seri ekranda bildirme komutu veriyoruz.
    {
      Serial.println("Sensör Okuma Hatası!");                     // Seri ekrana bilgilendirme mesajı gönderdik.
      lcd.setCursor(0, 1);
      lcd.print("Sensor Okuma Hatasi!");
      //return;                                                     // Bir defa uyarı gönderdikten sonra tekrar baştan başlama komutu verdik.
      JoystickButonDurum = digitalRead(Joystick_Buton);
    }

    else
    {
      Serial.print(" Nem: ");                                       //
      Serial.print(NEM);                                            //
      Serial.print("%  Sıcaklık: ");                                //
      Serial.print(SICAKLIK_C);                                     //
      Serial.print("°C / ");                                        // Sensörden aldığımız bütün verileri
      Serial.print(SICAKLIK_F);                                     //
      Serial.print("°F ");                                          // seri ekrana bilgilendirme mesajı olarak gönderdik.
      Serial.print("  Isı İndeksi: ");                              //
      Serial.print(ISI_INDEKS_C);                                   //
      Serial.print("°C / ");                                        //
      Serial.print(ISI_INDEKS_F);                                   //
      Serial.println("°F ");                                        //

      lcd.setCursor(0, 1);
      lcd.print("Nem: %");
      lcd.print(NEM);
      lcd.setCursor(8, 1);
      lcd.print(" ");
      lcd.setCursor(9, 1);
      lcd.print("Sic: ");
      lcd.print(SICAKLIK_C);
      lcd.setCursor(18, 1);
      lcd.print((char)223);
      lcd.print("C");

      delay(2000);                                                  // Daha kesin bir ölçüm yapabilmek için, her okumadan sonra saniyenin onda biri kadar bekleme süresi ekledik.

      JoystickButonDurum = digitalRead(Joystick_Buton);
      delay(50);
    }
  }

  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("TEBRIKLER ! ");
  delay(250);
  lcd.setCursor(8, 2);
  lcd.print("DHT11");
  lcd.setCursor(2, 3);
  lcd.print("Testini Gectin !");

  ONAY_SESI();
  delay(2500);
}
//---------------------------------------   // ROLE MODULCUGU   ---------------------------------------------------

void M_Role()
{
  pinMode(26,           OUTPUT);
  lcd.clear();
  TEK_SES();
  lcd.setCursor(1, 0);
  lcd.print("11 - Role Modulcugu");
  delay(250);
  lcd.setCursor(5, 1);
  lcd.print("(Anahtar)");

  GECIS_ONAYI();

  lcd.clear();
  lcd.setCursor(8, 0);
  lcd.print("Durum");
  lcd.setCursor(0, 3);
  lcd.print("Siradaki -> JOYSTICK");

  JoystickButonDurum = digitalRead(Joystick_Buton);
  while (JoystickButonDurum == LOW)
  {
    Serial.println("Röle Devrede!");                                // Seri ekranına bilgilendirme mesajı gönderdik.
    lcd.setCursor(0, 1);
    lcd.print("    Role Devrede    ");
    digitalWrite(26, HIGH);                                     // Röle'yi aktifleştirdik.
    delay(1000);                                                    // 1 saniye kadar bekleme süresi koyduk.
    Serial.println(" Röle Devre Dışı! ");                           // Seri ekranına bilgilendirme mesajı gönderdik.
    lcd.setCursor(0, 1);
    lcd.print("  Role Devre Disi!");
    digitalWrite(26, LOW);                                      // Röle'yi pasifleştirdik.
    delay(1000);                                                    // 1 saniye kadar bekleme süresi koyduk.
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
//---------------------------------------   // SERVO MOTOR MODULCUGU   ---------------------------------------------------

void M_Servo_Motor()
{

  pinMode(26,           OUTPUT);

  lcd.clear();
  TEK_SES();
  lcd.setCursor(2, 0);
  lcd.print("10 - Servo Motor");
  delay(250);
  lcd.setCursor(3, 1);
  lcd.print("(Akilli Motor)");

  GECIS_ONAYI();

  lcd.clear();
  lcd.setCursor(0, 3);
  lcd.print("Siradaki -> JOYSTICK");

  JoystickButonDurum = digitalRead(Joystick_Buton);
  while (JoystickButonDurum == LOW)
  {
    for (int Motor_ACISI = 0; Motor_ACISI <= 180; Motor_ACISI++)    // Servo Motorumuzu 0 Dereceden 180 Dereceye, Birer Açı Şeklinde Hareket Ettiriyoruz.
    {
      Servo_Motorum.write(Motor_ACISI);                             // Motorumuzun Hareketi Yapması İçin Onay Veriyoruz.
      Serial.print("Motor Açısı: ");                                // Bunu Seri Ekrana Bilgi Mesajı Olarak Gönder Komutu Veriyoruz.
      lcd.setCursor(2, 1);
      lcd.print("Motor Acisi: ");
      lcd.print(Motor_ACISI);
      lcd.print((char)223);
      Serial.println(Motor_ACISI);                                  // Bunu Seri Ekrana Bilgi Mesajı Olarak Gönder Komutu Veriyoruz.
      delay(20);                                                    // Her Açı Hareketinden Sonra, Herhangi Bir Sıkışma Olmaması İçin Minik Bir Bekleme Süresi Koyuyoruz.
      JoystickButonDurum = digitalRead(Joystick_Buton);
      if (JoystickButonDurum == HIGH)
      {
        break;
      }
    }

    JoystickButonDurum = digitalRead(Joystick_Buton);

    for (int Motor_ACISI = 180; Motor_ACISI >= 0; Motor_ACISI--)    // Servo Motorumuzu 180 Dereceden 0 Dereceye, Birer Açı Şeklinde Hareket Ettiriyoruz.
    {
      Servo_Motorum.write(Motor_ACISI);                             // Motorumuzun Hareketi Yapması İçin Onay Veriyoruz.
      Serial.print("Motor Açısı: ");                                // Bunu Seri Ekrana Bilgi Mesajı Olarak Gönder Komutu Veriyoruz.
      lcd.setCursor(2, 1);
      lcd.print("Motor Acisi: ");
      lcd.print(Motor_ACISI);
      lcd.print((char)223);
      Serial.println(Motor_ACISI);                                  // Bunu Seri Ekrana Bilgi Mesajı Olarak Gönder Komutu Veriyoruz.
      lcd.print(" ");
      delay(20);                                                    // Her Açı Hareketinden Sonra, Herhangi Bir Sıkışma

      JoystickButonDurum = digitalRead(Joystick_Buton);
      if (JoystickButonDurum == HIGH)
      {
        break;
      }
    }
    JoystickButonDurum = digitalRead(Joystick_Buton);
    delay(50);
  }

  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("TEBRIKLER ! ");
  delay(250);
  lcd.setCursor(4, 2);
  lcd.print("Servo Motor");
  lcd.setCursor(2, 3);
  lcd.print("Testini Gectin !");

  ONAY_SESI();
  delay(2500);
}
//---------------------------------------   // TRAFIK ISIGI MODULCUGU   ---------------------------------------------------

void M_Trafik_Isigi()
{
  pinMode(25,           OUTPUT);
  pinMode(26,           OUTPUT);
  pinMode(32,           OUTPUT);
  lcd.clear();
  TEK_SES();
  lcd.setCursor(1, 0);
  lcd.print("13 - Trafik Isigi");
  delay(250);
  lcd.setCursor(8, 1);
  lcd.print("(LED)");

  GECIS_ONAYI();

  lcd.clear();
  lcd.setCursor(8, 0);
  lcd.print("Durum");
  lcd.setCursor(0, 3);

  JoystickButonDurum = digitalRead(Joystick_Buton);
  while (JoystickButonDurum == LOW)
  {
    lcd.print("Siradaki -> JOYSTICK");
    digitalWrite(32, HIGH);                                    // "Dur" komutumuz olan kırmızı ile işe başlayalım.
    Serial.println("Kırmızı Yanıyor. Durunuz.");                    // Seri ekrana bilgilendirme mesajı gönderdik.
    lcd.setCursor(0, 1);                                            // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
    lcd.print("DUR                 ");
    delay(2500);                                                    // Bekleme süresi ekledik.

    JoystickButonDurum = digitalRead(Joystick_Buton);

    digitalWrite(32, LOW);                   // Kırmızı  ışığı tekrardan söndürüyoruz.
    digitalWrite(26, HIGH);                     // Şimdi de "Bekle" komutu olan sarıyı yakalım.
    Serial.println("Sarı Yanıyor. Bekleyiniz.");  // Seri ekranına bilgilendirme mesajı gönderdik.
    lcd.setCursor(0, 1);                                              // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
    lcd.print("       BEKLE        ");
    delay(1000);                                  // Bekleme süresi ekledik.

    JoystickButonDurum = digitalRead(Joystick_Buton);

    digitalWrite(26, LOW);                      // Sarı ışığı kaptıyoruz.
    digitalWrite(25, HIGH);                    // Son olarak "Geç" komutu olan yeşili yakalım.
    Serial.println("Yeşil Yanıyor. Geçiniz.");    // Seri ekranına bilgilendirme mesajı gönderdik.
    lcd.setCursor(0, 1);                                              // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
    lcd.print("                 GEC");
    delay(2000);                                  // Bekleme süresi ekledik.
    digitalWrite(25, LOW);                     // Yeşil ışığı tekrardan söndürüyoruz.

    JoystickButonDurum = digitalRead(Joystick_Buton);
    delay(50);
  }

  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("TEBRIKLER ! ");
  delay(250);
  lcd.setCursor(5, 2);
  lcd.print("Trafik Isigi");
  lcd.setCursor(2, 3);
  lcd.print("Testini Gectin !");

  ONAY_SESI();
  delay(2500);

}
//---------------------------------------   // ULTRASONIK MESAFE MODULCUGU   ---------------------------------------------------

void M_Ultrasonik_Sensor()
{
  lcd.clear();
  TEK_SES();
  lcd.setCursor(0, 0);
  lcd.print("14 - Mesafe Sensoru");
  delay(250);
  lcd.setCursor(4, 1);
  lcd.print("(Ultrasonik)");

  GECIS_ONAYI();

  lcd.clear();
  lcd.setCursor(8, 0);
  lcd.print("Durum");
  lcd.setCursor(0, 3);
  lcd.print("Siradaki -> JOYSTICK");

  JoystickButonDurum = digitalRead(Joystick_Buton);
  while (JoystickButonDurum == LOW)
  {
    digitalWrite(32, LOW);               // Alıcı kısmını, sinyal kalmayacak şekilde topraklıyoruz.
    digitalWrite(27, LOW);               // Verici kısmınıda aynı şekilde topraklıyoruz.
    delayMicroseconds(2);                     // Sinyallerin yerine oturması için 2 mikro saniye bekliyoruz.
    digitalWrite(27, HIGH);              // Gönderici kısmını açıyoruz.
    delayMicroseconds(10);                    // 10 mikro saniye bekleme veriyoruz.
    digitalWrite(27, LOW);               // Kapatıyoruz.

    SURE = pulseIn(32, HIGH);            // Gönderilen sinyalin geri gelme süresini ölçüyoruz.
    MESAFE = (SURE / 2.0) * 0.0343;           // Giden ve gelen sesin arasındaki süreden faydalanarak, cismin uzaklığını hesaplıyoruz.

    if (MESAFE >= 400 || MESAFE <= 3)           // Ölçülen mesafe menzil dışında kalıyor ise;
    {
      Serial.println(" - Menzil Dışı!");         // Seri ekrana bilgilendirme mesajı gönderdik.
      lcd.setCursor(0, 1);
      lcd.print("    Menzil Disi!    ");

      JoystickButonDurum = digitalRead(Joystick_Buton);
      if (JoystickButonDurum == HIGH)
      {
        break;
      }
    }
    else  if (MESAFE < 400 || MESAFE > 3)            // Eğer menzil içerisinde ise;
    {

      Serial.print("Mesafe: ");               // Seri ekrana ölçülen mesafe için bilgilendirme mesajı gönderdik.
      Serial.print(MESAFE, 1);                // Ölçülen mesafeyi, virgülden sonra bir basamak yazdırmak için sınırlandırıyoruz.
      Serial.println(" cm");                  // Ölçülen değerin birimini seri ekranda yazıyoruz.
      lcd.setCursor(2, 1);
      lcd.print("Mesafe: ");
      lcd.print(MESAFE);
      lcd.setCursor(16, 1);
      lcd.print(" cm");
      delay(100);
    }
    JoystickButonDurum = digitalRead(Joystick_Buton);
    delay(50);
  }

  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("TEBRIKLER ! ");
  delay(250);
  lcd.setCursor(1, 2);
  lcd.print("Ultrasonik Sensor");
  lcd.setCursor(2, 3);
  lcd.print("Testini Gectin !");

  ONAY_SESI();
  delay(2500);
}
//---------------------------------------   // DC MOTOR MODULCUGU   ---------------------------------------------------

void M_DC_Motor()
{
  lcd.clear();
  TEK_SES();
  lcd.setCursor(3, 0);
  lcd.print("15 - DC Motor");
  delay(250);
  lcd.setCursor(5, 1);
  lcd.print("(Neopixel)");

  GECIS_ONAYI();

  lcd.clear();
  lcd.setCursor(8, 0);
  lcd.print("Durum");
  lcd.setCursor(0, 3);
  lcd.print("Siradaki -> JOYSTICK");


  JoystickButonDurum = digitalRead(Joystick_Buton);
  while (JoystickButonDurum == LOW)
  {
    Serial.println("Sağa Dönüyor..");
    lcd.setCursor(0, 1);
    lcd.print("  Saga Donuyor..  ");
    digitalWrite(26, HIGH);            // Motorumuzun birinci pinine güç vererek devreye sokuyoruz.
    digitalWrite(27, LOW);             // Motorumuzun diğer pinini devre dışı bırakarak bir taraftan ilerlemesini sağlıyoruz.
    delay(2000);

    JoystickButonDurum = digitalRead(Joystick_Buton);

    Serial.println("Duruyor!");
    lcd.setCursor(0, 1);
    lcd.print("      DURUYOR       ");
    digitalWrite(26, LOW);             // Motorları durduruyoruz.
    digitalWrite(27, LOW);             // Motorları durduruyoruz.
    delay(3000);

    JoystickButonDurum = digitalRead(Joystick_Buton);

    Serial.println("Sola Dönüyor..");
    lcd.setCursor(0, 1);
    lcd.print("  Sola Donuyor..  ");
    digitalWrite(26, LOW);             // Motorumuzun birinci pinini devre dışı bırakıyoruz.
    digitalWrite(27, HIGH);            // Motorumuzun diğer pinini devreye sokarak bir taraftan ilerlemesini sağlıyoruz.
    delay(2000);

    JoystickButonDurum = digitalRead(Joystick_Buton);

    Serial.println("Duruyor!");
    lcd.setCursor(0, 1);
    lcd.print("      DURUYOR       ");
    digitalWrite(26, LOW);             // Motorları durduruyoruz.
    digitalWrite(27, LOW);             // Motorları durduruyoruz.
    delay(3000);

    JoystickButonDurum = digitalRead(Joystick_Buton);
    delay(50);
  }

  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("TEBRIKLER ! ");
  delay(250);
  lcd.setCursor(8, 2);
  lcd.print("DC Motor");
  lcd.setCursor(2, 3);
  lcd.print("Testini Gectin !");

  ONAY_SESI();
  delay(2500);

}

//---------------------------------------   // NTC MODULCUGU   ---------------------------------------------------
/*
  void M_NTC()
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
  //---------------------------------------   // HAREKET SENSORU MODULCUGU   ---------------------------------------------------

  void M_Hareket_Sensoru()
  {
  Sensor_Durumu = digitalRead(PIR);         // Başlangıçta sensörden bilgi okumak için komut veriyoruz.

  if (Sensor_Durumu == HIGH)                // Eğer sensörümüz herhangi bir hareket algılarsa;
  {
    Serial.println("Hareket Algılandı !");  // Hareketin algılandığına dair bilgiyi seri ekranına yazdırıyoruz.
  }

  delay(100);                               // Daha kaliteli bir ölçüm yapabilmek için,
  // her okumadan sonra saniyenin onda biri kadar
  // bekleme süresi ekledik.
  }
  //---------------------------------------   // STEP MOTOR MODULCUGU   ---------------------------------------------------

  void M_Step_Motor()
  {
  Serial.println("Saat Yönünde İlerliyor");           // Seri Ekrana Bilgilendirme Mesajı Gönderdik.
  for (int i = 0; i < 20; i++)                        // 20 Tur Saat Yönünde Hareket Etmesi İçin Komut Veriyoruz.
  {
    Step_Motorum.step(ADIM_SAYISI);                   // Bu Hareket Miktarı Motorun Desteklediği Adım Sayısı Kadar Olması Gerekiyor.
  }
  delay(500);                                         // Durduğunu Anlamak İçin Hareket Sonunda Yarım Saniye Bekleme Süresi Ekliyoruz.

  Serial.println("Saat Yönünün Tersine İlerliyor");   // Seri Ekrana Bilgilendirme Mesajı Gönderdik.
  for (int i = 0; i < 10; i++)                        // 10 Tur Saat Yönünün Tersinde Hareket Etmesi İçin Komut Veriyoruz.
  {
    Step_Motorum.step(-ADIM_SAYISI);                  // Bu Hareket Miktarı Motorun Desteklediği Adım Sayısı Kadar Olması Gerekiyor.
  }
  delay(500);                                         // Durduğunu Anlamak İçin Hareket Sonunda Yarım Saniye Bekleme Süresi Ekliyoruz.

  }
  //---------------------------------------   // GAZ DUMAN MODULCUGU   ---------------------------------------------------

  void M_Gaz_Duman()
  {

  }

  //---------------------------------------   // MİKROFON MODULCUGU   ---------------------------------------------------

  void M_Mikrofon()
  {

  }
*/
//---------------------------------------   // TEST SONU KODU   ---------------------------------------------------

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
}

//---------------------------------------   // TUSA BASMA ONAYI   ---------------------------------------------------

void GECIS_ONAYI()
{
  JoystickButonDurum = digitalRead(Joystick_Buton);
  while (JoystickButonDurum == LOW)
  {
    i = i + 1;
    if (i < 15)
    {
      lcd.setCursor(0, 3);                            // İmleci, yazmak istediğimiz koordinata yönlendiriyoruz.
      lcd.print("Joystick'e Basiniz..");              // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
    }
    if (i >= 15)
    {
      lcd.setCursor(0, 3);                            // İmleci, yazmak istediğimiz koordinata yönlendiriyoruz.
      lcd.print("                    ");             // Ekranda yazmasını istediğimiz yazıları yolluyoruz.
    }
    if (i == 30)
    {
      i = 0;
    }
    JoystickButonDurum = digitalRead(Joystick_Buton);
  }
  TEK_SES();
  delay(200);
  JoystickButonDurum = digitalRead(Joystick_Buton);
}

//---------------------------------------   // SESLER   ---------------------------------------------------

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

//---------------------------------------   // XXXXXXXXXXXXX   ---------------------------------------------------
