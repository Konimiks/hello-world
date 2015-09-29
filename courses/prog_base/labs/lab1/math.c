double calc(double x,double y,double z)  {
	
	double a;

	double b;	
	double c;
	double d;
	
	b=pow(x,y+1)/pow(x-y,1/z);
	c=y/(4*abs(x+y));
	d=pow(x,1/abs(sin(y)));
	
	a=b+c+d;

	return a;
}
