void UART_init()
{
  menyDraw("UART", false);

  tft.setTextDatum(TL_DATUM);
  tft.loadFont(Font_12);
  tft.setTextColor(TEXT_01, TFT_BLACK);
  pinMode(RXD2, INPUT);
  detectionBaud();
}

void UART_draw(uint8_t arr)
{
  if (arr == 10)
  {
    tft.fillRect(0, 20, 240, 114, TFT_BLACK);
    if (uart_arr == 7) uart_arr = 0;
    incoming_array[0] = incomming;
    for (uint8_t i = 0; i < 7; i++) tft.drawString(incoming_array[i], 10, 30 + 15 * i);
    for (uint8_t i = 6; i > 0; i--) incoming_array[i] = incoming_array[i - 1];
    uart_arr++;
    incomming = "";
  }
  else incomming += String((char)arr);
}

void uartHandler()
{
  uart_event_t event;
  size_t buffered_size;
  //if (xQueueReceive(UART_QUEUE, (void * )&event, (portTickType)portMAX_DELAY))
  if (xQueueReceive(UART_QUEUE, (void * )&event, 50))
  {
    if (event.type == UART_DATA)
    {
      uint8_t UART_data[128];
      int UART_data_length = 0;

      ESP_ERROR_CHECK(uart_get_buffered_data_len(PORT_NUM, (size_t*)&UART_data_length));
      UART_data_length = uart_read_bytes(PORT_NUM, UART_data, UART_data_length, 100);

      for (byte i = 0; i < UART_data_length; i++)  if (baud_true) UART_draw(UART_data[i]);
      //Serial.print((char)UART_data[i]);
    }
    if (event.type == UART_FIFO_OVF)
    {
      Serial.println("UART_FIFO_OVF");
      uart_flush(PORT_NUM);
    }
    if (event.type == UART_BUFFER_FULL)
    {
      Serial.println("UART_BUFFER_FULL");
      uart_flush(PORT_NUM);
    }
    if (event.type == UART_BREAK)
    {
      Serial.println("UART_BREAK");
      uart_flush(PORT_NUM);
    }
    if (event.type == UART_PARITY_ERR)
    {
      Serial.println("UART_PARITY_ERR");
      uart_flush(PORT_NUM);
    }
    if (event.type == UART_FRAME_ERR)
    {
      Serial.println("UART_FRAME_ERR");
      uart_driver_delete(PORT_NUM);
      uart_flush(PORT_NUM);
      UART_setup();
    }
    if (event.type == UART_PATTERN_DET)
    {
      Serial.println("UART_PATTERN_DET");
      uart_flush(PORT_NUM);
    }
  }
}

long detectionBaud()
{
  UART_baudDraw("DETECTION", TFT_RED);
  uint32_t width_impulse;                      // Ширина импульса
  uint32_t width_impulse_last = 10000;         // Ширина импульса последняя
  for (uint16_t i = 0; i < baud_count_max; i++)
  {
    while (digitalRead(RXD2) == 1)
    {
      if (btn_up || btn_dwn)
      {
        Serial.println("BREAK");
        baud_exit = true;
        break;
      }
    }
    if (!baud_exit)
    {
      width_impulse = pulseIn(RXD2, LOW);
      if (width_impulse < width_impulse_last)
      {
        if (width_impulse < 12) BAUD_RATE = 115200;
        else if (width_impulse < 20) BAUD_RATE = 57600;
        else if (width_impulse < 29) BAUD_RATE = 38400;
        else if (width_impulse < 40) BAUD_RATE = 28800;
        else if (width_impulse < 60) BAUD_RATE = 19200;
        else if (width_impulse < 80) BAUD_RATE = 14400;
        else if (width_impulse < 150) BAUD_RATE = 9600;
        else if (width_impulse < 300) BAUD_RATE = 4800;
        else if (width_impulse < 600) BAUD_RATE = 2400;
        else if (width_impulse < 1200) BAUD_RATE = 1200;
        else BAUD_RATE = 0;
        width_impulse_last = width_impulse;
      }
      if (i == 50) UART_baudDraw("DETECTION", TEXT_02);
      if (i == 100) UART_baudDraw("DETECTION", TFT_RED);
      if (i == 150) UART_baudDraw("DETECTION", TEXT_02);
      if (i == 200) UART_baudDraw("DETECTION", TFT_RED);
      if (i == 250) UART_baudDraw("DETECTION", TEXT_02);
      if (i == 300) UART_baudDraw("DETECTION", TFT_RED);
      if (i == 350) UART_baudDraw("DETECTION", TEXT_02);
      if (i == 400) UART_baudDraw("COMPLITTED", RES_GREEN);
    }
    else break;
  }
  if (!baud_exit)
  {
    UART_baudDraw(String(BAUD_RATE), TEXT_02);
    tft.setTextDatum(TL_DATUM);
    tft.loadFont(Font_12);
    tft.setTextColor(TEXT_01, TFT_BLACK);
    baud_true = true;
    delay(10);
    UART_setup();
  }
}

void UART_setup()
{
  uart_config_t uart_config = {
    .baud_rate = BAUD_RATE,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    .rx_flow_ctrl_thresh = 122,
  };
  uart_param_config(PORT_NUM, &uart_config);
  uart_set_pin(PORT_NUM, TXD2, RXD2, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
  uart_driver_install(PORT_NUM, BUF_SIZE, BUF_SIZE, 10, &UART_QUEUE, 0);
}
