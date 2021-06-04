void inductance_init()
{
  menyDraw("INDUCTANCE", true);
  valueDraw(22, 0, TFT_WHITE);
  simbolDraw("UH", TFT_GRAY_1);

  // ИНДУКТИВНОСТЬ
  indLevelDraw(102);
}
