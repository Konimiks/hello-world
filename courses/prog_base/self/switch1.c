#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main () {
    int m;
    int code;
    int h;
    double cost;
    
    if (code>=10 && code<=999) {
                               switch(code) {
                                            case 44:
                                                 cost=(h*60+m)*0.77;
                                                 printf("%lf",cost);break;
                                            case 62:
                                                 cost=(h*60+m)*0.8;
                                                 printf("%lf",cost);break;                                           
                                            case 32:
                                                 cost=(h*60+m)*0.95;
                                                 printf("%lf",cost);break;
                                            case 692:
                                            case 697:
                                                 cost=(h*60+m)*1.5;
                                                 printf("%lf",cost);break;
                                            default:
                                                    cost=(h*60+m)*1;
                                                    printf("%lf",cost);break;
                                                 }
                                                 }
                               
    return 0;
}
    
    
