#pragma once

#include <stdint.h>

#define P0x   0x0000
#define P03   P0x + 3
#define P05   P0x + 5
#define P07   P0x + 7

#define P1x   0x0010
#define P12   P1x + 2
#define P13   P1x + 3
#define P14   P1x + 4
#define P15   P1x + 5
#define P16   P1x + 6
#define P17   P1x + 7

#define P2x   0x0020
#define P20   P2x + 0
#define P21   P2x + 1
#define P22   P2x + 2
#define P23   P2x + 3
#define P24   P2x + 4
#define P25   P2x + 5
#define P26   P2x + 6
#define P27   P2x + 7

#define P3x   0x0030
#define P30   P3x + 0
#define P31   P3x + 1
#define P32   P3x + 2
#define P33   P3x + 3
#define P34   P3x + 4
#define P35   P3x + 5
#define P36   P3x + 6
#define P37   P3x + 7

#define P4x   0x0040
#define P40   P4x + 0
#define P41   P4x + 1
#define P42   P4x + 2
#define P43   P4x + 3
#define P44   P4x + 4
#define P45   P4x + 5
#define P46   P4x + 6
#define P47   P4x + 7

#define P5x   0x0050
#define P50   P5x + 0
#define P51   P5x + 1
#define P52   P5x + 2
#define P53   P5x + 3
#define P54   P5x + 4
#define P55   P5x + 5

#define PAx   0x00A0
#define PA0   PAx + 0
#define PA1   PAx + 1
#define PA2   PAx + 2
#define PA3   PAx + 3
#define PA4   PAx + 4
#define PA5   PAx + 5
#define PA6   PAx + 6
#define PA7   PAx + 7

#define PBx   0x00B0
#define PB0   PBx + 0
#define PB1   PBx + 1
#define PB2   PBx + 2
#define PB3   PBx + 3
#define PB4   PBx + 4
#define PB5   PBx + 5
#define PB6   PBx + 6
#define PB7   PBx + 7

#define PCx   0x00C0
#define PC0   PCx + 0
#define PC1   PCx + 1
#define PC2   PCx + 2
#define PC3   PCx + 3
#define PC4   PCx + 4
#define PC5   PCx + 5
#define PC6   PCx + 6
#define PC7   PCx + 7

#define PDx   0x00D0
#define PD0   PDx + 0
#define PD1   PDx + 1
#define PD2   PDx + 2
#define PD3   PDx + 3
#define PD4   PDx + 4
#define PD5   PDx + 5
#define PD6   PDx + 6
#define PD7   PDx + 7

#define PEx   0x00E0
#define PE0   PEx + 0
#define PE1   PEx + 1
#define PE2   PEx + 2
#define PE3   PEx + 3
#define PE4   PEx + 4
#define PE5   PEx + 5
#define PE6   PEx + 6
#define PE7   PEx + 7

#define PHx   0x0110
#define PH0   PHx + 0
#define PH1   PHx + 1
#define PH2   PHx + 2
#define PH3   PHx + 3

#define PJx   0x0110
#define PJ3   PJx + 3

#define portModeRegister(P)         (uint8_t*)(((P & 0xFFF0) >> 4) + 0x0008C000)  // RX231 Specific : PDR
#define portOutputRegister(P)       (uint8_t*)(((P & 0xFFF0) >> 4) + 0x0008C020)  // RX231 specific : PODR
#define portInputRegister(P)        (uint8_t*)(((P & 0xFFF0) >> 4) + 0x0008C040)  // RX231 specific : PIDR
#define portOpenDrainRegister(P)    (uint8_t*)(((P & 0xFFF0) >> 4)*2 + 0x0008C080 + ((P&0x0F)>=4?1:0))  // RX231 specific : ODR
#define portPullUpRegister(P)       (uint8_t*)(((P & 0xFFF0) >> 4) + 0x0008C0C0)  // RX231 specific : PCR

#define digitalPinToBitMask(P)      (1 << (0xF & P))
