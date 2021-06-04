void battery()
{
  if (batt_level < batt_level_0 && bat_redraw && CHRG_OFF)
  {
    batt_level = BATT_LEVEL;
    bat_redraw = false;

    if (bat_red)
    {
      tft.drawRect(209, 4, 23, 12, TFT_RED);
      tft.fillRect(232, 7, 3, 7, TFT_RED);
    }
    else
    {
      tft.drawRect(209, 4, 23, 12, TEXT_01);
      tft.fillRect(232, 7, 3, 7, TEXT_01);
    }
    bat_red = !bat_red;
  }

  if ((bat_counter >= bat_counter_check || check_bat) && CHRG_OFF)
  {
    check_bat = false;
    bat_counter = 0;
    batt_level = BATT_LEVEL;

    //tft.loadFont(Font_14);
    //tft.setTextDatum(TL_DATUM);
    //tft.setTextColor(TEXT_01, HEADER);
    //tft.drawNumber(batt_level, 130, 5);

    if (batt_level > batt_level_0)
    {
      tft.drawRect(209, 4, 23, 12, TEXT_01);
      tft.fillRect(232, 7, 3, 7, TEXT_01);
    }

    if (batt_level > batt_level_1) tft.fillRect(211, 6, 3, 8, TEXT_01);
    else tft.fillRect(211, 6, 3, 8, HEADER);
    if (batt_level > batt_level_2) tft.fillRect(215, 6, 3, 8, TEXT_01);
    else tft.fillRect(215, 6, 3, 8, HEADER);
    if (batt_level > batt_level_3)tft.fillRect(219, 6, 3, 8, TEXT_01);
    else tft.fillRect(219, 6, 3, 8, HEADER);
    if (batt_level > batt_level_4)tft.fillRect(223, 6, 3, 8, TEXT_01);
    else tft.fillRect(223, 6, 3, 8, HEADER);
    if (batt_level > batt_level_5)tft.fillRect(227, 6, 3, 8, TEXT_01);
    else tft.fillRect(227, 6, 3, 8, HEADER);
  }

  if (CHRG_ON && bat_redraw)
  {
    batt_level = BATT_LEVEL;
    bat_redraw = false;

    if (bat_redraw_chrg)
    {
      bat_redraw_chrg = false;
      counter_seconds = 0;
    }

    if (counter_seconds > 10 && counter_seconds < 20)
    {
      tft.drawRect(209, 4, 23, 12, TFT_GREEN);
      tft.fillRect(232, 7, 3, 7, TFT_GREEN);
      tft.fillRect(211, 5, 20, 10, HEADER);
    }
    if (counter_seconds > 20 && counter_seconds < 30)tft.fillRect(211, 6, 3, 8, TFT_GREEN);
    if (counter_seconds > 30 && counter_seconds < 40)tft.fillRect(215, 6, 3, 8, TFT_GREEN);
    if (counter_seconds > 40 && counter_seconds < 50)tft.fillRect(219, 6, 3, 8, TFT_GREEN);
    if (counter_seconds > 50 && counter_seconds < 60)tft.fillRect(223, 6, 3, 8, TFT_GREEN);
    if (counter_seconds > 60)
    {
      tft.fillRect(227, 6, 3, 8, TFT_GREEN);
      counter_seconds = 0;
    }
  }
  if (CHRG_OFF && !bat_redraw_chrg)
  {
    bat_redraw_chrg = true;
    bat_redraw = false;
    batt_level = BATT_LEVEL;
    bat_counter = bat_counter_check;
  }
}
