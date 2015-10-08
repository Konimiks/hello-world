#include <math.h>



int exec(int op, int a, int b) {
   int result;
   int c,k;
   c=b;
   int PI=3.14;
   k=b%8;
   if (op<0) {op=-op; b=a; a=c;}
   switch(op) {
              case 0:
                   result=-a;break;
              case 1:
                   result=a+b;break;
              case 2:
                   result=a-b;break;
              case 3:
                   result=a*b;break;
              case 4:
                   result=a/b;break;
              case 5:
                   result=abs(a);break;
              case 6:
                   if (a>0) result=pow(a,b);
                   else return 0;
                   break;
              case 7:
              case 13:
              case 77:
                   result=a%b;break;
              case 8:
                   if (a>b) result=a;
                   else result=b;
                   break;
              case 9:
                   if (a<b) result=a;
                   else result=b;
                   break;
              case 10:
                   switch(k) {
                               case 0: sizeof(char);break;
                               case 1: sizeof(signed char);break;
                               case 2: sizeof(short);break;
                               case 3: sizeof(unsigned int);break;
                               case 4: sizeof(long);break;
                               case 5: sizeof(unsigned long long);break;
                               case 6: sizeof(float);break;
                               case 7: sizeof(double);break;
                               default:return 0;
                               }
                             
                   result=abs(a)*sizeof(k);break;
              case 11:
                   if (a!=0) result=(4*PI*cos(a*b))/a;
                   else return 0;
                   break;
              default:
                      if(op<100) result=(op%abs(a+1))+(op%abs(b+1));
                      if(op>=100) result=-1;
                      }
   
   
   return result;
}
