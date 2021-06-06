#include <stdio.h>
#include <stdlib.h>
#include "GPIO.h"
#include <math.h>
#define pi 3.141592653589793238
#define R 6371
#define TO_RAD (3.1415926536 / 180)

 double distance = 0;
 int led = 0; 

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
	s = (int)distance % 100;
	s = s / 10;
	t = (int)distance % 10;
	GPIO_PORTB_DATA_R |= f;
	GPIO_PORTB_DATA_R |= (s<<4);
	GPIO_PORTE_DATA_R |= (t<<2);
}

void led_on(){
if(distance > 100){
GPIO_PORTF_DATA_R |= 0x0E;
	led = 1;
}
}




double dist(double lat1, double lon1,double lat2,double lon2){
double lon,lat;
double a,b,c,d,dis;

lon=lon2-lon1;
lat=lat2-lat1;
lon=lon*(pi/180.0);
lat=lat*(pi/180.0);

a=pow(sin(lat/2.0),2.0);
b=cos(lat1*(pi/180.0));
c=cos(lat2*(pi/180.0));
d=pow(sin(lon/2.0),2.0);
dis=sqrt(a+b*c*d);
dis=2*R*asin(dis);

return dis*1000; // RETURN DISTANCE IN METERS

}


int main(){
	PortFInit();
	PortBInit();
	PortEInit();
	while ( distance < 10000*1000){
		distance += dist(36.12, -86.67 , 33.94, -118.4);
		if(led == 0){led_on();}

	}
	seg_output();
	while(1);
}
