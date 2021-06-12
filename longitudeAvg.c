double averaging_lon(double x )
{
static double total = 0;
static int n1 = 0;
double res = 0;
total +=x;
n1++;
if (n1==freq)
{

res = total /n1;
	total=0;
	n1 =0;
	return res ;
	
}
else
{
	return res;
}

	
	
}
