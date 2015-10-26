#include <stdio.h>
#include <math.h>

double long2double(long long number) {

	int arr[64];
	double exp[11], man[52];
	double fract = 0, expn = 0, sign;
	int i;

	for (i = 0; i <= 63; i++) {
		arr[i] = (number & (1LL << 63 - i)) ? 1 : 0;
	}
	for (i = 0; i < 11; i++) {
		exp[i] = arr[i + 1];
	}
	for (i = 0; i < 52; i++) {
		man[i] = arr[i + 12];
	}
	sign = arr[0];
	for (i = 0; i <= 10; i++) {
		expn += exp[i] * pow(2, i);
	}
	for (i = 0; i < 52; i++) {
		fract += man[i] * pow(2, -i - 1);
	}
	if (expn == 0 && fract != 0) {
		return pow(-1, sign) * pow(2, -1022) * fract;
	}
	if (expn >0 && expn < 2047) {
		return pow(-1, sign) * pow(2, expn - 1023) * (fract + 1);
	}
	if (expn == 2047 && fract != 0) {
		return NAN;
	}
	if (expn == 2047 && fract == 0 && sign == 1) {
		return -INFINITY;
	}
	if (expn == 2047 && fract == 0 && sign == 0) {
		return INFINITY;
	}
	if (expn == 0 && fract == 0 && sign == 1) {
		return -0;
	}
	if (expn == 0 && fract == 0 && sign == 0) {
		return 0;
	}

}
