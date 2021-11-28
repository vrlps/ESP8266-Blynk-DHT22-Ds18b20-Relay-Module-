#define BLYNK_PRINT Serial

#include <SPI.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Adafruit_Sensor.h>



char auth[] = ""; 
char ssid[] = ""; 
char pass[] = "";  
#define DHTPIN 2
#define DHTTYPE DHT22
#define ONE_WIRE_BUS 14

DHT dht(DHTPIN, DHTTYPE);
BlynkTimer timer;
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

float temp, temp1; 

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  
  Blynk.virtualWrite(V5, h);
  Blynk.virtualWrite(V6, t);
}

void sendTemps()
    {
  sensors.requestTemperatures();
  int temp  = sensors.getTempCByIndex(0);
  //int temp1  = sensors.getTempCByIndex(1);
  Blynk.virtualWrite(V1, temp);
  //Blynk.virtualWrite(V2, temp1); 
    }
    
void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  timer.setInterval(1000L, sendSensor);
  sensors.begin();
}

void loop()
{
  Blynk.run();
  timer.run();
  sendTemps();
}
