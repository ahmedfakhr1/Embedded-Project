int UART_Available(){
	
	return ((UART7_FR_R & 0x10) == 0x10)? 0:1;
}

char UART_read(){
	while(UART_Available() != 1);

	return UART7_DR_R & 0xFF;
}