

// Inkluderer biblotekene som blir brukt i koden:
#include <LiquidCrystal.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <SPI.h>
#include <SD.h>
#include <MQ135.h>
//Definerer type tempratur sensor og Pinen den er koblet til
#define DHTPIN 2
#define DHTTYPE DHT22
//Definerer signal Pinen for SD kort  
#define SD_CS_PIN 10

//Setter verdier for CO2 sensor 
const int ANALOGPIN = A0;
MQ135 gasPin = MQ135(ANALOGPIN);

int a = 0; //Start tiden
float x = (0.5); //minutter mellom hver måling
int y = 10000; //målinger

// Setter verdier for LCD skjermen og lager skjermen. Parametere: (RS, E, D4, D5, D6, D7):
const int rs = 8, en = 9, d4 = 5, d5 = 4, d6 = 3, d7 = 7;
LiquidCrystal lcd = LiquidCrystal(rs, en, d4, d5, d6, d7);

//Setter inn hvilke verdier som er inputen for tempratursensor 
DHT dht = DHT(DHTPIN, DHTTYPE);

//Lager en fil med navn myFile
File myFile;



void setup() {
  Serial.begin(9600);
//Starter komunikasjonen med arduinon via den serielle koblingen på 9600 

//Starter tempratur sensoren 
 dht.begin();
   // Spesifiserer LCD skjermen sit numer av linjer og kolloner
   lcd.begin(16, 2);

//Begynner komunikasjon med SD kortet og setter filen myfile til å skrive verdier
SD.begin(SD_CS_PIN);
myFile = SD.open("TEST.txt", FILE_WRITE);
pinMode(SD_CS_PIN, OUTPUT);

// Hvis myFile åpnes skrives det inn på Filen
if (!myFile){Serial.print("a");};
myFile.println("Writing to test.txt...");
myFile.close();

//Skriver navnene på verdiene til filen
myFile.print("minutter etter start: ");
myFile.print(" Humidity: ");
myFile.print(" % ");
myFile.print("Temperature: ");
myFile.print(" \xC2\xB0");
myFile.print("C | ");
myFile.println("CO2: ");

}

 
void loop() {
//Åpner filen myFile og gjør den klar for å bli skrevet til
myFile=SD.open("TEST.txt", FILE_WRITE);

//Måler verdiene for tempratur og luftfuktighet
float h = dht.readHumidity();

float t = dht.readTemperature();



 //Sjekker at målingene fra tempratur sensoren gikk fint
if (isnan(h) || isnan(t)) {
Serial.println("Failed to read from DHT sensor!");
return;
}

//Setter verdier for CO2
float co2ppm = gasPin.getPPM();

//Setter verdier for minutter som har gått
float mytime = (millis()/60000); 

//Skriver verdiene som er målt til myFile
myFile.print(mytime);
myFile.print(", ");
myFile.print(h);
myFile.print(", ");
myFile.print(t);
myFile.print(", ");
myFile.println(co2ppm);

//Skriver verdiene som er målt opp på LCD-skjermen 
lcd.setCursor(0, 0);
lcd.print("Temp:");
lcd.setCursor(5, 0);
lcd.print(t);
lcd.setCursor(0, 1);
lcd.print("C");
lcd.setCursor(2, 1);
lcd.print(co2ppm);
lcd.setCursor(8, 1);
lcd.print("m:");
lcd.setCursor(9, 1);
lcd.print(a);

//setter verdi for antall målinger
a=a+1  
//Lukker filen og lagrer data, setter en pause mellom målingene på antall minutter som er bestemt 
myFile.close();
delay(x*1000*60);
Serial.println(x*1000*60);

}
