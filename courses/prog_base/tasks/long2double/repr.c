#include <math.h>
#include <stdio.h>

double long2double(long long b)
{

short znak, i;
double Man=0.0, result;
int E;
if ((b>>63)==0){
znak = 0;
E = (b>>52);
}
else {
znak=1;
E = abs((b>>52)+1);
}
for (i = 51; i >= 0; --i) {
Man+=(((b>>i)&1)*(pow(2, i - 52)));
}
if ((E == 2047) && (Man!=0.0)) return NAN;
if ((E == 2047) && (Man == 0.0) && (znak == 1) )return -INFINITY;
if ((E == 2047) && (Man == 0.0) && (znak == 0))return INFINITY;
if ((E > 0) && (E <2047)) {result = (pow(-1,znak)* pow(2,E-1023)*(1+Man));
return result;}
if ((E == 0) && (Man !=0.0)) {result = (pow(-1, znak)* pow(2, -1022)*(Man));
return result;}
if ((E == 0) && (Man == 0.0) && (znak == 1)) return -0.0;
if ((E == 0) && (Man == 0.0) && (znak == 0)) return 0;

}
