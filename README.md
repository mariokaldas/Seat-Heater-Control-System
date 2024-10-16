# Seat-Heater-Control-System
Implementation of a seat heater control system for the front two seats in the car (driver seat and passenger  seat) using FreeRTOS and TM4C123GH6PM micro-controller. 

- Hardware components for each seat:
  1- Temperature sensor measure the range (0 deg to 45 deg) but the valid range is (5 deg to 40 deg) if it's out of the valid range that represents failure in the temperature sensor.
  2- Heater (represented by two LEDs, blue and green to indicate intensity of the heater  >> green:low intensity, blue:medium inntensity, cyan:high intensity).
  3- Red LED indicates failure in the temperature sensor if it's out of it's valid range.
  4- Push button to set the required temperature, there are four states representing the desired temperature (off, 25 deg, 30 deg, 35 deg) every press switches between these states in order.
    5- The driver seat has additional push button in the driving wheel to make it easy for the driver.

- This project has three layers of software code:
  1- Application layer Contain the tasks of the RTOS and functions of the application, this layer is the layer that included in main file and it contain of :
    - APP.c : Header file contain FreeRTOS includes, application includes (hardware drivers), other includes(for ex, UART driver), definitions and types declaration, global variables, prototype of all tasks and          functions.
    - APP.c : Source file contain used global variables, hooks implementation, Inerrupt Service Routines (ISRs), functions and tasks implementation.

  2- Hardware Abstraction Layer (HAL) included in application layer and it contain of all used hardware drivers:
    - LED driver (represents the heater intensity and error LED indicator), this driver support up to 15 defined LED.
    - pushbutton driver to set the desired temperature of the each seat, this driver support up to 15 defined push button.
    - Temperature sensor driver that  support ANY kind of temperature sensor and only reqires some parameter about this sensor (minimum and maximum temperature, maximum output voltage).
 
  3- Micro-controller Abstraction Layer (MCAL) included in hardware abstraction layer and it contain of all used drivers to controll the ECU:
    - ADC driver that supports twelve ADC channel, you just need to configure which channel/s you'll use, also this driver supports both techniques (interrupt, polling).
    - GPIO driver that support up to 43 General Purpose Input Output pins.
    - NVIC driver to control all kinds of interrupts in this micro-controller.
    - UART driver that configured to baud rate of 9600 and one stop-bit with no parity bits with data size of 8-bits.
    - General Purpose Timer (GPTM) used for runtime measurements.
 
  4- FreeRTOS files that use : Semaphores and mutexes, Message queues, Event groups.



  
