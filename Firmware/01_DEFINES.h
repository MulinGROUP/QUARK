#define WIDTH                              240   // Ширина дисплея
#define HEIGHT                             135   // Высота дисплея
#define USB_POW                                  // Уровни при подключении USB
#define ADDRES_AD5254_RC                  0x2C   // Адрес потенциометра RC
#define ADDRES_AD5254_OSC                 0x2D   // Адрес потенциометра OSC

#define RXD2                                16   // RX2 пин
#define TXD2                                -1   // TX2 пин
#define SDA1                                21   // Переназначение SDA
#define SCL1                                22   // Переназначение SCL
#define IND_VAL                             35   // Индуктивность  ВХОД
#define SPEAK                               17   // Динамик
#define REL_02                              25   // Реле 1
#define REL_01                              26   // Реле 2
#define POWER                               14   // Включение
#define PCB_LIGHT                           12   // Подсветка платы
#define BUTTON                              27   // Кнопки
#define CHRG                                36   // Статус зарядки
#define ADC_CR                              39   // Вход измерения резисторов и конденсаторов
#define ADC_BAT                             34   // Вход заряда батареи
#define RC_EN                               13   // Включение измерения резисторов и конденасторов
#define IND_EN                              15   // Включение измерения индуктивности
#define L_GEN                                2   // Генератор индуктора

#define RC_ON           digitalWrite(RC_EN, 1)   // Включение коммутатора RC
#define RC_OFF          digitalWrite(RC_EN, 0)   // Выключение коммутатора RC
#define IND_ON         digitalWrite(IND_EN, 1)   // Включение коммутатора индуктора
#define IND_OFF        digitalWrite(IND_EN, 0)   // Выключение коммутатора индуктора
#define PWR_ON          digitalWrite(POWER, 0)   // Питание включено
#define PWR_OFF         digitalWrite(POWER, 1)   // Питание выключено
#define LIGHT_ON    digitalWrite(PCB_LIGHT, 1)   // Подсветка платы включено
#define LIGHT_OFF   digitalWrite(PCB_LIGHT, 0)   // Подсветка платы выключено
#define BATT_LEVEL         analogRead(ADC_BAT)   // Уровень заряда
#define CHRG_ON           digitalRead(CHRG)==0   // Заряд идет
#define CHRG_OFF          digitalRead(CHRG)==1   // Заряд не идет

#define AMPERS                     relay(true)   // Измерение амперов и напряжения
#define MEAS                      relay(false)   // Измерение сопротивления, индуктивности, емкости

//ОСЦИЛЛОГРАФ
#define ADC_CHANNEL             ADC1_CHANNEL_3   // Номер канала осциллографа GPIO39
#define NUM_SAMPLES                       1000   // Количество семплов
#define BUFF_SIZE                         5000   // Размер буфера
#define DISP_WIDTH                         200   // Ширина дисплея осциллографа
#define DISP_HEIGHT                        200   // Ширина дисплея осциллографа

//АМПЕРМЕТР
#define R_SHUNT                            0.5   // Значение шунта Ом. 0.00375
#define V_SHUNT_MAX                      0.075   // Максимальное значение напряжения на шунте.
#define V_BUS_MAX                           26   // Максимальное напряжение шины.
#define I_MAX                              3.2   // Максимальный ток, потребляемый шиной + шунтом.

//ОМЕТР
//Цвета резисторов
#define RES_BACK     0xCD71
#define RES_GOLD_T   0xEC06
#define RES_GOLD_B   0x6226
#define RES_SILVER_T 0x9D35
#define RES_SILVER_B 0x3A8B
#define RES_GRAY_2   0x8C71

#define RES_BLACK    0x0020
#define RES_BROWN    0xB280
#define RES_RED      0xD800
#define RES_ORANGE   0xFC40
#define RES_YELOW    0xE6A0
#define RES_GREEN    0x0583
#define RES_BLUE     0x04FD
#define RES_VIOLET   0x801D
#define RES_GRAY     0x8410
#define RES_WHITE    0xEF7D

//ЕМКОСТЬ
#define CAP_BACK     0xED6B

//UART
#define BUF_SIZE                    (1024 * 2)   // Размер буфера UART
#define PORT_NUM                    UART_NUM_2   // Номер порта UART

//ШРИФТЫ
#define Font_8        "CenturyGothic-8"
#define Font_10       "CenturyGothic-10"
#define Font_12       "CenturyGothic-12"
#define Font_14       "CenturyGothic-14"
#define Font_16       "CenturyGothic-16"
#define Font_18       "CenturyGothic-18"
#define Font_24       "CenturyGothic-24"
#define Font_32       "CenturyGothic-32"
#define Font_48       "CenturyGothic-48"
#define Font_64       "CenturyGothic-64"

// ЦВЕТА
// http://www.barth-dev.de/online/rgb565-color-picker/
// Конвертер
// https://www.rapidtables.com/convert/color/hex-to-rgb.html
//СЕРЫЕ
#define TFT_GRAY     0x2945
#define TFT_GRAY_1   0x94B2
#define TFT_GRAY_2   0x0821
#define TFT_GRAY_3   0xAD75
//КРАСНЫЕ
#define TFT_RED_5    0x5000
//ЗЕЛЕНЫЕ
#define TFT_GREEN_1  0x0602
//СИНИЕ
#define TFT_BLUE_1   0x2A0B
#define TFT_BLUE_5   0x008C
#define HEADER       0x0883
#define TEXT_01      0x7C76
#define TEXT_02      0x9E93
#define OSC_LEFT     0x0001
#define OSC_PINK     0xf818
#define OSC_LEVEL    0xc000
#define DIGIT        0x08C8
//ФИОЛЕТОВЫЕ
#define TFT_VIOL_1   0xD81F
