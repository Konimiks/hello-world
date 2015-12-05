// VARIANT 14

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


int main(void)
{
    printf("Please enter your text:::");
    char string[1000];
    gets(string);
    //printf("%s", string);
    int counter = 0;
    for(int i = 0; i < 999; i++ )
    {
        if(i == 0)
        {
            if(string[i] == '\0')
                break;
        }
        if(string[i] == '.')
            counter++;
        if(string [i-1] != '.' && string[i] == '\0' )
        {
            counter++;
            break;
        }
        if(string[i] == '\0' )
        {
            break;
        }

    }
    printf("THE NUMBER OF STRINGS IS ::: %i", counter);


    return 0;
}
