#include "GPIO.h"
unsigned int distance = 129;

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

void PortEInit(void){
	SYSCTL_RCGCGPIO_R |= 0x10;
	while((SYSCTL_PRGPIO_R & 0x10) != 0x10);
	GPIO_PORTE_LOCK_R = 0x4C4F434B;
	GPIO_PORTE_DIR_R = 0x3C;
	GPIO_PORTE_CR_R = 0x3F;
	GPIO_PORTE_DEN_R = 0x3C;
	GPIO_PORTE_AMSEL_R &= ~0x3C;
	GPIO_PORTE_PCTL_R &= ~0xFFFF00;
}

void seg_output(void){
	unsigned int f;
	unsigned int s;
	unsigned int t;
	f = distance / 100;
	s = distance % 100;
	s = s / 10;
	t = distance % 10;
	GPIO_PORTB_DATA_R |= f;
	GPIO_PORTB_DATA_R |= (s<<4);
	GPIO_PORTE_DATA_R |= (t<<2);
}
int main(){
seg_output();
}
