/***************************************************
 * Obtener DHT22 datos
 **************************************************/
void obtenerDHTdata(void)
{
  float tempIni = aireTemp;
  float humIni = aireHum;
  aireTemp = dht.readTemperature();
  aireHum = dht.readHumidity();
  if(isnan(aireHum) || isnan(aireTemp)) //Chequeo si hay alguna lectura 
  {
    Serial.println("Fallo lectura del Sensor DHT");
    aireTemp = tempIni;
    aireHum = humIni;
    return;
  }
}
/***************************************************
 *  Obtener Suelo Moister datos
 **************************************************/
void obtenerSueloMoisterData(void)
{
  sueloMoister = 0;
  digitalWrite(soilMoisterVcc, HIGH);
  delay(500);
  int N = 3;
  for(int i=0; i<N; i++)// leer el sensor N veces y obtener un promedio
  {
    sueloMoister += analogRead(soilMoisterPin);
    delay(150);
  }
  digitalWrite(soilMoisterVcc, LOW);
  sueloMoister = sueloMoister/N;
  sueloMoister = map(sueloMoister, 600, 0, 0, 100);  
}
/***************************************************
 *  Obtener Suelo Temperatura datos
 **************************************************/
void obtenerSueloTempData(void)
{
  DS18B20.requestTemperatures();
  sueloTemp = DS18B20.getTempCByIndex(0);
  
  int newData = ((sueloTemp + 0.05)*10); //Fijar Temp con 1 decimal
  sueloTemp = (newData / 10.0);
}
