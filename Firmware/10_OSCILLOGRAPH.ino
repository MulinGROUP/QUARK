void oscillograph_init()
{
  tft.fillRect(30, 0, 178, 20, HEADER);
  tft.fillRect(30, 115, 210, 20, HEADER);
  tft.fillRect(0, 0, 30, 135, OSC_LEFT);
  if (connectBL) drawBmp("/BL_ico.bmp", 192, 2);
  tft.setTextColor(TEXT_01, HEADER);
  tft.loadFont(Font_14);
  tft.setTextDatum(TL_DATUM);
  tft.drawString("F", 40, 5);
  tft.drawString("P", 130, 5);
  tft.drawString("RANGE", 40, 120);
  tft.drawString("SCALE", 150, 120);
  if (auto_scale)
  {
    tft.setTextColor(TFT_RED, HEADER);
    tft.drawString("А", 225, 120);
  }
  else
  {
    tft.setTextColor(TFT_GREEN, HEADER);
    tft.drawString("Р", 225, 120);
  }
  tft.setTextColor(TEXT_02, HEADER);
  tft.drawString("0", 55, 5);
  tft.drawString("0", 145, 5);
  tft.drawString(String(mass_rate[num_rate]), 90, 120);

  configure_i2s(mass_rate[num_rate]);
}

void redraw_footer()
{
  tft.loadFont(Font_14);
  tft.fillRect(30, 115, 210, 20, HEADER);
  if (auto_rate) tft.setTextColor(TEXT_01, HEADER);
  else tft.setTextColor(TFT_GREEN, HEADER);
  tft.drawString("RANGE", 40, 120);
  tft.setTextColor(TEXT_01, HEADER);
  tft.drawString("SCALE", 150, 120);
  if (auto_scale)
  {
    tft.setTextColor(TFT_RED, HEADER);
    tft.drawString("А", 225, 120);
  }
  else
  {
    tft.setTextColor(TFT_GREEN, HEADER);
    tft.drawString("Р", 225, 120);
  }
  tft.setTextColor(TEXT_02, HEADER);
  tft.drawString(String(mass_rate[num_rate]), 90, 120);
  drawLevelOscill();
}

void find_triger()
{
  for (uint16_t i = 1; i < NUM_SAMPLES; i++)
  {
    if (osc_buffer[i] < osc_buffer[i - 1])triger_level_min = osc_buffer[i];
    if (osc_buffer[i] > osc_buffer[i - 1])triger_level_max = osc_buffer[i];
  }
  //triger_level = (triger_level_max - triger_level_min)/2 + 12288;
  triger_level = triger_level_min;
}

void triger()
{
  uint16_t duty_temp = 0;
  bool triger_minimum_01 = false;
  bool triger_maximum_01 = false;
  bool triger_minimum_02 = false;
  bool triger_maximum_02 = false;

  triger_level_min = 16384;
  triger_level_max = 12288;

  if (triger_level == 0) find_triger();

  for (uint16_t i = 1; i < NUM_SAMPLES; i++)
  {
    if (!triger_minimum_01)
    {
      if (osc_buffer[i] < triger_level)
      {
        triger_maximum_01 = true;
      }
    }
    if (!triger_minimum_01 && triger_maximum_01)
    {
      if (osc_buffer[i] > triger_level)
      {
        triger_minimum_01 = true;
        triger_01 = i;
      }
    }

    if (triger_minimum_01)
    {
      if (!triger_minimum_02)
      {
        if (osc_buffer[i] < triger_level)
        {
          triger_maximum_02 = true;
        }
      }
      if (!triger_minimum_02 && triger_maximum_02)
      {
        if (osc_buffer[i] > triger_level)
        {
          triger_minimum_02 = true;
          triger_02 = i;
          duty_temp = triger_02 - triger_01;
        }
      }
    }
    if (osc_buffer[i] < triger_level_min) triger_level_min = osc_buffer[i];
    if (osc_buffer[i] > triger_level_max) triger_level_max = osc_buffer[i];
  }
  if (check_freq_cur != check_freq_num)
  {
    if (duty_temp != 0) check_freq_mass[check_freq_cur] = duty_temp;
    check_freq_cur ++;
  }
  else
  {
    check_freq_cur = 0;
    if (check_freq_mass[0] == check_freq_mass[1] && check_freq_mass[0] == check_freq_mass[2])
    {
      duty = check_freq_mass[0];
      if (duty < duty_min && num_rate != 5 && auto_rate) rate_increment();
      if (duty > duty_max && num_rate != 0 && auto_rate) rate_decrement();
    }
  }
}

