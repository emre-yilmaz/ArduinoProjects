#define ag_ismi "Elmas iphone6"
#define ag_sifresi "1234567890"
#define IP "184.106.153.149"    //thingspeak.com IP adresi

#include "HX711.h"

HX711 scale;

int inPin = 2; //Button giris input degeri
int val = 0;
float tartiVerisi = 0;
void setup() {
  
  Serial.begin(115200);
  Serial.println("AT");
  
  pinMode(inPin, INPUT);// inPin degerinin giris olarak tanımlandigı belirtildi.
  pinMode(9, OUTPUT); //beep sesi cikisi

  delay(3000); //ESP ile iletişim için 3 saniye bekliyoruz.
  
if(Serial.find("OK")){         //esp modülü ile bağlantıyı kurabilmişsek modül "AT" komutuna "OK" komutu ile geri dönüş yapıyor.
     Serial.println("AT+CWMODE=1"); //esp modülümüzün WiFi modunu STA şekline getiriyoruz. Bu mod ile modülümüz başka ağlara bağlanabilecek.
     delay(2000);
     String baglantiKomutu=String("AT+CWJAP=\"")+ag_ismi+"\",\""+ag_sifresi+"\"";
    Serial.println(baglantiKomutu);
     delay(5000);
 }
  
  Serial.println("Initializing the scale");
  // parameter "gain" is ommited; the default value 128 is used by the library
  // HX711.DOUT	- pin #A1
  // HX711.PD_SCK	- pin #A0
  scale.begin(A1, A0);
  Serial.println(scale.read());			// print a raw reading from the ADC
  Serial.println(scale.read_average(20));  	// print the average of 20 readings from the ADC
  Serial.println(scale.get_value(5));		// print the average of 5 readings from the ADC minus the tare weight (not set yet)
  Serial.println(scale.get_units(5), 1);	// print the average of 5 readings from the ADC minus tare weight (not set) divided
						// by the SCALE parameter (not set yet)

  scale.set_scale(2280.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();				        // reset the scale to 0

  Serial.println(scale.read());                 // print a raw reading from the ADC
  Serial.println(scale.read_average(20));       // print the average of 20 readings from the ADC
  Serial.println(scale.get_value(5));		// print the average of 5 readings from the ADC minus the tare weight, set with tare()
  Serial.println(scale.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided
						// by the SCALE parameter set with set_scale

  Serial.println("Readings:");
}

void loop() {
  val = digitalRead(inPin);

  if (val == HIGH) {   
    scale.set_scale(2280.f);
     scale.tare();
     beep(200);
  }
  Serial.print("one reading:\t");
  Serial.print(scale.get_units(), 1);
  Serial.print("\t| average:\t");
  Serial.println(scale.get_units(10)/10, 1);
  tartiVerisi = scale.get_units(2)/10, 1 ;
  scale.power_down();			        // put the ADC in sleep mode
  send_data(tartiVerisi);
  delay(1000);
  scale.power_up();
}
void beep(unsigned char delayms){
  analogWrite(9, 20);      // Almost any value can be used except 0 and 255
  delay(delayms);          // wait for a delayms ms
  analogWrite(9, 0);       // 0 turns it off
  delay(delayms);          // wait for a delayms ms   
}
void send_data(float data){
 Serial.println(String("AT+CIPSTART=\"TCP\",\"") + IP + "\",80");  //thingspeak sunucusuna bağlanmak için bu kodu kullanıyoruz. 
                                                                   //AT+CIPSTART komutu ile sunucuya bağlanmak için sunucudan izin istiyoruz. 
                                                                   //TCP burada yapacağımız bağlantı çeşidini gösteriyor. 80 ise bağlanacağımız portu gösteriyor
 delay(1000);
  if(Serial.find("Error")){     //sunucuya bağlanamazsak ESP modülü bize "Error" komutu ile dönüyor.
   Serial.println("AT+CIPSTART Error");
    return;
  }
  
 String yollanacakkomut = "GET /update?key=E0P82I3TVW0KXPKD&field1=";   // Burada 64T0OS3R1OEAYUML yazan kısım bizim API Key den aldığımız Key. Siz buraya kendi keyinizi yazacaksınız.
 yollanacakkomut += (float(data));                                      // Burada ise sıcaklığımızı float değişkenine atayarak yollanacakkomut değişkenine ekliyoruz.
 yollanacakkomut += "\r\n\r\n";                                             // ESP modülümüz ile seri iletişim kurarken yazdığımız komutların modüle iletilebilmesi için Enter komutu yani
  delay(3000);                                                                                // /r/n komutu kullanmamız gerekiyor.
 
 Serial.print("AT+CIPSEND=");                    //veri yollayacağımız zaman bu komutu kullanıyoruz. Bu komut ile önce kaç tane karakter yollayacağımızı söylememiz gerekiyor.
 Serial.println(yollanacakkomut.length()+2);       //yollanacakkomut değişkeninin kaç karakterden oluştuğunu .length() ile bulup yazırıyoruz.
 
 delay(1000);
 
 if(Serial.find(">")){                           //eğer sunucu ile iletişim sağlayıp komut uzunluğunu gönderebilmişsek ESP modülü bize ">" işareti ile geri dönüyor.
                                                 // arduino da ">" işaretini gördüğü anda sıcaklık verisini esp modülü ile thingspeak sunucusuna yolluyor.
 Serial.print(yollanacakkomut);
 Serial.print("\r\n\r\n");
 }
 else{
 Serial.println("AT+CIPCLOSE");
 }
}

