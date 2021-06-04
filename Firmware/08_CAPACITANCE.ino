void capacitance_init()
{
  menyDraw("CAPACITANCE", true);
  valueDraw(10, 0, TFT_WHITE);
  simbolDraw("UF", TFT_GRAY_1);

  // КОНДЕНСАТОР
  capLevelDraw(102);
}
