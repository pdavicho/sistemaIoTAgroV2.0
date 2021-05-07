/***************************************************
* Esperar push Boton y definir tiempo en seg
****************************************************/
void esperarBotonPush (int esperarTime)
{
  long iniciarTime = millis();
  while (debounce(SENSORES_LEER_BOTON)) 
  { 
    if ((millis()-iniciarTime) > (esperarTime*1000)) break;
  }
}
/***************************************************
* Iniciar Timers
****************************************************/
void empezarTimer(void)
{
  timer.setInterval(LEER_BOTON_TM*1000, leerLocalCmd);
  timer.setInterval(LEER_SUELO_TEMP_TM*1000, obtenerSueloTempData);
  timer.setInterval(LEER_AIRE_DATOS_TM*1000, obtenerDHTdata);
  timer.setInterval(LEER_SUELO_HUM_TM*1000, obtenerSueloMoisterData);
  timer.setInterval(ENVIAR_DATOS_TM*1000, enviarDatos);
  timer.setInterval(CTRL_AUTO_TM*1000, autoControlAgro);
  //timer.setInterval(DISPLAY_DATA_TM*1000, displayData);
}
/***************************************************
* Key deboug
****************************************************/
boolean debounce(int pin)
{
  boolean estado;
  boolean estadoPrevio;
  const int debounceDelay = 30;

  estadoPrevio = digitalRead(pin);
  for(int contador=0; contador < debounceDelay; contador++)
  {
    delay(1);
    estado = digitalRead(pin);
    if(estado != estadoPrevio)
    {
      contador = 0;
      estadoPrevio = estado;
    }
  }
  return estado;  
}
