#include <stdlib.h>
#include <stdio.h>

void fprocess(const char * pread, const char * pwrite){
    FILE* fr = fopen(pread, "r");
	FILE* fw = fopen(pwrite, "w");
	char str[1000];
	for(int i = 0; i < 3; i++){
        for(int k = 0; k < 1000; k++)
            str[k] = 0;
		fgets(str, 1000, fr);
	}
	int wordsnumber = 0;
	//printf("%s\n", str);
	for(int j = 0; j < 1000; j++){
        if(str[j] == 32 && str[j + 1] != 32) wordsnumber++;
        if(str[j] == 13) break;
	}
	wordsnumber++;
	//printf("%i\n", wordsnumber);
	int n = 0;
	int wordslen[wordsnumber];
	for(int i = 0; i < wordsnumber; i++){
            wordslen[i] = 0;
            for(int j = 0 + n; j < 1000; j++){
                if(str[j] == 32 && str[j + 1] == 32){
                    n = j + 1;
                    continue;
                }
                if(str[j] == '\0'){
                    wordslen[i]--;
                    //printf("%i, ", wordslen[i]);
                    break;
                }
                if(str[j] != 32)
                    wordslen[i]++;
                if(str[j] == 32 && str[j + 1] != 32){
                    //printf("%i, ", wordslen[i]);
                    n = j + 1;
                    break;
                }
        }
	}
	//for(int i = 0; i < wordsnumber; i++)
    //    fprintf(fw, "%i, ", wordslen[i]);
	fclose(fr);
	fclose(fw);
}
