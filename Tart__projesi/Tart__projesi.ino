#define ag_ismi "Elmas iphone6"
#define ag_sifresi "1234567890"
#define IP "184.106.153.149"    //thingspeak.com IP adresi

#include "HX711.h"

HX711 scale;

int inPin = 2; //Button giris input degeri
int val = 0;
float tartiVerisi = 0;
void setup() {
  Serial.begin(38400);
  pinMode(inPin, INPUT);// inPin degerinin giris olarak tanımlandigı belirtildi.
  pinMode(9, OUTPUT); //beep sesi cikisi
  
  Serial.println("HX711 Demo");
  

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
  delay(1000);
  scale.power_up();
}
void beep(unsigned char delayms){
  analogWrite(9, 20);      // Almost any value can be used except 0 and 255
  delay(delayms);          // wait for a delayms ms
  analogWrite(9, 0);       // 0 turns it off
  delay(delayms);          // wait for a delayms ms   
} 

