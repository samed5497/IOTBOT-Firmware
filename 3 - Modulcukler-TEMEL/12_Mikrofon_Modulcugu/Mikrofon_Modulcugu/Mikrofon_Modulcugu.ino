/*
                                     ///////////////////////////////////////////////////////
                                     /////////   IoT BOT Test Yazılımları Serisi   /////////
                                     //////////////   MODÜLCÜK TESTLERİ   //////////////////
                                                          Mikrofon
*/

//---------------------------------------      //LA LA LA LAAAA... SES VERELİM        ------------------------------------------------------

//---------------------------------------   // İLK TANIMLAMALAR VE KÜTÜPHANE EKLEME   ------------------------------------------------------

int Mikrofon = 27;                          // Potansiyometremizin bağlı olduğu pini tanımladık.
int SesDegeri;                              // Potansiyometreden okunan değerleri integer(Tam sayı) olarak tanımladık.

//---------------------------------------   // SADECE İLK AÇILIŞTA BİR KERE ÇALIŞACAK KISIM   ---------------------------------------------

void setup()
{
  Serial.begin(115200);                     // Seri haberleşmeyi "115200" bandında başlattık.
  Serial.println("     IoT BOT    ");       // Seri ekrana bilgilendirme mesajı gönderdik.
  Serial.println("Mikrofon Testi...");
  pinMode(Mikrofon,  INPUT);                 // Potansiyometreyi veri aldığı için giriş olarak belirledik.
}

//---------------------------------------   // SÜREKLİ ÇALIŞACAK DÖNGÜ İÇİNDEKİ KISIM   ----------------------------------------------------
void loop()
{
  SesDegeri = analogRead(Mikrofon);         // Encoderdan sürekli analog olarak değer okuma komutu veriyoruz.
  Serial.print("Duyulan Değer: ");          // Seri ekrana bilgilendirme mesajı gönderdik.
  Serial.println(SesDegeri);                // Okuduğumuz değeri seri ekrana bilgilendirme mesajı olarak gönderdik.

  delay(100);                               // Daha kesin bir ölçüm yapabilmek için, 
                                            // her okumadan sonra saniyenin onda biri kadar
                                            // bekleme süresi ekledik.  
}
