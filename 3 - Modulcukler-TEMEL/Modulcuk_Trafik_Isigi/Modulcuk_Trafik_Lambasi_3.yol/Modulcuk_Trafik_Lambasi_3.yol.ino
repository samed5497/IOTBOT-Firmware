/*
                                     ///////////////////////////////////////////////////////
                                     /////////   IoT BOT Test Yazılımları Serisi   /////////
                                     //////////////   MODÜLCÜK TESTLERİ   //////////////////
                                                        TRAFİK IŞIĞI
*/
//---------------------------------------   GEÇERKEN TRAFİK IŞIĞINA DİKKAT ETTİN Mİ?  ------------------------------------------------------ 

//---------------------------------------   // İLK TANIMLAMALAR VE KÜTÜPHANE EKLEME   ------------------------------------------------------


int KIRMIZI = 32;                           // Kırmızı ledin bağlı olduğu pini tanımladık.
int SARI    = 26;                           // Sarı ledin bağlı olduğu pini tanımladık.
int YESIL   = 25;                           // Yeşil ledin bağlı olduğu pini tanımladık.


//---------------------------------------   // SADECE İLK AÇILIŞTA BİR KERE ÇALIŞACAK KISIM   ---------------------------------------------

void setup()
{
  Serial.begin(115200);                     // Seri haberleşmeyi "115200" bandında başlattık.
  Serial.println("     IoT BOT    ");       // Seri ekranına bilgilendirme mesajı gönderdik.
  Serial.println("Trafik Işığı Testi...");
  
  pinMode(KIRMIZI, OUTPUT);                 // Ledimizi sonuç vediği için çıkış olarak belirledik.
  pinMode(SARI,    OUTPUT);                   // Ledimizi sonuç vediği için çıkış olarak belirledik.
  pinMode(YESIL,   OUTPUT);                  // Ledimizi sonuç vediği için çıkış olarak belirledik.                                          
}

//---------------------------------------   // SÜREKLİ ÇALIŞACAK DÖNGÜ İÇİNDEKİ KISIM   ---------------------------------------------------

void loop()
{
     Yazdirma(KIRMIZI);
     Yazdirma(SARI);
     Yazdirma(YESIL);
} 


void Yazdirma(int a){
  digitalWrite(a, HIGH);                                                                     // İlk önce kırmızı ışığı yaktık. 
  if(a==25)                                                                                  // Seri ekrana bilgilendirme mesajı gönderdik.
    Serial.println("Kırmızı Yanıyor.DURUN");
  else if(a==26)
    Serial.println("Sarı Yanıyor.DİKKAT");
  else
    Serial.println("Yeşil Yanıyor.GEÇİN");
  delay(2000);                                                                               // Bekleme süresi ekledik.
  digitalWrite(a, LOW); 
}
