/*
                                  ///////////////////////////////////////////////////////
                                  /////////   IoT BOT Test Yazılımları Serisi   /////////
                                  ///////////////////////////////////////////////////////
                                           RFID (Radyo Frekanslı Kimlik Okuyucu)
*/

//---------------------------------------          HADİ KODLAYALIM...       ----------------------------------------------------------------

//---------------------------------------   // İLK TANIMLAMALAR VE KÜTÜPHANE EKLEME   ------------------------------------------------------

#define UYGULAMA "RFID Testi"

int i = 0;                                            // Gidip gelen yazının animasyonu için oluşturulan değişken.

#include <Wire.h>                                     // I2C iletişim protokolünü kullanabilmek için gerekli kütüphaneyi ekliyoruz. 
#include <LiquidCrystal_I2C.h>                        // LCD ekran için gerekli olan kütüphaneyi ekliyoruz. 
LiquidCrystal_I2C lcd(0x27, 20, 4);                   // LCD ekranımızın özelliklerini giriyoruz.
                                                      // Bizim ekranımız 20 satır, 4 sütun karakter destekliyor.

#include <SPI.h>                                      // SPI haberleşme protokolünü ekledik.
#include <MFRC522.h>                                  // Sensör kütüphanemizi tanımladık.

MFRC522 rfid(5, 10);                                  // Sensörün işlemcimizde bağlı olduğu pinlerimizi tanımladık.
MFRC522::MIFARE_Key key;


byte nuidPICC[4];                                     // Kimlik bilgilerini depolamak için 4 Byte veri tanımladık.
long HEX_ID;

//---------------------------------------   // SADECE İLK AÇILIŞTA BİR KERE ÇALIŞACAK KISIM   ---------------------------------------------

void setup()
{
  Serial.begin(115200);                               // Seri haberleşmeyi "115200" bandında başlattık.
  lcd.init();                                         // LCD ekranı başlatma komutu gönderiyoruz.
  lcd.backlight();                                    // LCD ekranın arka plan aydınlatma ışığını açıyoruz.
  
  giris_animasyon();

  Serial.println("     IoT BOT    ");                 // Seri ekrana bilgilendirme mesajı gönderdik.
  Serial.println(UYGULAMA);

  SPI.begin();                                        // SPI haberleşme protokolünü başlattık.
  rfid.PCD_Init();                                    // Sensörümüzü baştattık.
  
}

//---------------------------------------   // SÜREKLİ ÇALIŞACAK DÖNGÜ İÇİNDEKİ KISIM   ---------------------------------------------------

