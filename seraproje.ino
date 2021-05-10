int LDR_Pin = A2;
int toprak=A0;
int olcumsonuc;
#include "DHT.h"
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#define DHTPIN 9    
#define DHTTYPE DHT11  
DHT dht(DHTPIN, DHTTYPE);
int direnc=0;
float sayi=0;

LiquidCrystal_I2C lcd(0x27, 16, 2);
void setup() {
  Serial.begin(9600);
  dht.begin();
  lcd.init();
lcd.backlight();
}
void loop() {
 sicaklik();
 LDRR();
topraknem();
}
void sicaklik(){
  //delay(2000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("SENSORDEN OKUNAMADI."));
    return;
  }
  float hif = dht.computeHeatIndex(f, h);
  float hic = dht.computeHeatIndex(t, h, false);
   Serial.print(F("Nem: "));
  Serial.print(h);
  Serial.print(F("%  Sıcaklık: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.println();
  int isi=t;
  int nem=h;
  lcd.setCursor(0,0);
  lcd.print("ISI:");
  lcd.print(isi);
 lcd.print("C");
  lcd.setCursor(0,1);
  lcd.print("NEM:");
  lcd.print("%");
  lcd.print(nem); 
}

 
void LDRR(){
  int LDRReading = analogRead(LDR_Pin);
  Serial.print("ISIKDIRENC=");
Serial.println(LDRReading);
lcd.setCursor(8,0);
lcd.print("ISK:%");
int sayi=LDRReading;
float yuzde=sayi/10.23;
int a=yuzde;
if(a==100){
lcd.setCursor(13,0);
lcd.print(a);
}
else if(a>=10){
  lcd.setCursor(13,0);
  lcd.print(" ");
   lcd.setCursor(14,0);
lcd.print(a);
}
else{
  lcd.setCursor(13,0);
  lcd.print("  ");
   lcd.setCursor(15,0);
lcd.print(a);
}
}
void topraknem(){
  olcumsonuc=analogRead(toprak);
  Serial.print("TOPRAKDIRENC=");
  Serial.print(olcumsonuc);
  Serial.println();
  delay(500);
  int sayi=olcumsonuc;
  float yuzde=sayi/10.23;
  int sonuc=yuzde-100;
  int a=sonuc*-1;
  
if(a<10){
  lcd.setCursor(13,1);
  lcd.print("  ");
   lcd.setCursor(8,1);
lcd.print("TPRK:%");
  lcd.setCursor(15,1);
lcd.print(a);
}
else if(a<100){
  lcd.setCursor(13,1);
  lcd.print(" ");
   lcd.setCursor(8,1);
lcd.print("TPRK:%");
  lcd.setCursor(14,1);
lcd.print(a);
}

}
