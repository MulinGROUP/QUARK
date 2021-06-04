void button_2()
{
  switch (mode)
  {
    case 0:

      break;
    case 1:

      break;
    case 2:

      break;
    case 3:

      break;
    case 4:

      break;
    case 5:
      auto_rate = !auto_rate;
      mode_change = auto_rate;
      redraw_footer();
      break;
    case 6:

      break;
    case 7:

      break;
    case 8:

      break;
  }
}

void button()
{
  restore_ADC_Reg();
  if (analogRead(BUTTON) > btn_01_min && analogRead(BUTTON) < btn_01_max)
  {
    if (!btn_01_en)
    {
      btn_press_arr[btn_press_counter] = 1;
      btn_press_counter++;
      btn_counter = 0;
    }
    btn_en = true;
    btn_01_en = true;
    btn_02_en = false;
    btn_03_en = false;
    btn_04_en = false;
    btn_05_en = false;
  }
  if (analogRead(BUTTON) > btn_02_min && analogRead(BUTTON) < btn_02_max)
  {
    if (!btn_02_en)
    {
      btn_press_arr[btn_press_counter] = 2;
      btn_press_counter++;
      btn_counter = 0;
    }
    btn_en = true;
    btn_01_en = false;
    btn_02_en = true;
    btn_03_en = false;
    btn_04_en = false;
    btn_05_en = false;
  }
  if (analogRead(BUTTON) > btn_03_min && analogRead(BUTTON) < btn_03_max)
  {
    if (!btn_03_en)
    {
      btn_press_arr[btn_press_counter] = 3;
      btn_press_counter++;
      btn_counter = 0;
    }
    btn_en = true;
    btn_01_en = false;
    btn_02_en = false;
    btn_03_en = true;
    btn_04_en = false;
    btn_05_en = false;
  }
  if (analogRead(BUTTON) > btn_04_min && analogRead(BUTTON) < btn_04_max)
  {
    if (!btn_04_en)
    {
      btn_press_arr[btn_press_counter] = 4;
      btn_press_counter++;
      btn_counter = 0;
    }
    btn_en = true;
    btn_01_en = false;
    btn_02_en = false;
    btn_03_en = false;
    btn_04_en = true;
    btn_05_en = false;
  }
  if (analogRead(BUTTON) > btn_05_min && analogRead(BUTTON) < btn_05_max)
  {
    if (!btn_05_en)
    {
      btn_press_arr[btn_press_counter] = 5;
      btn_press_counter++;
      btn_counter = 0;
    }
    btn_en = true;
    btn_01_en = false;
    btn_02_en = false;
    btn_03_en = false;
    btn_04_en = false;
    btn_05_en = true;
  }

  if (btn_counter == 10 && btn_05_en)
  {
    btn_05_en = false;
    btn_counter = 0;
    light_pcb = !light_pcb;
    if (light_pcb)
    {
      Serial.println("PCB LIGHT ON");
      LIGHT_ON;
    }
    else
    {
      Serial.println("PCB LIGHT OFF");
      LIGHT_OFF;
    }
  }

  if (analogRead(BUTTON) == 0 && btn_en)
  {
    btn_en = false;
    if (btn_counter >= btn_press_delay)
    {
      btn_up = false;
      btn_dwn = false;
      btn_01_en = false;
      btn_02_en = false;
      btn_03_en = false;
      btn_04_en = false;
      btn_05_en = false;
    }

    if (btn_press_arr[0] < btn_press_arr[1] &&
        btn_press_arr[1] < btn_press_arr[2] &&
        btn_press_arr[2] < btn_press_arr[3])
    {
      btn_up = true;
      btn_dwn = false;
      btn_01_en = false;
      btn_02_en = false;
      btn_03_en = false;
      btn_04_en = false;
      btn_05_en = false;
    }
    if (btn_press_arr[0] > btn_press_arr[1] &&
        btn_press_arr[1] > btn_press_arr[2] &&
        btn_press_arr[2] > btn_press_arr[3])
    {
      btn_up = false;
      btn_dwn = true;
      btn_01_en = false;
      btn_02_en = false;
      btn_03_en = false;
      btn_04_en = false;
      btn_05_en = false;
    }
    btn_counter = 0;
    btn_press_counter = 0;
    for (uint8_t i = 0; i < 6; i++) btn_press_arr[i] = 0;
    if (btn_counter < btn_press_delay) button_funct();
  }
  if (btn_counter >= 100)btn_counter = 0;
}

void button_funct()
{
  if (btn_up)
  {
    Serial.println("BTN UP");
    if (mode == 6 && baud_true)
    {
      Serial.println("STOP UART");
      baud_exit = false;
      baud_true = false;
      uart_flush(PORT_NUM);
      uart_driver_delete(PORT_NUM);
    }
  }
  if (btn_dwn)
  {
    Serial.println("BTN DWN");
    if (mode == 6 && baud_true)
    {
      Serial.println("STOP UART");
      baud_exit = false;
      baud_true = false;
      uart_flush(PORT_NUM);
      uart_driver_delete(PORT_NUM);
    }
  }
  if (btn_01_en)
  {
    Serial.println("BTN 01");
  }
  if (btn_02_en)
  {
    Serial.println("BTN 02");
  }
  if (btn_03_en)
  {
    Serial.println("BTN 03");
  }
  if (btn_04_en)
  {
    Serial.println("BTN 05");
  }
  if (btn_05_en)
  {
    Serial.println("BTN 05");
  }
}
