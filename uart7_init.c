#include <tm4c123gh6pm.h>

void uart7init(void){
	SYSCTL_RCGCUART_R |= 0x80; // Enablibg clock on uart 7
	SYSCTL_RCGCGPIO_R|=0X10; //turning port E on
	while ((SYSCTL_PRGPIO_R&0X10) != 0x10){ };


	//uart settings
	UART7_CTL_R &= ~0x00000001; //disable
	//settings
	UART7_IBRD_R = 104;  //div is 104.1666667
	UART7_FBRD_R = 11;
	UART7_LCRH_R |=0x70; //fifo and word length of 8 bits 0xB0
	//enable
	UART7_CTL_R |= (1<<9) | (1<<8);
	UART7_CTL_R |=(1);
	//GPIO settings
	//gpio a settings
	GPIO_PORTE_DEN_R |= 0x03;
	GPIO_PORTE_AMSEL_R&=~0x03;
	GPIO_PORTE_DIR_R &= ~0x01 ;
	GPIO_PORTE_LOCK_R = 0x4C4F434B;
	GPIO_PORTE_CR_R |= 0x01;
	GPIO_PORTE_AFSEL_R |=0x01;
	GPIO_PORTE_PCTL_R =(GPIO_PORTE_PCTL_R& ~0xFF)+0x01; //enabling alternate function on portE pin 0 as a reciever.

}
