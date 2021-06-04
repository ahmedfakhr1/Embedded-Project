#include <tm4c123gh6pm.h>

void uart0init(void){
SYSCTL_RCGCGPIO_R |=0X00000001; //turning port a on
SYSCTL_RCGCUART_R |=0x00000001;
while ((SYSCTL_PRGPIO_R&0X01) != 1){ };





//uart settings
UART0_CTL_R &= ~0x00000001; //disable
//settings
UART0_IBRD_R = 104;  //div is 104.1666667
UART0_FBRD_R = 11;
UART0_LCRH_R |=0x70; //fifo and word length of 8 bits
//enable
UART0_CTL_R |= (1<<8) | (1<<9);
UART0_CTL_R |=(1);


//gpio a settings
GPIO_PORTA_DEN_R |= 0xFF;
GPIO_PORTA_AMSEL_R&=~0xFF;
GPIO_PORTA_DIR_R |= 0x02 & (~0x01);
GPIO_PORTA_LOCK_R = 0x4C4F434B;
GPIO_PORTA_CR_R |= 0xFF;
GPIO_PORTA_AFSEL_R |=0x03;
GPIO_PORTA_PCTL_R |=0x11&(~0xFFFFFF00);
}
