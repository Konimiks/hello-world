#include <math.h>


double calc(double x, double y, double z)  {
	double a;


	if(sin(y)==0 || z==0 || (x-y)<=0 || (x+y)==0 || x<0 ) {return NAN;}
	else{

	a=(pow(x,y+1)/pow(x-y,1/z))+(y/(4*fabs(x+y)))+(pow(x,1/fabs(sin(y))));
    }

	return a;
}
