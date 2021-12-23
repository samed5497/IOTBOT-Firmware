/*
                                  ///////////////////////////////////////////////////////
                                  /////////   IoT BOT Test Yazılımları Serisi   /////////
                                  ///////////////////////////////////////////////////////
                                                   AKILLI RÖLE MODÜLCÜĞÜ
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

#define UYGULAMA "Akıllı Röle Modülcüğü"


int ROLE_1 = 12;                                      // Rolenin Bağlı Olduğu Pini 12. Pin Tanımladık.
int ROLE_2 = 13;                                      // Rolenin Bağlı Olduğu Pini 12. Pin Tanımladık.

//---------------------------------------   // SADECE İLK AÇILIŞTA BİR KERE ÇALIŞACAK KISIM   ---------------------------------------------

void setup()
{
  Serial.begin(115200);                               // Seri haberleşmeyi "115200" bandında başlattık.

  Serial.println("     IoT BOT    ");                 // Seri ekrana bilgilendirme mesajı gönderdik.
  Serial.println(UYGULAMA);

  pinMode(ROLE_1, OUTPUT);                            // Röleyi çıkış pini olarak ayarladık.
  pinMode(ROLE_2, OUTPUT);                            // Röleyi çıkış pini olarak ayarladık.
  pinMode(2, OUTPUT);                                 // İşlemcinin üzerindeki ledi çıkış olarak tanımladık.

  digitalWrite(ROLE_1, LOW);                          // Sinyallerin anlaşılması için iki röleyide kapalı konuma getirdik.
  digitalWrite(ROLE_2, LOW);                          // Sinyallerin anlaşılması için iki röleyide kapalı konuma getirdik.
}

//---------------------------------------   // SÜREKLİ ÇALIŞACAK DÖNGÜ İÇİNDEKİ KISIM   ---------------------------------------------------

void loop()
{
  digitalWrite(ROLE_1, HIGH);                         // 1. Röleyi tetikliyoruz. 
  digitalWrite(2, HIGH);                              // Ledi açıyoruz.
  delay(2000);                                        // Sinyallerin anlaşıabilmesi için araya bekleme süresi koyuyoruz. 
  digitalWrite(ROLE_1, LOW);                          // 1. Röleyi devre dışı bırakıyoruz.  
  delay(1000);                                        // Sinyallerin anlaşıabilmesi için araya bekleme süresi koyuyoruz. 
  
  digitalWrite(ROLE_2, HIGH);                         // 2. Röleyi tetikliyoruz. 
  digitalWrite(2, HIGH);                              // Ledi açıyoruz.
  delay(2000);                                        // Sinyallerin anlaşıabilmesi için araya bekleme süresi koyuyoruz. 
  digitalWrite(ROLE_2, LOW);                          // 2. Röleyi devre dışı bırakıyoruz.  
  delay(1000);                                        // Sinyallerin anlaşıabilmesi için araya bekleme süresi koyuyoruz. 
  
  digitalWrite(2, HIGH);                              // Ledi açıyoruz.
  digitalWrite(ROLE_1, HIGH);                         // 1. Röleyi tetikliyoruz. 
  digitalWrite(ROLE_2, HIGH);                         // 2. Röleyi tetikliyoruz. 
  delay(3000);                                        // Sinyallerin anlaşıabilmesi için araya bekleme süresi koyuyoruz. 
  
  digitalWrite(2, LOW);                               // Ledi açıyoruz.
  digitalWrite(ROLE_1, LOW);                          // 1. Röleyi devre dışı bırakıyoruz.  
  digitalWrite(ROLE_2, LOW);                          // 2. Röleyi devre dışı bırakıyoruz.  
  delay(3000);                                        // Sinyallerin anlaşıabilmesi için araya bekleme süresi koyuyoruz. 
}