void loop()
{

  if ( ! rfid.PICC_IsNewCardPresent())                // Yeni bir kart yok ise, "Döngüyü durdur" komutu verdik. 
  {
    return;
  }

  if ( ! rfid.PICC_ReadCardSerial())                  // Kimlik bilgilerinin okunup okunamadığını kontrol ettirdik. 
  {
    return;
  }
  
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);   // Okunulan kartın cinsini anlayıp
  Serial.print("Kart Tipi: ");                                     // Seri ekrana yazı yazdırıyoruz.
  lcd.setCursor(2, 2);
  lcd.print("Tipi: ");
  Serial.println(rfid.PICC_GetTypeName(piccType));                 // seri ekranda yazdırıyoruz.
  lcd.print(rfid.PICC_GetTypeName(piccType));
  
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&   //
      piccType != MFRC522::PICC_TYPE_MIFARE_1K   &&   // Okutulan kartın türünü eğer yapısıyla kontrol ediyoruz.
      piccType != MFRC522::PICC_TYPE_MIFARE_4K     )  //
  {
    Serial.println("Bu Kart Türü Desteklenmiyor.");   // Eğer sensörle uyumlu değilse, seri ekrana uyarı mesajı gönderiyoruz.
    lcd.setCursor(0, 2);
    lcd.print(" Desteklenmeyen Kart");
    return;                                           // Daha sonra tekrar döngünün başına dönüyoruz.
  }

  if (rfid.uid.uidByte[0] != nuidPICC[0] ||           //
      rfid.uid.uidByte[1] != nuidPICC[1] ||           // Son okutulan kart ile, daha önceden okutulan
      rfid.uid.uidByte[2] != nuidPICC[2] ||           // kartın kimlik numaralarını eğer yapısıyla karşılaştırıyoruz.
      rfid.uid.uidByte[3] != nuidPICC[3]    )         //
  {
    Serial.println("Yeni Kart Tespit Edildi!");       // Eğer kimlikler aynı değilse seri ekranda bunu bildiriyoruz.

    for (byte i = 0; i < 4; i++)                      // Yeni okutulan kartın kimlik bilgilerini kaydediyoruz.
    { //
      nuidPICC[i] = rfid.uid.uidByte[i];              // Okutulan bilgileri hafızaya kaydetme komutu veriyoruz.
    }

    Serial.println("Okunan Kartın Kimliği:");         // Seri ekrana bilgilendirme mesajı gönderdik.
    Serial.print("HEX Türünde    : ");                // Seri ekrana bilgilendirme mesajı gönderdik.
    printHex(rfid.uid.uidByte, rfid.uid.size);        // printHex ile seri ekranına HEX(Yazı) türünde bilgileri yazdırıyoruz.
    Serial.println();                                 // Seri ekranında alt sıraya geçmek için boş metin gönderdik.
    Serial.print("DECIMAL Türünde: ");                // Seri ekranına bilgilendirme mesajı gönderdik.
    printDec(rfid.uid.uidByte, rfid.uid.size);        // printDec ile seri ekranına DECIMAL(Sayı)türünde bilgilerini gönderdik.
    Serial.println();                                 // Seri ekranında alt sıraya geçmek için boş metin gönderdik.
    lcd.setCursor(3, 3);
    lcd.print("                ");
    lcd.setCursor(0, 3);
    lcd.print("ID: ");
    lcd.print(nuidPICC[0]);
    lcd.print(" ");
    lcd.print(nuidPICC[1]);
    lcd.print(" ");
    lcd.print(nuidPICC[2]);
    lcd.print(" ");
    lcd.print(nuidPICC[3]);
  }

  else                                                // Eğer kimlikler aynı ise, bunu seri ekranında belirtiyoruz.
  {
    Serial.println("Son Okutulan Kart İle Aynı!");
  }

  rfid.PICC_HaltA();                                  // Sürekli başa sarmamak için, kartı kaldırmadığımız sürece 
  rfid.PCD_StopCrypto1();                             // yeni okuma yapmayı durduruyoruz.

  Serial.println();                                   // Seri ekranında alt sıraya geçmek için boş metin gönderdik.
}

//-------------------------------------------------   // ANA DÖNGÜ İÇERİSİNDE BİR KERE GİRİLEN BÖLÜM   ------------------------------------------------------------------

void printHex(byte *buffer, byte bufferSize)          // DECIMAL olarak okunan kimlik numarasını, HEX türüne çevirme kodu.
{
  for (byte i = 0; i < bufferSize; i++)               //
  {                                                   //
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");      //
    Serial.print(buffer[i], HEX);                     //
  }                                                   //
}

//-------------------------------------------------   // ANA DÖNGÜ İÇERİSİNDE BİR KERE GİRİLEN BÖLÜM   ------------------------------------------------------------------

void printDec(byte *buffer, byte bufferSize)          // HEX olarak okunan kimlik numarasını, DECIMAL türüne çevirme kodu.
{
  for (byte i = 0; i < bufferSize; i++)               //
  {                                                   //
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");      //
    Serial.print(buffer[i], DEC);                     //
  }                                                   //
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

  lcd.setCursor(5, 1);
  lcd.print(UYGULAMA);
  delay(1000);
}

void yan_son_yazi()                                    // Yanıp sönen bilgilendirme mesajını hazırlıyoruz. 
{
  lcd.setCursor(4, 2);                                // İmleci, yazmak istediğimiz koordinata yönlendiriyoruz.
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
