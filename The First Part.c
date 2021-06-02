#include <stdio.h>
#include <stdlib.h>
#include "GPIO.h"

void PortFInit(void){
    SYSCTL_RCGCGPIO_R |= 0x20;
    while((SYSCTL_PRGPIO_R & 0x20) != 0x20);
    GPIO_PORTF_LOCK_R = 0x4C4F434B;
    GPIO_PORTF_DIR_R = 0x0E;
    GPIO_PORTF_CR_R = 0xff;
    GPIO_PORTF_DEN_R = 0xff;
    GPIO_PORTF_AMSEL_R &= ~0x0E;
    GPIO_PORTF_PCTL_R &= ~0x0000FFF0;
}