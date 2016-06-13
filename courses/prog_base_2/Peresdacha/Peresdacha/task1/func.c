#include "func.h"

//to find str1 in str2
//return 0 if find
//else return -1
int mystrstr(const char * str1, const char * str2){
    if(strlen(str1) > strlen(str2))
        return -1;
    int statusOfBegin = -1;
    int length = 0;
    for(int i = 0; i < strlen(str2); i++){
        if(str2[i] == '\n')
            continue;
        if(str1[length] == str2[i] && statusOfBegin == -1){
            if(length == strlen(str1) - 1){
                return 0;
            }
        else
        {
            statusOfBegin = 0;
            length++;
        }
        }
        else if(str1[length] == str2[i] && statusOfBegin == 0){
            if(length == strlen(str1) - 1){
                return 0;
            }
            else {
                length++;
            }
        }
        else if(str1[length] != str2[i]){
            statusOfBegin = -1;
            length = 0;
        }
    }
    return -1;
}
