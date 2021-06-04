#include <driver/i2s.h>
#include <driver/adc.h>
#include <soc/syscon_reg.h>
#include <Wire.h>
#include <TFT_eSPI.h>
#include <SPI.h>
#include <INA219.h>
#include "driver/uart.h"
#include "esp_adc_cal.h"
#include "01_DEFINES.h"
#include "02_VARIABLES.h"
#include "FS.h"
#include "SPIFFS.h"
#include "BluetoothSerial.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"

#include "soc/rtc_io_reg.h"
#include "soc/rtc_cntl_reg.h"
#include "soc/sens_reg.h"

INA219 INA_219;
TFT_eSPI tft = TFT_eSPI(HEIGHT, WIDTH);
BluetoothSerial Bluetooth;

esp_adc_cal_characteristics_t adc_chars;

TaskHandle_t TASK_BTN;
TaskHandle_t TASK_MENY;
TaskHandle_t TASK_BL;
QueueHandle_t UART_QUEUE;

// ТАЙМЕРЫ
hw_timer_t * count_timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

void IRAM_ATTR counter_funct()
{
  portENTER_CRITICAL_ISR(&timerMux);
  if (mode == 1) amper_count = true;
  counter_seconds++;
  btn_counter ++;
  bat_counter ++;
  bat_redraw = true;
  portEXIT_CRITICAL_ISR(&timerMux);
}

void save_ADC_Reg(void)
{
  reg_b = READ_PERI_REG(SENS_SAR_READ_CTRL2_REG);
}

void restore_ADC_Reg(void)
{
  WRITE_PERI_REG(SENS_SAR_READ_CTRL2_REG, reg_b);
  SET_PERI_REG_MASK(SENS_SAR_READ_CTRL2_REG, SENS_SAR2_DATA_INV);
}

void setup()
{
  save_ADC_Reg();
  Bluetooth.register_callback(callback);
  Bluetooth.setPin(pin);
  Bluetooth.begin("QUARK");
  Serial.begin(115200);
  Serial.println();
  Serial.println("START");

  SPIFFS.begin();
  INA_219.begin();
  INA_219.configure(INA219::RANGE_32V,
                    INA219::GAIN_2_80MV,
                    INA219::ADC_16SAMP,
                    INA219::ADC_16SAMP,
                    INA219::CONT_SH_BUS);
  INA_219.calibrate(R_SHUNT,
                    V_SHUNT_MAX,
                    V_BUS_MAX,
                    I_MAX);

  Wire.begin(SDA1, SCL1);

  pinMode(IND_VAL, INPUT);
  pinMode(SPEAK, OUTPUT);
  pinMode(REL_01, OUTPUT);
  pinMode(REL_02, OUTPUT);
  pinMode(POWER, OUTPUT);
  pinMode(PCB_LIGHT, OUTPUT);
  pinMode(BUTTON, INPUT);
  pinMode(CHRG, INPUT);
  pinMode(ADC_CR, INPUT);
  pinMode(ADC_BAT, INPUT);
  pinMode(RC_EN, OUTPUT);
  pinMode(IND_EN, OUTPUT);
  pinMode(L_GEN, OUTPUT);

  pinMode(32, INPUT);
  pinMode(33, INPUT);

  MEAS;
  PWR_ON;
  IND_OFF;
  RC_OFF;

  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextDatum(TL_DATUM);
  tft.fillRect(0, 0, 240, 20, HEADER);

  //printDeviceAddress();
  battery();
  menu_change();

  // ТАЙМЕРЫ
  count_timer = timerBegin(0, 80, true);                     // Таймер анимации, делитель 80
  timerAttachInterrupt(count_timer, &counter_funct, true);   // Присоединяем функцию counter_funct к нашему таймеру.
  timerAlarmWrite(count_timer, count_mult, true);            // Вызов count_timer десять раз в секунду, повтор
  timerAlarmEnable(count_timer);                             // Запсук

  xTaskCreatePinnedToCore(
    btn_handle,
    "btn_handle",
    10000,  /* Stack size in words */
    NULL,  /* Task input parameter */
    0,  /* Priority of the task */
    &TASK_BTN,  /* Task handle. */
    0); /* Core where the task should run */

  xTaskCreatePinnedToCore(
    menu_handle,
    "menu_handle",
    10000,  /* Stack size in words */
    NULL,  /* Task input parameter */
    3,  /* Priority of the task */
    &TASK_MENY,  /* Task handle. */
    1); /* Core where the task should run */
}

void btn_handle( void * pvParameters )
{
  (void) pvParameters;
  for (;;)
  {
    button();
    vTaskDelay(pdMS_TO_TICKS(10));
  }
}

void menu_handle( void * pvParameters )
{
  (void) pvParameters;
  for (;;)
  {
    if (Serial.available()) serialHandler();
    if (Bluetooth.available()) BluetoothHandler();
    if (btn_up)
    {
      btn_up = false;
      mode++;
      if (mode > 8) mode = 0;
      menu_change();
    }
    if (btn_dwn)
    {
      btn_dwn = false;
      mode--;
      if (mode == 255) mode = 8;
      menu_change();
    }
    battery();
    mode_handler();
    vTaskDelay(pdMS_TO_TICKS(20));
  }
}

void loop() {}

void BluetoothHandler()
{
  String mess = Bluetooth.readString();
  Serial.println(mess);
  if (mess == "RESTART") ESP.restart();
  if (mess == "M0" && mode != 0)
  {
    mode = 0;
    menu_change();
  }
  if (mess == "M1" && mode != 1)
  {
    mode = 1;
    menu_change();
  }
  if (mess == "M2" && mode != 2)
  {
    mode = 2;
    menu_change();
  }
  if (mess == "M3" && mode != 3)
  {
    mode = 3;
    menu_change();
  }
  if (mess == "M4" && mode != 4)
  {
    mode = 4;
    menu_change();
  }
  if (mess == "M5" && mode != 5)
  {
    mode = 5;
    menu_change();
  }
  if (mess == "M6" && mode != 6)
  {
    mode = 6;
    menu_change();
  }
  if (mess == "M7" && mode != 7)
  {
    mode = 7;
    menu_change();
  }
}


void serialHandler()
{
  String mess = Serial.readString();
  if (mess == "r") ESP.restart();
  if (mess == "1")
  {
    uart_flush(PORT_NUM);
    Serial.println("BTN UP");
    mode++;
    if (mode > 8) mode = 0;
    menu_change();
  }
  if (mess == "2")
  {
    Serial.println("BTN DWN");
    mode--;
    if (mode == 255) mode = 8;
    menu_change();
  }
}

void relay(bool state)
{
  pinMode(REL_01, OUTPUT);
  pinMode(REL_02, OUTPUT);
  if (state)
  {
    digitalWrite(REL_01, 1);
    digitalWrite(REL_02, 0);
  }
  else
  {
    digitalWrite(REL_01, 0);
    digitalWrite(REL_02, 1);
  }
  delay(300);
  pinMode(REL_01, INPUT);
  pinMode(REL_02, INPUT);
}
