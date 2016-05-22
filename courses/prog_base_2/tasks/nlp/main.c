
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "types.h"

int main(void) {
	text_t * myText = text_new();

	int fileCheck = text_addText(myText, "input.txt");
	if (fileCheck == NO_FILE) {
		printf("Cannot open file.\n");
		text_free(myText);
		return 0;
	}

	text_formListOfSent(myText);
	text_sortWordsAndWrite(myText, "output.txt");

	text_free(myText);
	return 0;
}
