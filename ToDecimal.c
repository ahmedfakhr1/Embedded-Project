
double To_decimal (double i)
{
	int a;
	double b;
	a = i/100;
	b = ((i/100)-a)*100;
	b/=60;
	b+=a;
	return b ;
}