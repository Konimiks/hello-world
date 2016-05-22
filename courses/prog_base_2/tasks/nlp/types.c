#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"

struct word_s {
	char word[50];
	int length;
};

typedef struct word_s word_t;

struct sent_s {
	list_t * wordList;
};

struct text_s {
	char text[100000];
	list_t * sentList;
};

static int file_length(const char * frName) {
	int newLine;
	int linesAmount = 0;
	FILE * frPtr = fopen(frName, "r");
	if (frPtr == NULL) {
		return NO_FILE;
	}
	do {
		newLine = fgetc(frPtr);
		if (newLine == '\n') {
			linesAmount++;
		}
	} while (newLine != EOF);
	fclose(frPtr);
	return linesAmount;
}

static word_t * word_new(void) {
	word_t * wordSmp = malloc(sizeof(struct word_s));
	return wordSmp;
}

static void word_free(word_t * self) {
	free(self);
}

sent_t * sent_new(void) {
	sent_t * sentSmp = malloc(sizeof(struct sent_s));
	sentSmp->wordList = list_new();
	return sentSmp;
}

void sent_free(sent_t * self) {
	int wordAmount = list_getSize(self->wordList);
	for (int i = 0; i < wordAmount; i++) {
		word_free((word_t *)list_pop_back(self->wordList));
	}
	list_free(self->wordList);
	free(self);
}

text_t * text_new(void) {
	text_t * textSmp = malloc(sizeof(struct text_s));
	textSmp->sentList = list_new();
	return textSmp;
}

void text_free(text_t * self) {
	int sentAmount = list_getSize(self->sentList);
	for (int i = 0; i < sentAmount; i++) {
		sent_free((sent_t *)list_pop_back(self->sentList));
	}
	list_free(self->sentList);
	free(self);
}

int text_addText(text_t * self, const char * frName) {
	FILE * frPtr = fopen(frName, "r");
	if (frPtr == NULL) {
		return NO_FILE;
	}
	char buff[100000];
	int fileLength = file_length(frName);
	if (fileLength == NO_FILE) {
		return NO_FILE;
	}
	strcpy(self->text, "");
	for (int i = 0; i < fileLength; i++) {
		fgets(buff, 1000000, frPtr);
		strcat(self->text, buff);
	}
	fclose(frPtr);
	return SUCCESS;
}

static void sent_formListOfWords(sent_t * self, char * sent) {
	char buff[10000];
	strcpy(buff, sent);
	char * token = strtok(buff, "\',-!?/();: \"\\");
	while (token != NULL) {
		word_t * newWord = word_new();
		strcpy(newWord->word, token);
		newWord->length = strlen(newWord->word);
		list_push_back(self->wordList, newWord);
		token = strtok(NULL, ",-!?/();: \"\\");
	}
}

void text_formListOfSent(text_t * self) {
	char buff[100000];
	strcpy(buff, self->text);
	char * token = strtok(buff, ".\n");
	char ** sentences = NULL;
	int sentNumber = 0;
	while (token != NULL) {
		sentences = realloc(sentences, (sentNumber + 1)*sizeof(char *));
		sentences[sentNumber] = calloc(1000, sizeof(char));
		strcpy(sentences[sentNumber], token);

		sentNumber++;
		token = strtok(NULL, ".\n");
	}
	for (int i = 0; i < sentNumber; i++) {
		sent_t * newSent = sent_new();
		sent_formListOfWords(newSent, sentences[i]);
		list_push_back(self->sentList, newSent);
		free(sentences[i]);
	}
	free(sentences);
}

void text_sortWordsAndWrite(text_t * self, const char * fwName) {
    text_t * text = text_new();
    text_t * text2 = text_new();
	int sentAmount = list_getSize(self->sentList);
	for (int i = 0; i < sentAmount; i++) {
		sent_t * sent = (sent_t *)list_get(self->sentList, i);
        sent = sent_sort(sent);
        list_push_back(text->sentList, (void*) sent);
	}
	for ( int i = 0; i < sentAmount; i++)
        list_push_back(text2->sentList, (void *) list_pop_back(text->sentList));
	file_writeWordsToFile(text2, fwName);
	return ;
}

sent_t * sent_sort(sent_t * self){
    int wcount = list_getSize(self->wordList);
    sent_t * copy = sent_new();
    word_t * words[wcount];
    for(int i = 0; i < wcount; i++){
        words[i] = word_new();
        words[i] = (word_t *)list_pop_back(self->wordList);
    }
    int minindex = 0;
    word_t * minword = word_new();
    word_t * tmp = word_new();
    for(int j = 0; j < wcount - 1; j++){
        minindex = j;
        minword = words[j];
        for(int i = j + 1; i < wcount; i++){
            tmp = words[i];
            if(strcmp(tmp->word, minword->word) < 0){
                minword = tmp;
                minindex = i;
                continue;
            }
            else continue;
        }
        if(minindex != j){
            tmp = words[j];
            words[j] = words[minindex];
            words[minindex] = tmp;
        }
    }
    for(int i = wcount - 1; i >= 0; i--){
        list_push_back(copy->wordList, (void*)words[i]);
    }
    return copy;
}

int file_writeWordsToFile(text_t * self, const char * fwName) {
	FILE * fwPtr = fopen(fwName, "w");
	if (fwPtr == NULL) {
		return NO_FILE;
	}
	int sentAmount = list_getSize(self->sentList);
	sent_t * curSent;
	word_t * curWord;
	for(int k = 0; k < sentAmount; k++){
        curSent = (sent_t *)list_pop_back(self->sentList);
        int wordsAmount = list_getSize(curSent->wordList);
        for (int i = 0; i < wordsAmount; i++) {
            curWord = (word_t *)list_pop_back(curSent->wordList);
            fprintf(fwPtr, "%s, ", curWord->word);
        }
        fprintf(fwPtr, "\n");
	}
	word_free(curWord);
	fclose(fwPtr);
	return SUCCESS;
}
