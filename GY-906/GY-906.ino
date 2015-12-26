//GY-906 MLX90614 sensor


#include <i2cmaster.h>
#include <LiquidCrystal.h>
#include <Math.h>


int role = 7;
LiquidCrystal lcd(12,11,5,4,3,2);

int adres = 0xb4; //  MLX90614 sensorun adresi
int erc = 0;      // PEC değerini tutan değişken
int daneH = 0;    // ikinci veri bytı
int daneL = 0;    // ilk veri baytı  
double tempnalsb = 0.02;  // degişken çarpanı
double sicaklik = 0; 

void setup(){

//roleye cikis baglantısı oldugu tanimlaniyor
pinMode(role,OUTPUT);

i2c_init();
//LCD nin ozelligini belirtiyoruz
lcd.begin(20,4);
}

void loop(){
  
 i2c_start_wait(adres+I2C_WRITE);     // kayıt modunda I2C iletişimi başlatın
  i2c_write(0x07);                     // Yaz değeri (Kayıt Tobj1 seçerek) 0x07 
  i2c_rep_start(adres+I2C_READ);       // yeniden I2C haberleşme 
  daneL = i2c_readAck();               // ilk veri baytı Oku
  daneH = i2c_readAck();               // ikinci veri byte Oku
  erc = i2c_readNak();                 // üçüncü veri (önemli olmayan) bayt Oku
  i2c_stop();                          // I2C ile iletimi bitir 
 
 
  sicaklik = (double)(((daneH & 0x007F) << 8) + daneL); //iki tek baytlık değişkenden oluşan 16-bitlik değişken
  sicaklik = sicaklik*tempnalsb; // bir bit üzerinde 0.02 K düşer bu işlemin sonucu, Kelvin cinsinden sıcaklıktır
 
  sicaklik = sicaklik - 273.15; // Santigrat derece donusumu
 
  lcd.setCursor(0,0);                 // Ekran satırı 
  lcd.print("Sicaklik = ");
  lcd.print(sicaklik);
  lcd.print(" ");
  lcd.write(0xDF);                    // Derece Sembolu
  lcd.print("C ");  
 

Serial.print("Celcius: ");
Serial.println(sicaklik);
/*
lcd.setCursor(0 , 0);
lcd.print("Sicaklik: ");
lcd.setCursor(0 , 1);
lcd.print("Selam");
lcd.print(" ");
lcd.print((char)223);
lcd.print("C");
*/
if (sicaklik < 26) { //röle devreye girme sıcaklıgı
digitalWrite(role,HIGH);
} else {
digitalWrite(role,LOW);
}

delay(1000); // Ekran yenileme Ms 
lcd.clear();


}
