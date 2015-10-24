#include <stdio.h>
#include <stdlib.h>


void fillRand(int mat[4][4]){
    int i,j;
    for (i=0; i<4; i++)
        for (j=0; j<4; j++)
            mat [i][j] = rand() % 1999-999 ;
}

void rotateCCW90(int mat[4][4]){
    int i,j;
    int mat2 [4][4];
    for(i=0; i<4; i++)
        for(j=0;j<4;j++)
            mat2[i][j]=mat[i][j];
    for(i=0; i<4; i++)
        for(j=0;j<4;j++)
            mat[i][j]=mat2[j][3-i];
}


void flipH(int mat[4][4]) {
 int i,j;
 int mat2 [4][4];
 for(i=0; i<4; i++)
        for(j=0;j<4;j++)
            mat2[i][j]=mat[i][j];
    for(i=0; i<4; i++)
        for(j=0;j<4;j++)
            mat[i][j]=mat2[j][i];
}


void transposSide(int mat[4][4]){
 int i,j;
 int mat2 [4][4];
 for(i=0; i<4; i++)
        for(j=0;j<4;j++)
            mat2[i][j]=mat[i][j];
    for(i=0; i<4; i++)
        for(j=0;j<4;j++)
            mat[i][j]=mat2[3-j][3-i];
}
