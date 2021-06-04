void voltmeter_init()
{
  menyDraw("VOLTMETER", true);
  valueDraw(0, 2, TFT_WHITE);
  simbolDraw("V", TFT_BLUE);

  voltLevelMenyDraw();
  voltLevelDraw(1, "N");
  voltLevelDraw(2, "N");
  voltLevelDraw(3, "N");
}

void voltmeter_draw(float value)
{
  if (value >= CMOS_18_1) voltLevelDraw(1, "1");
  else if (value <= CMOS_18_0) voltLevelDraw(1, "0");
  else voltLevelDraw(1, "N");

  if (value >= TTL_1) voltLevelDraw(2, "1");
  else if (value <= TTL_0) voltLevelDraw(2, "0");
  else voltLevelDraw(2, "N");

  if (value >= CMOS_5V_1) voltLevelDraw(3, "1");
  else if (value <= CMOS_5V_0) voltLevelDraw(3, "0");
  else voltLevelDraw(3, "N");
  
  if (value < voltage_alarm) valueDraw(value, 2, TFT_WHITE);
  else valueDraw(value, 2, TFT_RED);

  if (connectBL)
  {
    String data_volt;
    data_volt = PREF_VLT;
    data_volt.concat(String(value, 2));
    data_volt.concat(PREF_FIN);
    Bluetooth.print(data_volt);
    Bluetooth.write('>');
  }
}