void draw_graph()
{
  String mess;
  uint16_t y_trig;
  uint16_t x = 30;
  float v_max = triger_level_max;
  float v_min = triger_level_min;

  if (check_volt_cur != check_volt_num)
  {
    check_v_max_mass[check_volt_cur] = v_max;
    check_v_min_mass[check_volt_cur] = v_min;
    check_volt_cur ++;
  }
  else
  {
    check_volt_cur = 0;
    if (check_v_max_mass[0] == check_v_max_mass[1]) volt_level_max = check_v_max_mass[0];
    if (check_v_min_mass[0] == check_v_min_mass[1]) volt_level_min = check_v_min_mass[0];
    if (volt_level_min_last != volt_level_min || volt_level_max_last != volt_level_max) drawLevelOscill();
    volt_level_min_last = volt_level_min;
    volt_level_max_last = volt_level_max;
  }

  tft.fillRect(30, 20, 210, 95, TFT_BLACK);
  if (duty_last != duty)
  {
    freq = (mass_rate[num_rate] / duty) * 2;
    period = 1000000 / freq;
    float period_ = period;
    tft.fillRect(30, 0, 178, 20, HEADER);
    tft.setTextColor(TEXT_01, HEADER);
    tft.loadFont(Font_14);
    tft.drawString("F", 40, 5);
    tft.drawString("P", 130, 5);
    tft.setTextColor(TEXT_02, HEADER);
    tft.drawString(String(freq) + " Hz", 55, 5);
    if (period < 1000) tft.drawString(String(period) + " uS", 145, 5);
    if (period > 1000) tft.drawString(String(period_ / 1000, 1) + " mS", 145, 5);
    if (connectBL) drawBmp("/BL_ico.bmp", 192, 2);
  }
  duty_last = duty;

  if (auto_scale) y_trig = map(triger_level, triger_level_min, triger_level_max, 0, 94);
  else y_trig = map(triger_level, 12288, 16384, 0, 94);
  if (y_trig > 94) y_trig = 0;

  mess = PREF_ARR;
  for (uint16_t i = triger_01; i < 210 + triger_01; i++)
  {
    x++;
    uint8_t y_curr;
    uint8_t y_next;
    uint8_t y_bl;
    if (auto_scale)
    {
      y_curr = map(osc_buffer[i], triger_level_min, triger_level_max, 0, 94);
      y_next = map(osc_buffer[i + 1], triger_level_min, triger_level_max, 0, 94);
      y_bl = map(osc_buffer[i + 1], triger_level_min, triger_level_max, 0, 188);
    }
    else
    {
      y_curr = map(osc_buffer[i], 12288, 16384, 0, 94);
      y_next = map(osc_buffer[i + 1], 12288, 16384, 0, 94);
      y_bl = map(osc_buffer[i], 12288, 16384, 0, 188);
    }
    if (y_curr > 94) y_curr = 0;
    if (y_next > 94) y_next = y_curr;
    tft.drawLine(x, 114 - y_curr, x + 1, 114 - y_next, TFT_VIOL_1);

    
    mess.concat(y_bl);
    mess.concat("|");
  }
  if (BL_type && connectBL) 
  {
    Bluetooth.print(mess);
    Bluetooth.write('>');
  }
  if (!BL_type && connectBL)
  {
    String data_osc;
    data_osc = PREF_FRQ;
    data_osc.concat(String(freq));
    data_osc.concat(PREF_SCL);
    if (auto_scale)  data_osc.concat("A");
    if (!auto_scale) data_osc.concat("M");
    data_osc.concat(PREF_OMX);
    data_osc.concat(String(curr_max, 1));
    data_osc.concat(PREF_OMN);
    data_osc.concat(String(curr_min, 1));
    data_osc.concat(PREF_FIN);
    Bluetooth.print(data_osc);
    Bluetooth.write('>');
  }
  triger_01 = 0;
  BL_type = !BL_type;
}

