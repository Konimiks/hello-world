#include <math.h>


double calc(double x, double y, double z)  {
	double a;
	double a0,a1,a2;
	
	
	if(sin(y)==0 || z==0 || (x-y)<=0 || (x+y)==0 || (x-y)==0 || x<0 ) return NAN;
	else{	
   	a0=pow(x,y+1)/pow(x-y,1/z);
  	a1=y/(4*fabs(x+y));
	a2=pow(x,1/fabs(sin(y)));
	
	a=a0+a1+a2;}

	return a;
}
