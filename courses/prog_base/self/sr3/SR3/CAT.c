#include <stdlib.h>
#include <stdio.h>

int myfunc();

struct coord {
    int x;
    int y;
};


int main(void) {
    FILE *fp;
    struct coord squarex1, squarey1, squarex2, squarex3, squarex4, squarey2,squarey3, squarey4, roundx, roundy;
    int radius;
    fp = fopen("readthis.txt", "r");
    if(NULL == fp) {
        printf("CANNOT READ");
        return 1;
    }
    printf("i read!\n");
    fscanf(fp, "%i", &squarex1.x);
    fscanf(fp, "%i", &squarey1.y);
    fscanf(fp, "%i", &squarex2.x);
    fscanf(fp, "%i", &squarey2.y);
    fscanf(fp, "%i", &squarex3.x);
    fscanf(fp, "%i", &squarey3.y);
    fscanf(fp, "%i", &squarex4.x);
    fscanf(fp, "%i", &squarey4.y);
    fscanf(fp, "%i", &roundx.x);
    fscanf(fp, "%i", &roundy.y);
    fscanf(fp, "%i", &radius);
    fclose(fp);

    if(myfunc() == 0)
        printf("Peresekautsa");
    if(myfunc() == 1)
        printf("NE Peresekautsa");

    return 0;
}


