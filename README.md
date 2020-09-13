# FredlMK2
outdoor robot for robotour

#### Connections of Arduino MKR Vidor 4000

* **MKR connector** (2.54 mm pinheader, 28 pins)

| **Pin** | **Pin Name** | **Signal**    | **Description**                |
|:-------:|:------------:|:-------------:|:------------------------------:|
| 1       | AREF         | not connected |                                |
| 2       | DAC0/A0      |               | input voltage sense            |
| 3       | A1           | BARRELSWITCH  | BARRELSWITCH                   |
| 4       | A2           | KEYPAD        | HMI switches on ArduHMI        |
| 5       | A3           |               |                                |
| 6       | A4           | EMERGENCYSTOP | EMERGENCYSTOP                  |
| 7       | A5           |               |                                |
| 8       | A6           | BACKLIGHT     | ArduHMI Backlight              |
| 9       | D0           | DIS_A0        | ArduHMI A0                     |
| 10      | D1           | DIS_RESET     | ArduHMI RESET                  |
| 11      | D2           |               |                                |
| 12      | D3           | MCP2515_CS    | like MKRCANShield / not used   |
| 13      | D4           | STEPPER2_CS   |                                |
| 14      | D5           | STEPPER1_CS   |                                |
| 15      | D6           | DIS_CS        | ArduHMI SS                     |
| 16      | D7           | MCP2515_INT   | like MKRCANShield / not used   |
| 17      | D8/MOSI      | MOSI          | SPI                            |
| 18      | D9/SCK       | SCK           | SPI                            |
| 19      | D10/MISO     | MISO          | SPI                            |
| 20      | D11/SDA      | SDA           | I2C for sensors                |
| 21      | D12/SCL      | SCL           | I2C for sensors                |
| 22      | D13/RX       | GPS_RX        | communication with gps module  |
| 23      | D14/TX       | GPS_TX        | communication with gps module  |
| 24      | RESET        | RESET         | reset button on various boards |
| 25      | GND          | GND           |                                |
| 26      | 3V3          | 3V3-rail      | supply voltage for sensors ... |
| 27      | VIN          | 5V in         | input from voltage regulator   |
| 28      | 5V           | 5V out        | 5V output to display           |

