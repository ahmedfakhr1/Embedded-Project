#include <stdio.h>
#include <stdlib.h>
#include "GPIO.h"
#include <math.h>
#define pi 3.141592653589793238
#define R 6371
#define TO_RAD (3.1415926536 / 180)

double latitude;
double longitude;
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
	f = distance / 100;		\\store the first digit in f
	s = (int)distance % 100;
	s = s / 10;			\\store the second digit in s
	t = (int)distance % 10;		\\store the third digit in t
	GPIO_PORTB_DATA_R |= f;		\\Output the first digit from the first 4 bits of port B 
	GPIO_PORTB_DATA_R |= (s<<4);	\\Output the second digit from the last 4 bits of port B
	GPIO_PORTE_DATA_R |= (t<<2);	\\Output the third digit from the last 4 bits of port E
}

void led_on(){
	if(distance > 100){
		GPIO_PORTF_DATA_R |= 0x0E;
		led = 1;
	}
}

double To_decimal(double i){
	int a;
	double b;
	a = i/100;
	b = (i/100 - a)* 100;
	b /= 60;
	b += a;
	return b;
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

int  ADD_distance(int dist, int* olddist){
	dist += *olddist;
	*olddist = dist;
	return dist;
}


void parse_msg(char * msg){
    int counter = 1;
    int n1;
    int n2;
    char * element = strtok(msg, ",");

    while( element!= NULL ) {
        element = strtok(NULL, ",");
        switch(counter){
            case 2 :
            latitude = strtod(element,NULL);
            break;
            case 3 :
            n1 = (*element == 'N') ? 1 : -1;
            latitude *= n1 ;
            break;
            case 4 :
            longitude = strtod(element,NULL);
            break;
            case 5 :
            n2 = (*element == 'E') ? 1 : -1;
            longitude *= n2 ;
        }
        counter++;
    }
}

int main(){
	static double lon1 ;
	static double lat1 ;
	static double lon2 ;
	static double lat2 ;
	int n;
	static char v;
	int ti=0;
	int i =6;
	char gps_msg[100];
//	char gps_msg[100] = "$GPGGA,181908.00,3404.7041778,N,07044.3966270,W,4,13,1.00,495.144,M,29.200,M,0.10,0000*40";
	PortFInit();
	PortBInit();
	PortEInit();
	uart0init();
//	UART_write('e');
//	if(strstr(gps_msg, "$GPGGA")){
//		parse_msg(gps_msg);
//	}
//	lon1 = To_decimal(longitude);
//	lat1 = To_decimal(latitude);
	
	
	while ( distance < 100){
			while (1){
		v = UART_read();

//		UART_write(v)/
		if (v == '$'){
			for(ti=0;ti<6;ti++){
			gps_msg[ti] = v;

		 v = UART_read();
			}
			if(gps_msg[1] =='G'){
			if(gps_msg[2] == 'P'){
				if(gps_msg[3] == 'G'){
					if(gps_msg[4] == 'G'){
					if(gps_msg[5] == 'A'){
						i=7;
						gps_msg[6] = ',';

							while (v != '*'){
							v = UART_read();
							gps_msg[i] = v;
							i++;
							
				
			}
							for (n = 0 ; n<100 ; n++){
							if(gps_msg[n]== 'M'){
								turnRedOn(1);
								break;
							}
							}
				parse_msg(gps_msg);
				break;
			}
		}
		}
		}

					

		}
				memset(gps_msg,0,100);
	}
}
//		if(strstr(gps_msg, "$GPGGA")){
//			parse_msg(gps_msg);
//		}
		lon2 = lon1;
		lat2 = lat1;
		lon1 = To_decimal(longitude);
		lat1 = To_decimal(latitude);
		//distance = dist(36.12, -86.67 , 33.94, -118.4);
	//	distance = dist(lat1, lon1 , lat2, lon2);
		if(lon2 != 0 && lat2 !=0){
		distance +=dist(lat1, lon1 , lat2, lon2);
		if(led == 0){led_on();}
		seg_output();
		}
		memset(gps_msg,0,100);
//		strcpy(gps_msg,"$GPGGA,181908.00,7404.7041778,N,07044.3968270,W,4,13,1.00,495.144,M,29.200,M,0.10,0000*40");

	}



  
//  turnRedOn(1);
//  seg_output();
	while(1);
}
