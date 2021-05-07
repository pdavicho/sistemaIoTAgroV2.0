/*************************************************
 * Inicio OLED
 *************************************************/
 void oledInicio(void)
 {
  Wire.begin();
  oled.init();
  borrarOledDisplay(); //Función para borrar
  oled.clearDisplay(); //Borrar pantalla

  oled.setTextXY(0,0); oled.putString("IoT-Agricultura");
  oled.setTextXY(1,0); oled.putString(String(SW_VERSION));

  oled.setTextXY(2,0); oled.putString("CTRL_AUTO_TM");
  oled.setTextXY(2,13); oled.putString(String(CTRL_AUTO_TM));
  
  oled.setTextXY(3,0); oled.putString("Sue_SECO");
  oled.setTextXY(3,13); oled.putString(String(SUELO_SECO));

  oled.setTextXY(4,0); oled.putString("Tem_FRIA");
  oled.setTextXY(4,13); oled.putString(String(TEMP_FRIA));

  oled.setTextXY(5,0); oled.putString("BOMBA_ON");
  oled.setTextXY(5,13); oled.putString(String(TIME_BOMBA_ON));

  oled.setTextXY(6,0); oled.putString("LAMP_ON");
  oled.setTextXY(6,13); oled.putString(String(TIME_LAMP_ON));

  oled.setTextXY(7,0); oled.putString("  <SENSOR PUSH> ");
 }
/*************************************************
 * Mostrar datos OLED
 *************************************************/
void mostrarDatos(void)
{
  String bombaStatusStr;
  String lampStatusStr;
  if(bombaStatus == 1) bombaStatusStr = "on ";
  if(bombaStatus == 0) bombaStatusStr = "off ";
  if(lampStatus == 1) lampStatusStr = "on ";
  if(lampStatus == 0) lampStatusStr = "off ";

  oled.setTextXY(2, 0); oled.putString("                ");

  oled.setTextXY(3,0); oled.putString("AirTmp [C] ");
  oled.setTextXY(3,11); oled.putString("     ");
  oled.setTextXY(3,11); oled.putString(String(aireTemp));

  oled.setTextXY(4,0); oled.putString("AirHum [%] ");
  oled.setTextXY(4,11); oled.putString("     ");
  oled.setTextXY(4,11); oled.putString(String(aireHum));

  oled.setTextXY(5,0); oled.putString("SueloTmp[C] ");
  oled.setTextXY(5,11); oled.putString("     ");
  oled.setTextXY(5,11); oled.putString(String(sueloTemp));

  oled.setTextXY(6,0); oled.putString("SueloHum[%] ");
  oled.setTextXY(6,11); oled.putString("     ");
  oled.setTextXY(6,11); oled.putString(String(sueloMoister));

  oled.setTextXY(7,0); oled.putString("BMB ");
  oled.setTextXY(7,4); oled.putString(bombaStatusStr);

  oled.setTextXY(7,7); oled.putString("  LMP ");
  oled.setTextXY(7,13); oled.putString(lampStatusStr); 
}
/***************************************************
 * Clear OLED Display
 **************************************************/
void borrarOledDisplay()
{
  oled.setFont(font8x8);
  oled.setTextXY(0,0); oled.putString("                ");
  oled.setTextXY(1,0); oled.putString("                ");
  oled.setTextXY(2,0); oled.putString("                ");
  oled.setTextXY(3,0); oled.putString("                ");
  oled.setTextXY(4,0); oled.putString("                ");
  oled.setTextXY(5,0); oled.putString("                ");
  oled.setTextXY(6,0); oled.putString("                ");
  oled.setTextXY(7,0); oled.putString("                ");
  //oled.setTextXY(0,0); oled.putString("                ");              
}
