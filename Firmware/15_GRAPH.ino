////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//              БАЗОВАЯ ГРАФИКА              ///////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// МЕНЮ
void menyDraw(String string, bool bottom)
{
  if (meny_draw)
  {
    tft.fillScreen(TFT_BLACK);
    tft.setTextDatum(TC_DATUM);
    tft.loadFont(Font_24);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawString(string, 120, 60);
    delay(delay_mode);
    tft.fillScreen(TFT_BLACK);
  }
  // Рисуем графику меню
  tft.fillRect(0, 0, 208, 20, HEADER);
  if (connectBL) drawBmp("/BL_ico.bmp", 192, 2);
  if (bottom) tft.fillRect(0, 95, 240, 40, HEADER);

  tft.setTextDatum(TL_DATUM);
  tft.loadFont(Font_14);
  tft.setTextColor(TEXT_01, HEADER);
  tft.drawString(string, 10, 5);
}
// ЗНАЧЕНИЕ
void valueDraw(float value, uint8_t dot, uint16_t color)
{
  tft.setTextDatum(TR_DATUM);
  tft.loadFont(Font_64);
  tft.setTextColor(color, TFT_BLACK);
  tft.fillRect(20, 33, 160, 50, TFT_BLACK);
  if (dot > 0) tft.drawFloat(value, dot, 180, 33);
  else tft.drawNumber(value, 180, 33);
}
// СИМВОЛ
void simbolDraw(String simbol, uint16_t color)
{ 
  tft.setTextDatum(TL_DATUM);
  tft.loadFont(Font_14); 
  tft.setTextColor(color, TFT_BLACK);
  tft.drawString(simbol, 190, 70);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                 ВОЛЬТМЕТР                 ///////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void voltLevelMenyDraw()
{
  tft.fillRoundRect(6, 100, 72, 30, 3, TFT_BLUE_1);
  tft.fillRoundRect(84, 100, 72, 30, 3, TFT_BLUE_1);
  tft.fillRoundRect(162, 100, 72, 30, 3, TFT_BLUE_1);
  tft.loadFont(Font_24);
  tft.setTextColor(TEXT_01, TFT_BLUE_1);
  tft.drawString("1.8", 14, 106);
  tft.drawString("TTL", 92, 106);
  tft.drawString("5V", 170, 106);
}

void voltLevelDraw(uint8_t num, String level)
{
  tft.setTextDatum(TC_DATUM);
  tft.loadFont(Font_24);
  if (num == 1)
  {
    tft.fillRect(51, 106, 20, 20, TFT_BLUE_1);
    if (level == "0")tft.setTextColor(TFT_BLUE, TFT_BLUE_1);
    if (level == "1")tft.setTextColor(TFT_GREEN, TFT_BLUE_1);
    if (level == "N")tft.setTextColor(TFT_GRAY, TFT_BLUE_1);
    tft.drawString(level, 60, 106);
  }
  if (num == 2)
  {
    tft.fillRect(129, 106, 20, 20, TFT_BLUE_1);
    if (level == "0")tft.setTextColor(TFT_BLUE, TFT_BLUE_1);
    if (level == "1")tft.setTextColor(TFT_GREEN, TFT_BLUE_1);
    if (level == "N")tft.setTextColor(TFT_GRAY, TFT_BLUE_1);
    tft.drawString(level, 138, 106);
  }
  if (num == 3)
  {
    tft.fillRect(207, 106, 20, 20, TFT_BLUE_1);
    if (level == "0")tft.setTextColor(TFT_BLUE, TFT_BLUE_1);
    if (level == "1")tft.setTextColor(TFT_GREEN, TFT_BLUE_1);
    if (level == "N")tft.setTextColor(TFT_GRAY, TFT_BLUE_1);
    tft.drawString(level, 216, 106);
  }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                  ЕМКОСТЬ                  ///////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void capLevelDraw(uint16_t value)
{  
  tft.fillRoundRect(30, 105, 40, 20, 4, CAP_BACK);
  
  tft.setTextDatum(TC_DATUM);
  tft.loadFont(Font_18);
  tft.setTextColor(TFT_BLACK, CAP_BACK);
  tft.drawNumber(value, 50, 108);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//               ИНДУКТИВНОСТЬ               ///////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void indLevelDraw(uint16_t value)
{  
  tft.fillRoundRect(30, 105, 40, 20, 4, TFT_BLUE_1);
  
  tft.setTextDatum(TC_DATUM);
  tft.loadFont(Font_18);
  tft.setTextColor(TFT_BLACK, TFT_BLUE_1);
  tft.drawNumber(value, 50, 108);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                    UART                   ///////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UART_dataDraw(String mess)
{  
  tft.fillRect(0, 20, 100, 80, TFT_BLACK);
  
  tft.setTextDatum(TC_DATUM);
  tft.loadFont(Font_14);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);
  tft.drawString(mess, 20, 30);
}
void UART_baudDraw(String value, uint16_t color)
{
  tft.fillRect(100, 0, 85, 20, HEADER);

  tft.setTextDatum(TL_DATUM);
  tft.loadFont(Font_14);
  tft.setTextColor(color, HEADER);
  tft.drawString(value, 100, 5);
  tft.setTextColor(TEXT_01, HEADER);
  tft.drawString("BAUD", 55, 5);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                    BMP                    ///////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void drawBmp(const char *filename, int16_t x, int16_t y)
{
  if ((x >= tft.width()) || (y >= tft.height())) return;
  fs::File bmpFS;
  bmpFS = SPIFFS.open(filename, "r");

  if (!bmpFS)
  {
    Serial.print("File not found");
    return;
  }

  uint32_t seekOffset;
  uint16_t w, h, row, col;
  uint8_t  r, g, b;
  uint32_t startTime = millis();

  if (read16(bmpFS) == 0x4D42)
  {
    read32(bmpFS);
    read32(bmpFS);
    seekOffset = read32(bmpFS);
    read32(bmpFS);
    w = read32(bmpFS);
    h = read32(bmpFS);

    if ((read16(bmpFS) == 1) && (read16(bmpFS) == 24) && (read32(bmpFS) == 0))
    {
      y += h - 1;

      bool oldSwapBytes = tft.getSwapBytes();
      tft.setSwapBytes(true);
      bmpFS.seek(seekOffset);

      uint16_t padding = (4 - ((w * 3) & 3)) & 3;
      uint8_t lineBuffer[w * 3 + padding];

      for (row = 0; row < h; row++) {
        
        bmpFS.read(lineBuffer, sizeof(lineBuffer));
        uint8_t*  bptr = lineBuffer;
        uint16_t* tptr = (uint16_t*)lineBuffer;
        // Convert 24 to 16 bit colours
        for (uint16_t col = 0; col < w; col++)
        {
          b = *bptr++;
          g = *bptr++;
          r = *bptr++;
          *tptr++ = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
        }
        tft.pushImage(x, y--, w, 1, (uint16_t*)lineBuffer);
      }
      tft.setSwapBytes(oldSwapBytes);
      Serial.print("Loaded in "); Serial.print(millis() - startTime);
      Serial.println(" ms");
    }
    else Serial.println("BMP format not recognized.");
  }
  bmpFS.close();
}

uint16_t read16(fs::File &f) {
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read(); // MSB
  return result;
}

uint32_t read32(fs::File &f) {
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read(); // MSB
  return result;
}