void drawLevelOscill()
{
  if (!auto_scale)
  {
    pos_y_max = 109 - (map(volt_level_max, 12288, 16384, 0, 95));
    pos_y_min = 109 - (map(volt_level_min, 12288, 16384, 0, 95));
  }
  else
  {
    pos_y_max = 15;
    pos_y_min = 109;
  }

  curr_max = (volt_level_max - shift) / 4095.0 * 3.3;
  curr_min = (volt_level_min - shift) / 4095.0 * 3.3;

  //curr_max = volt_level_max / 4095.0 * 3.3;
  //curr_min = volt_level_min / 4095.0 * 3.3;

  tft.fillRect(0, 0, 30, 135, OSC_LEFT);
  tft.loadFont(Font_10);
  tft.setTextColor(TFT_WHITE, OSC_LEVEL);

  tft.fillRect(0, pos_y_min, 24, 11, OSC_LEVEL);
  tft.fillRect(24, pos_y_min + 1, 1, 9, OSC_LEVEL);
  tft.fillRect(25, pos_y_min + 2, 1, 7, OSC_LEVEL);
  tft.fillRect(26, pos_y_min + 3, 1, 5, OSC_LEVEL);
  tft.fillRect(27, pos_y_min + 4, 1, 3, OSC_LEVEL);
  tft.drawPixel(28, pos_y_min + 5, OSC_LEVEL);
  tft.drawString(String(curr_min, 1), 4, pos_y_min + 2);

  tft.fillRect(0, pos_y_max, 24, 11, OSC_LEVEL);
  tft.fillRect(24, pos_y_max + 1, 1, 9, OSC_LEVEL);
  tft.fillRect(25, pos_y_max + 2, 1, 7, OSC_LEVEL);
  tft.fillRect(26, pos_y_max + 3, 1, 5, OSC_LEVEL);
  tft.fillRect(27, pos_y_max + 4, 1, 3, OSC_LEVEL);
  tft.drawPixel(28, pos_y_max + 5, OSC_LEVEL);
  tft.drawString(String(curr_max, 1), 4, pos_y_max + 2);
}

void rate_increment()
{
  i2s_adc_disable(I2S_NUM_0);
  i2s_driver_uninstall(I2S_NUM_0);
  if (num_rate < 5) num_rate++;
  configure_i2s(mass_rate[num_rate]);
  redraw_footer();
}
void rate_decrement()
{
  i2s_adc_disable(I2S_NUM_0);
  i2s_driver_uninstall(I2S_NUM_0);
  if (num_rate > 0) num_rate--;
  configure_i2s(mass_rate[num_rate]);
  redraw_footer();
}

void configure_i2s(uint32_t rate)
{
  //keep in mind:
  //dma_buf_len * dma_buf_count * bits_per_sample/8 > 4096
  i2s_config_t i2s_config =
  {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX | I2S_MODE_ADC_BUILT_IN),  // I2S receive mode with ADC
    .sample_rate = rate,                                                          // sample rate
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,                                 // 16 bit I2S
    .channel_format = I2S_CHANNEL_FMT_ALL_LEFT,                                   // only the left channel
    .communication_format = (i2s_comm_format_t)(I2S_COMM_FORMAT_I2S | I2S_COMM_FORMAT_I2S_MSB),   // I2S format
    .intr_alloc_flags = 1,                                                        // none
    .dma_buf_count = 2,                                                           // number of DMA buffers
    .dma_buf_len = NUM_SAMPLES,                                                   // number of samples
    .use_apll = 0,                                                                // no Audio PLL
  };
  adc1_config_channel_atten(ADC_CHANNEL, ADC_ATTEN_11db);  // ADC channel 0 with 11db (divide by input 3.6)
  adc1_config_width(ADC_WIDTH_12Bit);                      // 12 bit ADC
  i2s_driver_install(I2S_NUM_0, &i2s_config, 0, NULL);     // install I2S 0 driver, using event queue

  i2s_set_adc_mode(ADC_UNIT_1, ADC_CHANNEL);               // ADC should use ADC_CHANNEL
  // The raw ADC data is written in DMA in inverted form. This add aninversion:
  SET_PERI_REG_MASK(SYSCON_SARADC_CTRL2_REG, SYSCON_SARADC_SAR1_INV);
  i2s_adc_enable(I2S_NUM_0);                               // enable I2S ADC
  i2s_enable = true;
  find_triger();
}

void ADC_Sampling(uint16_t *osc_buffer)
{
  for (int i = 0; i < BUFF_SIZE / NUM_SAMPLES; i++)
  {
    i2s_read_bytes(I2S_NUM_0, (char*)&osc_buffer[i * NUM_SAMPLES],  NUM_SAMPLES * sizeof(uint16_t), portMAX_DELAY);
  }
}

void characterize_adc()
{
  esp_adc_cal_value_t val_type = esp_adc_cal_characterize(
                                   (adc_unit_t)ADC_UNIT_1,
                                   (adc_atten_t)ADC_CHANNEL,
                                   (adc_bits_width_t)ADC_WIDTH_BIT_12,
                                   1100,
                                   &adc_chars);
}
