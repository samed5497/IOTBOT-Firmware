/*
                                  ///////////////////////////////////////////////////////
                                  /////////   IoT BOT Test Yazılımları Serisi   /////////
                                  ///////////////////////////////////////////////////////
                                                   YARDIMCI MODÜLCÜK
*/

//---------------------------------------          HADİ KODLAYALIM...       ----------------------------------------------------------------

/*
  NOT: 
        1 - Karta yükleme yapmadan önce kart  yöneticisinden işlemciyi "ESP8266 Generic Module" seçiyoruz.
        2 - Kartın üzerindeki "BOOT" tuşuna basılı tutarken "RESET" tuşuna bir kere basıp butonları bırakıyoruz ve cihazımı yükleme moduna alıyoruz.
        3 - BOOT modunda bekleyen kartımızın uygun yükleme portunu seçtikten sonra yükle butonuna basıyoruz.
        4 - Yükleme işlemi bittikten sonra reset tuşuna basarak işlemcimizi yükleme modundan çıkartarak kodumuzun çalışmasını sağlıyoruz.
*/

//---------------------------------------   // İLK TANIMLAMALAR VE KÜTÜPHANE EKLEME   ------------------------------------------------------

#define UYGULAMA "YARDIMCI MODULCUK - Servo Motor Testi"


#include <Servo.h>                                                // Motor Kontrolü İçin Gerekli Olan Kütüphaneyi Çağırıyoruz. 

int Servo_PIN = 4;                                                // Motorun Bağlı Olduğu Pini 4. Pin Tanımladık. 4 - 5 - 12 - 13 - 14 Numaralı Pinlerden Herhangi Birine Bağlanabilir.

Servo Servo_Motorum;                                              // Servo Motorumuza Bir İsim Veriyoruz. Biz "Servo_Motorum" Dedik.

//---------------------------------------   // SADECE İLK AÇILIŞTA BİR KERE ÇALIŞACAK KISIM   ---------------------------------------------

void setup()
{
  Serial.begin(115200);                                           // Seri haberleşmeyi "115200" bandında başlattık.

  Serial.println("     IoT BOT    ");                             // Seri ekrana bilgilendirme mesajı gönderdik.
  Serial.println(UYGULAMA);

  Servo_Motorum.attach(Servo_PIN);                                // İsimlendiğimiz Motoru, Tanımladığımız Pine Bağladık.
  pinMode(2, OUTPUT);                                             // İşlemcinin üzerindeki ledi çıkış olarak tanımladık. 
}

//---------------------------------------   // SÜREKLİ ÇALIŞACAK DÖNGÜ İÇİNDEKİ KISIM   ---------------------------------------------------

void loop()
{
for (int Motor_ACISI = 0; Motor_ACISI <= 180; Motor_ACISI++)      // Servo Motorumuzu 0 Dereceden 180 Dereceye,
  {                                                               // Birer Açı Şeklinde Hareket Ettiriyoruz.
    digitalWrite(2, HIGH);                                        // Ledi açıyoruz.
    Servo_Motorum.write(Motor_ACISI);                             // Motorumuzun Hareketi Yapması İçin Onay Veriyoruz.
    Serial.print("Motor Açısı: ");                                // Bunu Seri Ekrana Bilgi Mesajı Olarak Gönder Komutu Veriyoruz.
    Serial.println(Motor_ACISI);                                  // Bunu Seri Ekrana Bilgi Mesajı Olarak Gönder Komutu Veriyoruz.
    delay(20);                                                    // Her Açı Hareketinden Sonra, Herhangi Bir Sıkışma Olmaması İçin Minik Bir Bekleme Süresi Koyuyoruz.
  }                                                                

  for (int Motor_ACISI = 180; Motor_ACISI >= 0; Motor_ACISI--)    // Servo Motorumuzu 180 Dereceden 0 Dereceye,
  {                                                               // Birer Açı Şeklinde Hareket Ettiriyoruz.
    digitalWrite(2, LOW);                                         // Ledi kapatıyoruz.
    Servo_Motorum.write(Motor_ACISI);                             // Motorumuzun Hareketi Yapması İçin Onay Veriyoruz.
    Serial.print("Motor Açısı: ");                                // Bunu Seri Ekrana Bilgi Mesajı Olarak Gönder Komutu Veriyoruz.
    Serial.println(Motor_ACISI);                                  // Bunu Seri Ekrana Bilgi Mesajı Olarak Gönder Komutu Veriyoruz.
    delay(20);                                                    // Her Açı Hareketinden Sonra, Herhangi Bir Sıkışma Olmaması İçin Minik Bir Bekleme Süresi Koyuyoruz.
  }       
}
