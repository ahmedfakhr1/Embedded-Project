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
	int old_dist;
	int b;
	int xx=0;
	PortFInit();
	PortBInit();
	PortEInit();
	uart0init();

	while ( distance < 100){

		for(xx=0;xx<freq;xx++){
			while (1){
				v = UART_read();
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
										lon = To_decimal(longitude);
										lat = To_decimal(latitude);
										lat = averaging_lat(lat);
										lon = averaging_lon(lon);
										break;
									}
								}
							}
						}
					}
					memset(gps_msg,0,100);
				}
			}
		}
		lon2 = lon1;
		lat2 = lat1;
		lon1 = lon;
		lat1 = lat;
		if(lon2 != 0 && lat2 !=0){
			old_dist = distance;
			distance +=dist(lat1, lon1 , lat2, lon2);
			if(distance - old_dist >5){
				distance -= 5;
			}
			if(distance - old_dist >10){
				distance -= 10;
			}
			if(distance - old_dist >20){
				distance -= 20;
			}
			if(distance <= 0){
				lon1 = lon2;
				lat1 = lat2;
				distance = old_dist;
			}
			if(led == 0){
				led_on();
			}
		}
		memset(gps_msg,0,100);
	}
	seg_output();
	while(1);
}