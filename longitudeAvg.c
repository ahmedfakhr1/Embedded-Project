
/*This code for getting the average of the longitudes 
we have assign a global variable called (freq) so that we
could divide the sum of numbers oflongitudes on it 
so that we could reduce the error
*/

double averaging_lon(double x )
{
static double total = 0;
static int n1 = 0;
double res = 0;
total +=x;
n1++;
if (n1==freq)// freq is a global variable
{

res = total /n1;
	total=0;
	n1 =0;
	return res ; // res --> the result after getting the average of the longetudes 
	
}
	return res;
}
