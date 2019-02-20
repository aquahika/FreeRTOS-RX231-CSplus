#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


#define LOW               0x0
#define HIGH              0x1

#define INPUT             0x01
#define OUTPUT            0x02
#define PULLUP            0x04
#define OPEN_DRAIN        0x08

void pinMode(uint16_t pin, uint8_t mode);
void digitalWrite(uint16_t pin, uint8_t val);
int digitalRead(uint16_t pin);

#ifdef __cplusplus
}
#endif
