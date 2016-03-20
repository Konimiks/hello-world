#ifndef MY_CALLBACK
#define MY_CALLBACK

void detect();

void printCB(char *arr, int len, void(*cb)());
void red();
void green();
void blue();

void processCB(char *arr, int len, void(*cb)());
void make_zero(char *arr, int len);
void make_one(char *arr, int len);
void make_two(char *arr, int len);


#endif // MY_CALLBACK
