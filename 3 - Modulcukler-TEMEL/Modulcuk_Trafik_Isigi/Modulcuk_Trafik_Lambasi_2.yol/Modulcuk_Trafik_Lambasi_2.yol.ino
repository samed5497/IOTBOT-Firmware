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

int LEDLER[]={32,26,25};


//---------------------------------------   // SADECE İLK AÇILIŞTA BİR KERE ÇALIŞACAK KISIM   ---------------------------------------------

void setup()
{
  Serial.begin(115200);                     // Seri haberleşmeyi "115200" bandında başlattık.
  Serial.println("     IoT BOT    ");       // Seri ekranına bilgilendirme mesajı gönderdik.
  Serial.println("Trafik Işığı Testi...");
  
  for (int i = 0; i < 3; i++) {            
    pinMode(LEDLER[i], OUTPUT);             // Ledlerimizi sonuç verdiği için çıkış olarak belirledik.
}                                              
}

//---------------------------------------   // SÜREKLİ ÇALIŞACAK DÖNGÜ İÇİNDEKİ KISIM   ---------------------------------------------------

void loop()
{
   for (int i = 0; i < 3; i++) {            
    digitalWrite(LEDLER[i], HIGH);           // Ledlerimizi sırayla yakıyoruz.
    if (LEDLER[i]== 25) { 
    Serial.println("Kırmızı Yanıyor. DURUN");
    }
    else if (LEDLER[i]== 26) { 
    Serial.println("Sarı Yanıyor. DİKKAT");
    }     
    else 
    Serial.println("Yeşil Yanıyor. GEÇİN");
    delay(2000);
    digitalWrite(LEDLER[i], LOW);
} 
}
