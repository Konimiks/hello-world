#include <math.h>


int satisfies(int a, int b,int c) {
    int result;
    int modmin;
    int sum2;
    int max;
    int min;
    
    
    if (a<0 && b<0 && c<0) {
            if(a<b && a<c) {modmin=abs(a);}
            else if (b<a || b<c) {modmin=abs(b);}
            else {modmin=abs(c);}
            
            if (modmin=abs(a)) {sum2=b+c;}
            else if (modmin=abs(b)) {sum2=a+c;}
            else {sum2=a+b;}
            
            if(sum2<(-256) && modmin<256 && (modmin==1 || modmin==2 || modmin==4 || modmin==8 || modmin==16 || modmin==32 || modmin==64 || modmin==128))
            return 1; 
            else if(abs(sum2)>modmin && sum2>(-256)) return 1;
            else return 0;
            }
    if (a<0 || b<0 || c <0) {
            if(a<0 && b>=0 && c>=0) {if(a>(-256)) return 1; else return 0;}
            else if (b<0 && a>=0 && c>=0) {if(b>(-256)) return 1; else return 0;}
            else if(c<0 && a>=0 && b>=0) {if(c>(-256)) return 1; else return 0;}
            
            if(a<0 && b<0 && c>=0) {if((a+b)*3>(-256)) return 1; else return 0;}
            else if (a<0 && c<0 && b>=0) {if((a+c)*3>(-256)) return 1; else return 0;}
            else if(b<0 && c<0 && a>=0) {if((b+c)*3>(-256)) return 1; else return 0;}
            }
    if (a>=0 && b>=0 && c>=0) {
            if(a>b && a>c) max=a;
            else if(b>a && b>c) max=b;
            else max=c;
            
            if(a<b && a<c) min=a;
            else if(b<a && b<c) min=b;
            else min=c;
            
            if (min==0) return 0;
            else if (max%min==0) return 1;
            else if (max==0 && min!=0) return 0;
            else return 0; }
            
          return result;
          }            
