/*Parámetros para Control Automático*/
#define SUELO_SECO 66
#define SUELO_HUM 85
#define TEMP_FRIA 12
#define TEMP_CAL 22
#define TIME_BOMBA_ON 15
#define TIME_LAMP_ON 15

/*TEMPORIZADOR en seg*/
#define LEER_BOTON_TM 1L
#define LEER_SUELO_TEMP_TM 2L
#define LEER_SUELO_HUM_TM 10L
#define LEER_AIRE_DATOS_TM 2L
#define ENVIAR_DATOS_TM 10L
#define CTRL_AUTO_TM 60L

/*OLED*/
boolean apagarOLED = 1;
#define MOSTRAR 30

/*DHT22*/
#define DHTPIN D3
#define DHTTYPE DHT22
float aireHum = 0;
float aireTemp = 0;

/*Sensor Suelo*/
#define soilMoisterPin A0
#define soilMoisterVcc D8
int sueloMoister = 0;

/*DS18B20 Sensor de Temperatura*/
#define ONE_WIRE_BUS D5
float sueloTemp;

/*Relays*/
#define BOMBA_PIN D6
#define LAMP_PIN D7
boolean bombaStatus = 0;
boolean lampStatus = 0;

/*Botones*/
#define BOMBA_ON_BOTON D9 //push-button
#define LAMP_ON_BOTON D10 //push-button
#define SENSORES_LEER_BOTON D4 //push-button
