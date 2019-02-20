# FreeRTOS port for Renesas RX231(RXv2 core) with CS+ project


# Clock preference
This sample project is based on this clock speed.

 - External XTAL: 20MHz 
 - CPU Clock: 50MHz
 - Tick Timer(CMT0): 25MHz

## Clock Settings
- `FreeRTOS/FreeRTOSConfig.h`  : Set CPU and tick timer clock
- `FreeRTOS/system/clock.c`    : Clock Generator Setting
- `FreeRTOS/portable/ApplicationHook.c`-`vApplicationSetupTimerInterrupt()` : Tick Timer(CMT0) Setting


# Memory management

## Heap althorithm
 Currently using heap_3.c for this project. You can swap heap algorithm as you like. See: https://www.freertos.org/a00111.html

## Heap size
 Heap size is defined on `FreeRTOS/renesas/sbrk.h`, Edit here to change heap size as your application requires.