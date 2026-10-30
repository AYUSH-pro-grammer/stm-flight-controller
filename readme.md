## Flight Controller
A flight controller I designed to understand more about how drones are stable and how all the sensors interact. I created my own custom PCB using KiCad which includes an STM32F405, IMU, Magnetometer and Barometer. It has been a great way to learn about embedded systems, sensor calibration and PCB design, but has shown me what can go wrong when creating hardware. There is still plenty to learn before its ready to fly!

## How it works

This is a flight controller board which I have designed to learn how drones work and how they stay stable. The board contains an STM32F405 microcontroller as well as several sensors.

STM32F405 - This is the central processing unit of the board. It collects and processes the data from the sensors.
MPU6050 - The MPU6050 contains an accelerometer and gyroscope to give an understanding of the movement, rotation and tilting of the drone.
LIS3MDL - The LIS3MDL contains a magnetometer, which works like a digital compass.
BMP280 - The BMP280 gives information about the air pressure and temperature. The pressure can be used to determine the altitude of the drone.
Power management - There is a power management circuit on the board to provide the correct voltages to each of the components.
Communication - The sensors are connected to the STM32F405 using I2C. This means the microcontroller can collect the data from the sensors.


## Images

**Schematic View**
![Flight Controller Schematic](image/schamtic.png)

**PCB View**
![PCB Layout](image/pcb_view.png)

**Front View**
![PCB Front 3D View](image/pcb_front_3d.png)

**Back View**
![PCB Back 3D View](image/pcb_back_3d.png)

# BOM 

