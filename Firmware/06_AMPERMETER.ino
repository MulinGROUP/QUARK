void ampermeter_init()
{
  menyDraw("AMPERMETER", true);
  valueDraw(0, 2, TFT_WHITE);
  simbolDraw("A", TFT_RED);

  for (uint8_t i = 0; i < graph_width; i++)
  {
    amper_array_1[i] = 0;
    amper_array_2[i] = 0;
  }

  amper_pos_grid = 0;
  amper_pos_time_1 = 40;
  amper_pos_time_2 = 140;
  amper_pos_time_3 = 240;

  amper_time_1 = 0;
  amper_time_2 = 0;
  amper_time_3 = 0;

  amper_count = 0;
}

void ampermeter_draw(float value)
{
  if (value < amper_alarm) valueDraw(value, 3, TFT_WHITE);
  else valueDraw(value, 2, TFT_RED);

  String mess;
  mess = PREF_AAP;
  for (uint8_t i = 36; i < 239; i++)
  {
    mess.concat(amper_array_1[i]);
    mess.concat("|");
  }
  mess.concat(PREF_FIN);
  if (connectBL) 
  {
    Bluetooth.print(mess);
    Bluetooth.write('>');
  }
}

void ampermeter_graph_draw(float value)
{
  if (value > 3) value = 3;
  tft.fillRect(0, 95, 240, 40, HEADER);
  for (uint8_t i = 0; i < 26; i++) tft.drawLine(((i * 10) - amper_pos_grid), 104, ((i * 10) - amper_pos_grid), 134, TFT_GRAY);
  tft.drawLine(0, 104, 239, 104, TFT_GRAY);
  tft.drawLine(0, 114, 239, 114, TFT_GRAY);
  tft.drawLine(0, 124, 239, 124, TFT_GRAY);

  tft.unloadFont();
  tft.setTextSize(1);
  tft.setTextColor(TEXT_01, HEADER);

  if (amper_time_1 == 0) tft.drawString("00", (275 - amper_pos_time_1), 96, 1);
  else  tft.drawNumber(amper_time_1 * 10, (275 - amper_pos_time_1), 96, 1);
  if (amper_time_2 != 0) tft.drawNumber(amper_time_2 * 10, (275 - amper_pos_time_2), 96, 1);
  if (amper_time_3 != 0) tft.drawNumber(amper_time_3 * 10, (275 - amper_pos_time_3), 96, 1);

  for (uint8_t i = 0; i < graph_width; i++)  tft.drawLine(i, 134 - amper_array_1[i] / 100, i, 134 - amper_array_2[i] / 100, TFT_VIOL_1);
  for (uint8_t i = 0; i < graph_width; i++) amper_array_2[i] = amper_array_1[i];
  for (uint8_t i = 1; i < graph_width + 1; i++)
  {
    amper_array_1[i - 1] = amper_array_1[i];
    amper_array_1[graph_width] = value * 1000;
  }
}
