#define R 6371
#define pi 3.141592653589793238
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double totalDistance;

double coordinatesetting (double x,char y){
if(y= 'S' || 's' || 'W' || 'w' ){x=x*-0.01;}
else{x=x*0.01;}
return x;
}


double dist(double lon1, double lon2,double lat1,double lat2){
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
double sumDis(double x){

totalDistance+=x;
	
return totalDistance;
}

int main()
{

    double d = dist( 0.1246, 74.0445,51.5007,40.6892);
//	printf("dist: %lf m \n", d); // in meters

	return 0;
}
