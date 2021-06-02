#include <stdio.h>
#include <stdlib.h>
#include "GPIO.h"

void PortBInit(void){
	SYSCTL_RCGCGPIO_R |= 0x02;
	while((SYSCTL_PRGPIO_R & 0x02) != 0x02);
	GPIO_PORTB_LOCK_R = 0x4C4F434B;
	GPIO_PORTB_DIR_R |= 0xff;
	GPIO_PORTB_CR_R = 0xff;
	GPIO_PORTB_DEN_R = 0xff;
	GPIO_PORTB_AMSEL_R &= ~0xff;
	GPIO_PORTB_PCTL_R &= ~0xFFFFFFFF;
}
