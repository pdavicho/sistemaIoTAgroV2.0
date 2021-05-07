/***************************************************************************************************************
 *  IoT_Agricultura v2.0 usando NodeMCU ESP-12  
 *  DHT22 ==> pin D3 (Temperatura Ambiente y Humedad Relativa)
 *  Sensor de Suelo ==> pin A0
 *  OLED Display SCL==> pin D1 ; SDA==>pin D2
 *  OLED inicia con parámetros automáticos
 *  Control Manual 3 botones 
 *    1 ON/OFF Lampara
 *    2 ON/OFF BOMBA
 *    3 ON/OFF Modo Automático/Actualizacion de Sensores
 *  Control Automatico dependiente de variables                  
 *  Lectura de datos de los sensores para Blynk app
 *  Sistema de Control, Almacenamiento de Informacion y Monitoreamiento via Thinger
 ********************************************************************************************************************************/
#define SW_VERSION "IoT-Agro 2.0_dm"
#include "variables.h" // esp pines

/*ESP & Thinger*/
#define _DEBUG_
#include <ESP8266WiFi.h>
#include <ThingerESP8266.h>

/*Thinger Credenciales*/
#define USERNAME "pdavicho"
#define DEVICE_ID "agro_final"
#define DEVICE_CREDENTIAL "Pi2021loto"

/*Wifi Credenciales*/
#define SSID "TP-Link_52D6"
#define SSID_PASSWORD "Dav2108iD"

/*TIMER*/
#include <SimpleTimer.h>
SimpleTimer timer;

/*OLED*/
#include <ACROBOTIC_SSD1306.h>
#include <SPI.h>
#include <Wire.h>

/*DHT22*/
#include "DHT.h"
DHT dht(DHTPIN, DHTTYPE);

/*DS18B20 Sensor de Temperatura*/
#include <OneWire.h>
#include <DallasTemperature.h>
OneWire oneWire (ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);

/*Thinger Modulo*/
ThingerESP8266 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);
/*****************************************************************/
/*****************************************************************/
void setup() {

  Serial.begin(115200);
  pinMode(BUILTIN_LED, OUTPUT);
  delay(10);
  Serial.println("IoT-Agricultura");
  Serial.println("... Inicializando");
  Serial.println(" ");
  
  pinMode(BOMBA_PIN, OUTPUT);
  pinMode(LAMP_PIN, OUTPUT);
  pinMode(BOMBA_ON_BOTON, INPUT_PULLUP);
  pinMode(LAMP_ON_BOTON, INPUT_PULLUP);
  pinMode(SENSORES_LEER_BOTON, INPUT_PULLUP);
  pinMode(soilMoisterVcc, OUTPUT);

  oledInicio();
  dht.begin();
  DS18B20.begin();
  thing.add_wifi(SSID, SSID_PASSWORD);

  // digital pin control example (i.e. turning on/off a light, a relay, configuring a parameter, etc)
  thing["led"] << digitalPin(BUILTIN_LED);

  thing["bomba"] << [](pson& in){
    digitalWrite(BOMBA_PIN, in ? HIGH : LOW);
  };//fin bomba

  thing["lampara"] << [](pson& in){
    digitalWrite(LAMP_PIN, in ? HIGH : LOW);
  };//fin lampara
 
  digitalWrite(soilMoisterVcc, LOW);

  esperarBotonPush(MOSTRAR); //Esperar presion del Boton
  oled.clearDisplay();
  empezarTimer();
}//fin setup

void loop() {
  timer.run(); //Inicializar Simple Timer
  thing.handle(); // Inicializar thing
}//fin loop
/***************************************************
* Leer comandos locales (bomba y lampara son normalmente "HIGH")
****************************************************/
void leerLocalCmd()
{
  boolean digiValor = debounce(BOMBA_ON_BOTON);
  if(!digiValor)
  {
    bombaStatus = !bombaStatus;
    aplyCmd();
  }
  digiValor = debounce(LAMP_ON_BOTON);
  if(!digiValor)
  {
    lampStatus = !lampStatus;
    aplyCmd();
  }
  digiValor = debounce(SENSORES_LEER_BOTON);
  if(!digiValor)
  {
    apagarOLED = !apagarOLED;
    if(!apagarOLED)
    {
      oled.setTextXY(0,0); oled.putString("Act..SENSORES");
      obtenerDHTdata();
      obtenerSueloMoisterData();
      obtenerSueloTempData();
      oledInicio();
      mostrarDatos();
    }else oled.clearDisplay();
  }
 }
/***************************************************
* Recibir comandos y actuar
****************************************************/
void aplyCmd()
{
  if(bombaStatus == 1)
  {
    digitalWrite(BOMBA_PIN, HIGH);
    if(!apagarOLED) mostrarDatos();
  }
  else
  {
    digitalWrite(BOMBA_PIN, LOW);
    if(!apagarOLED) mostrarDatos();
  }
  if(lampStatus == 1)
  {
    digitalWrite(LAMP_PIN, HIGH);
    if(!apagarOLED) mostrarDatos();
    //LAMPs.on();
    //LAMPa.on();
  }
  else
  {
    digitalWrite(LAMP_PIN, LOW);
    if(!apagarOLED) mostrarDatos();
    //LAMPs.off();
    //LAMPa.off();
  }
}
/***************************************************
* Control Automatico basado en la lectura de los sensores
****************************************************/
void autoControlAgro(void)
{
  if(sueloMoister < SUELO_SECO)
  {
    turnONBomba();
  }
  if(aireTemp < TEMP_FRIA)
  {
    turnONLamp();
  }
}
/***************************************************
* Funcion encender BOMBA
****************************************************/
void turnONBomba()
{
  bombaStatus = 1;
  aplyCmd();
  delay(TIME_BOMBA_ON * 1000);
  bombaStatus = 0;
  aplyCmd();
}
/***************************************************
* Funcion encender LAMPARA
****************************************************/
void turnONLamp()
{
  lampStatus = 1;
  aplyCmd();
  delay(TIME_LAMP_ON * 1000);
  lampStatus = 0;
  aplyCmd();
}
/***************************************************
* Enviar informacion a Thing
****************************************************/
void enviarDatos()
{
  thing["dht22"] >> [](pson& out){
    out["humedad"] = dht.readHumidity();
    out["temperatura"] = dht.readTemperature();
  };//fin dht

  thing["suelo"] >> [](pson& out){
    out["sueloMoister"] = sueloMoister;
  };//fin suelo

  thing["tempExt"] >> [](pson& out){
    out["DSBtemp"] = sueloTemp;
  };//fin tempExt

}
























 
