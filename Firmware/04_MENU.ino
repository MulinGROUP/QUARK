void mode_handler()
{
  switch (mode)
  {
    case 0:
      voltage_last = voltage_prew;
      voltage_prew = INA_219.busVoltage();// - 0,87;
      if (voltage_last != voltage_prew) voltmeter_draw(voltage_prew);
      //delay(50);
      break;
    case 1:
      y = 1500 * sin(angle);
      angle = angle + increment;
      y = map(y, -1500, 1500, 0, 3000);
      y = y;

      amper_last = amper_prew;
      amper_prew = INA_219.shuntCurrent();
      //amper_prew = y;
      amper_prew = amper_prew / 1000;

      if (amper_count)
      {
        amper_count = false;
        amper_pos_grid++;
        amper_pos_time_1++;
        amper_pos_time_2++;
        amper_pos_time_3++;
        if (amper_pos_grid >= 10) amper_pos_grid = 0;
        if (amper_pos_time_1 >= 300)
        {
          amper_time_1 += 3;
          amper_pos_time_1 = 0;
        }
        if (amper_pos_time_2 >= 300)
        {
          if (amper_time_2 == 0) amper_time_2 = -1;
          amper_time_2 += 3;
          amper_pos_time_2 = 0;
        }
        if (amper_pos_time_3 >= 300)
        {
          if (amper_time_3 == 0) amper_time_3 = -2;
          amper_time_3 += 3;
          amper_pos_time_3 = 0;
        }
        ampermeter_graph_draw(amper_prew);
      }
      if (amper_last != amper_prew) ampermeter_draw(amper_prew);
      delay(50);
      break;
    case 2:
      res_last = res_prew;
      res_prew = adc1_get_raw(ADC_CHANNEL);
      if (res_last != res_prew) resistance_draw(res_prew, mult);
      break;
    case 3:

      break;
    case 4:

      break;
    case 5:
      ADC_Sampling(osc_buffer);
      if (freq == 0)find_triger();
      triger();
      draw_graph();
      break;
    case 6:
      if (baud_true) uartHandler();
      break;
    case 7:

      break;
    case 8:

      break;
  }
}

void menu_change()
{
  if (connectBL)
  {
    String mess = "M";
    mess.concat(mode);
    Bluetooth.print(mess);
    Bluetooth.write('>');
  }
  mode_last = mode;
  //counter_seconds = 0;
  bat_counter = 0;
  check_bat = true;

  meas_voltage = false;
  meas_amper = false;
  meas_resistance = false;
  meas_capacitance = false;
  meas_inductance = false;
  meas_oscillograph = false;
  read_UART = false;
  plotter = false;
  settings = false;

  tft.fillRect(0, 20, 240, 115, TFT_BLACK);

  switch (mode)
  {
    case 0:
      Serial.println("VOLTAGE");
      Wire.beginTransmission(ADDRES_AD5254_RC);
      Wire.write(0x00);
      Wire.write(byte(0));
      Wire.endTransmission();
      RC_OFF;
      IND_OFF;
      voltage_last = 0;
      voltage_prew = 0;

      meas_voltage = true;
      voltmeter_init();
      break;
    case 1:
      Serial.println("AMPER");
      IND_OFF;
      amper_last = 0;
      amper_prew = 0;

      meas_amper = true;
      ampermeter_init();
      break;
    case 2:
      Serial.println("RESISTANCE");
      meas_resistance = true;
      resistance_init();
      break;
    case 3:
      Serial.println("CAPACITANCE");
      meas_capacitance = true;
      capacitance_init();
      break;
    case 4:
      Serial.println("INDUCTANCE");
      meas_inductance = true;
      inductance_init();
      break;
    case 5:
      Serial.println("OSCILOGRAPH");
      meas_oscillograph = true;

      triger_01 = 0;
      triger_02 = 0;
      triger_level;
      triger_level_min = 0;
      triger_level_max = 0;

      duty = 0;
      duty_last = 0;
      period = 0;
      freq = 0;

      oscillograph_init();
      break;
    case 6:
      Serial.println("READ UART");
      read_UART = true;
      UART_init();
      break;
    case 7:
      Serial.println("PLOTTER");
      plotter = true;
      plotter_init();
      break;
    case 8:
      Serial.println("SETTINGS");
      settings = true;
      settings_init();
      break;
  }
  if (!meas_oscillograph && i2s_enable)
  {
    i2s_enable = false;
    i2s_adc_disable(I2S_NUM_0);
    i2s_driver_uninstall(I2S_NUM_0);
    Serial.println("I2S DISABLE");
    adc1_config_width(ADC_WIDTH_12Bit);                      //настройка ширины канала ацп 0-4095
    adc1_config_channel_atten(ADC_CHANNEL, ADC_ATTEN_DB_11); //настройка уровня приёма, тут от 150 до 1750 мВ
  }
  if (mode != 6)
  {
    baud_exit = false;
    baud_true = false;
    uart_event_t event;
  }
  if (meas_amper) AMPERS;
  else MEAS;
}
