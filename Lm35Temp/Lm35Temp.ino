#include <LiquidCrystal.h>
#include <Math.h>

float okunanSicaklik = 1.123;
int sensorPin = A0;
int role = 7;

LiquidCrystal lcd(12,11,5,4,3,2);

void setup() {
//LCD nin ozelligini belirtiyoruz
lcd.begin(20,4);

//roleye cikis baglantısı oldugu tanimlaniyor
pinMode(role,OUTPUT);

}

void loop() {
okunanSicaklik = analogRead(sensorPin);
okunanSicaklik = okunanSicaklik * 0.48828125 ;
lcd.setCursor(0 , 0);
lcd.print("Sicaklik: ");
lcd.setCursor(0 , 1);
lcd.print(okunanSicaklik,2);
lcd.print(" ");
lcd.print((char)223);
lcd.print("C");


if (okunanSicaklik < 26) {
digitalWrite(role,HIGH);
} else {
digitalWrite(role,LOW);
}

delay(500);
lcd.clear();

}
