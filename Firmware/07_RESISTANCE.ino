void resistance_init()
{
  menyDraw("RESISTANCE", true);
  valueDraw(0, 0, TFT_WHITE);
  simbolDraw("ОМ", TFT_GRAY_1);
  
  tft.setTextColor(TFT_GRAY_1, HEADER);
  tft.drawString("КОМ", 195, 114);

  // SMD РЕЗИСТОР
  tft.fillRect(25, 105, 39, 20, TFT_GRAY_3);
  tft.fillRect(30, 106, 29, 18, TFT_BLACK);
  tft.setTextColor(TFT_GRAY_1, TFT_BLACK);
  tft.drawNumber(num_01, 33, 110);
  tft.drawNumber(num_02, 41, 110);
  tft.drawNumber(num_03 + 1, 49, 110);

  // ЦВЕТОВАЯ МАРКИРОВКА
  tft.fillRoundRect(80, 105, 55, 20, 4, RES_BACK);

  tft.fillRect(90, 105, 5, 20, RES_GRAY);
  tft.fillRect(100, 105, 5, 20, RES_GRAY);
  tft.fillRect(110, 105, 5, 20, RES_GRAY);
  //tft.fillRect(120, 105, 5, 20, RES_GRAY);

  //rectGradient(120, 105, 5, 20, RES_GOLD_T, RES_GOLD_B);
  rectGradient(120, 105, 5, 20, RES_SILVER_T, RES_SILVER_B);

  // КИЛЛООМЫ
  tft.setTextColor(TFT_WHITE, HEADER);
  tft.loadFont(Font_24);
  tft.setTextColor(TFT_GRAY_1, HEADER);
  tft.setTextDatum(TR_DATUM);
  tft.drawString("0.0", 190, 107);
}

void resistance_draw(float value, int multipiller)
{
  float value_ = value;
  for (uint8_t i = 0; i < multipiller; i++) value_ = value_ * 10;

  if (value_ < 10000) valueDraw(value_, 0, TFT_WHITE);
  else valueDraw(value_ / 1000, 0, TFT_WHITE);

  draw_res_color(value, multipiller);

  // ЗНАЧЕНИЕ
  tft.setTextDatum(TR_DATUM);
  tft.setTextColor(TFT_WHITE, HEADER);
  tft.loadFont(Font_24);
  tft.setTextColor(TFT_GRAY_1, HEADER);
  tft.fillRect(140, 107, 30, 18, HEADER);
  if (value_ < 10000) tft.drawString(String(value_ / 1000, 1), 190, 107);
  else tft.drawString(String(value_ / 1000000, 1), 190, 107);
  tft.setTextDatum(TL_DATUM);

  tft.loadFont(Font_14);
  tft.setTextDatum(TL_DATUM);
  if (value_ < 10000)
  {
    simbolDraw("ОМ", TFT_GRAY_1);

    tft.setTextColor(TFT_GRAY_1, HEADER);
    tft.fillRect(195, 114, 40, 12, HEADER);
    tft.drawString("КОМ", 195, 114);
  }
  else
  {
    simbolDraw("КОМ", TFT_GRAY_1);

    tft.setTextColor(TFT_GRAY_1, HEADER);
    tft.fillRect(195, 114, 40, 12, HEADER);
    tft.drawString("МОМ", 195, 114);
  }
}

void draw_res_color(float value, uint8_t multipiller)
{
  num_01 = (String(value).substring(0, 1)).toInt();
  num_02 = (String(value).substring(1, 2)).toInt();
  num_03 = multipiller;

  tft.setTextDatum(TL_DATUM);
  tft.loadFont(Font_14);
  tft.fillRect(30, 106, 29, 18, TFT_BLACK);
  tft.setTextColor(TFT_GRAY_1, TFT_BLACK);
  tft.drawNumber(num_01, 33, 110);
  if (multipiller == 0 && value < 10) tft.drawString("R", 41, 110);
  else tft.drawNumber(num_02, 41, 110);
  tft.drawNumber(num_03, 49, 110);

  switch (num_01)
  {
    case 0:
      tft.fillRect(90, 105, 5, 20, RES_BLACK);
      break;
    case 1:
      tft.fillRect(90, 105, 5, 20, RES_BROWN);
      break;
    case 2:
      tft.fillRect(90, 105, 5, 20, RES_RED);
      break;
    case 3:
      tft.fillRect(90, 105, 5, 20, RES_ORANGE);
      break;
    case 4:
      tft.fillRect(90, 105, 5, 20, RES_YELOW);
      break;
    case 5:
      tft.fillRect(90, 105, 5, 20, RES_GREEN);
      break;
    case 6:
      tft.fillRect(90, 105, 5, 20, RES_BLUE);
      break;
    case 7:
      tft.fillRect(90, 105, 5, 20, RES_VIOLET);
      break;
    case 8:
      tft.fillRect(90, 105, 5, 20, RES_GRAY);
      break;
    case 9:
      tft.fillRect(90, 105, 5, 20, RES_WHITE);
      break;
  }

  switch (num_02)
  {
    case 0:
      tft.fillRect(100, 105, 5, 20, RES_BLACK);
      break;
    case 1:
      tft.fillRect(100, 105, 5, 20, RES_BROWN);
      break;
    case 2:
      tft.fillRect(100, 105, 5, 20, RES_RED);
      break;
    case 3:
      tft.fillRect(100, 105, 5, 20, RES_ORANGE);
      break;
    case 4:
      tft.fillRect(100, 105, 5, 20, RES_YELOW);
      break;
    case 5:
      tft.fillRect(100, 105, 5, 20, RES_GREEN);
      break;
    case 6:
      tft.fillRect(100, 105, 5, 20, RES_BLUE);
      break;
    case 7:
      tft.fillRect(100, 105, 5, 20, RES_VIOLET);
      break;
    case 8:
      tft.fillRect(100, 105, 5, 20, RES_GRAY);
      break;
    case 9:
      tft.fillRect(100, 105, 5, 20, RES_WHITE);
      break;
  }

  switch (multipiller)
  {
    case 0:
      tft.fillRect(110, 105, 5, 20, RES_BLACK);
      break;
    case 1:
      tft.fillRect(110, 105, 5, 20, RES_BROWN);
      break;
    case 2:
      tft.fillRect(110, 105, 5, 20, RES_RED);
      break;
    case 3:
      tft.fillRect(110, 105, 5, 20, RES_ORANGE);
      break;
    case 4:
      tft.fillRect(110, 105, 5, 20, RES_YELOW);
      break;
    case 5:
      tft.fillRect(110, 105, 5, 20, RES_GREEN);
      break;
    case 6:
      tft.fillRect(110, 105, 5, 20, RES_BLUE);
      break;
    case 7:
      tft.fillRect(110, 105, 5, 20, RES_VIOLET);
      break;
  }
}

void rectGradient(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint16_t TC, uint16_t BC)
{
  for (uint16_t i = 0; i < h; ++i) tft.drawFastHLine(x, y + i, w, (tft.alphaBlend((map(i, 0, h, 0, 255)), BC, TC)));
}