| Reference | Component | Quantity | Link | Cost |
|---|---|---:|---|---:|
| C1; C5 | YAGEO 10pF 0402 | 2 | [LCSC](https://www.lcsc.com/product-detail/C3860506.html) | |
| C2 | CCTC 10uF 0805 | 1 | [LCSC](https://www.lcsc.com/product-detail/C380331.html) | |
| C3; C7; C13; C23; C24; C28; C29 | FH 100nF 0603 | 7 | [LCSC](https://www.lcsc.com/product-detail/C30926.html) | |
| C4; C6; C9; C11; C12; C17; C18; C19; C20; C21; C22 | FH 100nF 0603 | 11 | [LCSC](https://www.lcsc.com/product-detail/C30926.html) | |
| C8; C10 | Samsung 2.2uF 0603 | 2 | [LCSC](https://www.lcsc.com/product-detail/C23630.html) | |
| C14 | CCTC 10nF 0402 | 1 | [LCSC](https://www.lcsc.com/product-detail/C688874.html) | |
| C15; C16 | SAMWHA 1uF 0603 | 2 | [LCSC](https://www.lcsc.com/product-detail/C513775.html) | |
| C25; C26 | YAGEO 22uF 1210 | 2 | [LCSC](https://www.lcsc.com/product-detail/C5341638.html) | |
| C27 | KEMET 220pF 0603 | 1 | [LCSC](https://www.lcsc.com/product-detail/C3843887.html) | |
| C30 | Samsung Electro-Mechanics CL10A105KB8NNNC 1uF 50V 0603 | 1 | [LCSC](https://www.lcsc.com/product-detail/C15849.html) | |
| C31 | YAGEO 4.7uF 0805 25V | 1 | [LCSC](https://www.lcsc.com/product-detail/C5185457.html) | |
| C32 | FH 4.7uF 0805 25V | 1 | [LCSC](https://www.lcsc.com/product-detail/C274413.html) | |
| C33 | CCTC 10nF 0603 | 1 | [LCSC](https://www.lcsc.com/product-detail/C282516.html) | |
| C34 | FH 2.2nF 0603 | 1 | [LCSC](https://www.lcsc.com/product-detail/C1604.html) | |
| C35 | YAGEO 22pF 0603 | 1 | [LCSC](https://www.lcsc.com/product-detail/C2240294.html) | |
| C36 | YAGEO 10nF 0603 | 1 | [LCSC](https://www.lcsc.com/product-detail/C100042.html) | |
| C37; C38 | CCTC 47uF 1210 | 2 | [LCSC](https://www.lcsc.com/product-detail/C53327077.html) | |
| C39 | KEMET 100nF 0805 | 1 | [LCSC](https://www.lcsc.com/product-detail/C141162.html) | |
| D1 | DIODES SD103ATW-7-F Schottky diode array | 1 | [LCSC](https://www.lcsc.com/product-detail/C3758863.html) | |
| D2 | Hubei KENTO Blue LED 0603 | 1 | [LCSC](https://www.lcsc.com/product-detail/C2288.html) | |
| D3; D6 | Yongyu Red LED 0603 | 2 | [LCSC](https://www.lcsc.com/product-detail/C434419.html) | |
| D4 | Comchip SS54-HF | 1 | [LCSC](https://www.lcsc.com/product-detail/C3757794.html) | |
| D5 | High Diode BAT54C | 1 | [LCSC](https://www.lcsc.com/product-detail/C466637.html) | |
| FB1 | Murata BLM18PG121SN1D Ferrite Bead | 1 | [LCSC](https://www.lcsc.com/product-detail/C14709.html) | |
| FB2; FB3 | TAI-TECH HCB1608KF-121T30 120R Ferrite Bead 0603 | 2 | [LCSC](https://www.lcsc.com/product-detail/C353920.html) | |
| J1 | HMTCONN Micro-USB B SMD right-angle | 1 | [LCSC](https://www.lcsc.com/product-detail/C53121380.html) | |
| J2; J4; J23; J17; J19; J20; J21; J24; J25; J26; J28 | BOOMELE 2.54mm 1x40P male header strip (cut to length) | 2 | [LCSC](https://www.lcsc.com/product-detail/C2337.html) | |
| J3 | Hirose DM3AT-SF-PEJM5 MicroSD Connector | 1 | [LCSC](https://www.lcsc.com/product-detail/C114218.html) | |
| L1 | KOHERelec MDA7030-4R7M 4.7uH | 1 | [LCSC](https://www.lcsc.com/product-detail/C2847483.html) | |
| R1 | YAGEO 1k 0603 | 1 | [LCSC](https://www.lcsc.com/product-detail/C22548.html) | |
| R2 | SEI 332k 1206 | 1 | [LCSC](https://www.lcsc.com/product-detail/C2486051.html) | |
| R3; R4; R12; R19 | YAGEO 1.5k 0603 | 4 | [LCSC](https://www.lcsc.com/product-detail/C114668.html) | |
| R5 | Vishay 10k 0805 | 1 | [LCSC](https://www.lcsc.com/product-detail/C844937.html) | |
| R6; R7; R8; R9; R10; R11 | YAGEO 4.7k 0603 | 6 | [LCSC](https://www.lcsc.com/product-detail/C99782.html) | |
| R15 | SEI 35.7k 1206 | 1 | [LCSC](https://www.lcsc.com/product-detail/C2533888.html) | |
| R16 | YAGEO 0 ohm 0603 | 1 | [LCSC](https://www.lcsc.com/product-detail/C95177.html) | |
| R17 | TE Connectivity 10.5k 1206 | 1 | [LCSC](https://www.lcsc.com/product-detail/C2084092.html) | |
| SW1 | C&K PCM12 SPDT Slide Switch | 1 | [LCSC](https://www.lcsc.com/product-detail/C221841.html) | |
| SW2 | C&K PTS647 Tactile Switch | 1 | [LCSC](https://www.lcsc.com/product-detail/C2800043.html) | |
| U1 | TDK InvenSense MPU-6050 | 1 | [LCSC](https://www.lcsc.com/product-detail/C24112.html) | |
| U2 | ST STM32F405RGT6 | 1 | [LCSC](https://www.lcsc.com/product-detail/C15742.html) | |
| U3 | AMS1117-3.3 | 1 | [LCSC](https://www.lcsc.com/product-detail/C6186.html) | |
| U4 | ST LIS3MDLTR | 1 | [LCSC](https://www.lcsc.com/product-detail/C478483.html) | |
| U5 | Bosch BMP280 Digital Pressure Sensor | 1 | [Robu](https://robu.in/product/bosch-bmp280-digital-pressure-sensor/) | |
| U6 | TI TPS5431DDA | 1 | [LCSC](https://www.lcsc.com/product-detail/C1355446.html) | |
| U7 | ST USBLC6-2SC6 | 1 | [LCSC](https://www.lcsc.com/product-detail/C7519.html) | |
| Y1 | DIODES FY1600066 16MHz Crystal | 1 | [LCSC](https://www.lcsc.com/product-detail/C5717615.html) | |
| PCB | PCB fabrication | 1 | — | $8.00 |
| **TOTAL** | **Components + PCB fabrication** | | | **$52.0474** |

