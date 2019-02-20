#include <machine.h>
#include <stdint.h>
#include "iodefine.h"

void init_system_clock(void)
{
    // This is a sample setting for 50MHz system clock and 25MHz timer(CMT0) clock source.
    // See FreeRTOS/portable/ApplicationHook.c - vApplicationSetupTimerInterrupt() to modify Timer(CMT0) Setting
    // and FreeRTOSConfig.h to set system and timer clock.

    SYSTEM.PRCR.WORD = 0xA503; //Write enable

    /* sub clock:stop (If you need to use sub clock(e.g. for RTC), change this setting.) */
    SYSTEM.SOSCCR.BYTE = 1; //sub clock stop
    while(SYSTEM.SOSCCR.BIT.SOSTP != 1); //wait sub clock to be stable
    RTC.RCR3.BIT.RTCEN = 0; //sub clock stop (RTC setting)
    while(RTC.RCR3.BIT.RTCEN); //wait sub clock to be stable (RTC setting)

    SYSTEM.MOFCR.BIT.MODRV21 = 1;
    SYSTEM.MOSCCR.BIT.MOSTP = 0;            //Main clock enable
    while(!SYSTEM.OSCOVFSR.BIT.MOOVF);      //Wait for stable main clock
    while(SYSTEM.OPCCR.BIT.OPCMTSF);
    SYSTEM.OPCCR.BIT.OPCM = 0;              //High Speed Mode
    while(SYSTEM.OPCCR.BIT.OPCMTSF);
    SYSTEM.MEMWAIT.BIT.MEMWAIT = 1;
    while(!SYSTEM.MEMWAIT.BIT.MEMWAIT);
    SYSTEM.PLLCR.BIT.PLIDIV = 1;            //Divide X'tal source 20MHz/2 = 10MHz
    SYSTEM.PLLCR.BIT.STC = 9;               //Multiply 5   --> 50MHz
    SYSTEM.SCKCR.BIT.ICK = 0;               //Divide 1, =50MHz
    SYSTEM.SCKCR.BIT.FCK = 1;               //Divide 2, =25MHz
    SYSTEM.SCKCR.BIT.PCKA = 1;              //PCLKA(MTU source): Divide 2, 50MHz/2 =25MHz
    SYSTEM.SCKCR.BIT.PCKB = 1;              //PCLKB(PWM,SPI,I2C):Divide 2, 50MHz/2 =25MHz
    while(!SYSTEM.SCKCR.BIT.PCKB);


    SYSTEM.SCKCR3.BIT.CKSEL = 0;// PLL Selection disable
    SYSTEM.PLLCR2.BIT.PLLEN = 1; //Stop PLL
    while(SYSTEM.OSCOVFSR.BIT.PLOVF);


    SYSTEM.PLLCR2.BIT.PLLEN = 0;            //Enable PLL
    while(!SYSTEM.OSCOVFSR.BIT.PLOVF);      //Wait for Stable PLL
    SYSTEM.SCKCR3.BIT.CKSEL = 4;            //PLL Select
    SYSTEM.PRCR.WORD = 0xA500;              //Disable allow modify register
}