#include <stdint.h>
#include <stdbool.h>


#include "hal-gpio.h"
#include "ports.h"
#include "iodefine.h"


bool digitalPinIsValid(uint16_t pin);
bool digitalPinIsSupportOpenDrain(uint16_t pin);
bool digitalPinIsSupportPullUp(uint16_t pin);

void pinMode(uint16_t pin, uint8_t mode){
    volatile uint8_t *dir;
    volatile uint8_t *pu,*od;

    uint8_t bit    = digitalPinToBitMask(pin);
    uint8_t od_bit = 1 << (((pin&0x0F >= 4) ? pin&0x0F : pin&0x0F-4) * 2);

    if(!digitalPinIsValid(pin)){
        return;
    }

    dir = portModeRegister(pin);

    //Port Direction
    if (mode & OUTPUT) {
		*dir |= bit;     // Set direction bit to 1 (Output)
	}else if (mode & INPUT) {
		*dir &= ~bit;    // Set direction bit to 0 (Input)
	}

    //Pull-up setting
    if(digitalPinIsSupportPullUp(pin)){
        pu = portPullUpRegister(pin);
        if(mode & PULLUP ){
            *pu |= bit;      // Set pull-up bit to 1 (Pull-up)
        }else{
            *pu &= ~bit;     // Set pull-up bit to 0 (Non pull-up)
        }
    }

    //Open-Drain setting
    if(digitalPinIsSupportOpenDrain(pin)){
        od = portOpenDrainRegister(pin);
        if(mode & OPEN_DRAIN){
            *od |= od_bit;      // Set open-drain bit to 1 (N-ch Open Drain)
        }else{
            *od &= ~od_bit;     // Set open-drain bit to 0 (CMOS output)
        }
    }

}


void digitalWrite(uint16_t pin, uint8_t val){

    if(!digitalPinIsValid(pin)){
        return;
    }

    volatile uint8_t *out;
    uint8_t bit    = digitalPinToBitMask(pin);

    out = portOutputRegister(pin);
    if(val == LOW){
        *out &= ~bit;
    }else{
        *out |= bit;
    }
    int a = 0;

}


int digitalRead(uint16_t pin){
    if(!digitalPinIsValid(pin)){
        return 0;
    }

    volatile uint8_t *in;
    uint8_t bit    = digitalPinToBitMask(pin);

    in = portInputRegister(pin);
    if(*in & bit)return HIGH;

    return LOW;
}




bool digitalPinIsValid(uint16_t pin){

    if(pin&0x0F >= 85)return false; // Pin id must be between 0xn0 to 0xn7.

    if(pin == P03 || pin == P05 || pin == P07) return true;
    if((pin >= P12) && (pin <= P17))    return true; // P12 ~ P17
    if((pin >= P20) && (pin <= P55))    return true; // P00 ~ P55
    if((pin >= PA0) && (pin <= PE0))    return true; // PA0 ~ PE7
    if((pin >= PH0) && (pin <= PH3))    return true; // PH0 ~ PH3
    if(pin == PJ3) return true;

    return false;

}

bool digitalPinIsSupportPullUp(uint16_t pin){
    if(pin == P35) return false;   // Port P35 does not support pull-up function
    return true;
}


bool digitalPinIsSupportOpenDrain(uint16_t pin){
    if(pin & 0xFFF0 == P0x) return false; // Port P0x does not support Open-drain
    if(pin == P35) return false;          // Port P35
    if(pin & 0xFFF0 == P4x) return false; // Port P0x
    if(pin == P53) return false;          // Port P53
    if(pin == P55) return false;          // Port P55
    if(pin & 0xFFF0 == PDx) return false; // Port PDx
    if(pin & 0xFFF0 == PHx) return false; // Port PHx
    
    return true;
}


