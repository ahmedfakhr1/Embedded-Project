#include "GPIO.h"
double distance = 129;

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
	f = distance / 100;		\\store the first digit in f
	s = (int)distance % 100;
	s = s / 10;			\\store the second digit in s
	t = (int)distance % 10;		\\store the third digit in t
	GPIO_PORTB_DATA_R |= f;		\\Output the first digit from the first 4 bits of port B 
	GPIO_PORTB_DATA_R |= (s<<4);	\\Output the second digit from the last 4 bits of port B
	GPIO_PORTE_DATA_R |= (t<<2);	\\Output the third digit from the last 4 bits of port E
}
int main(){
seg_output();				\\call the function to display the distance(129)
}
