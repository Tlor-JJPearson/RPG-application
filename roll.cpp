#include"roll.h"
#include<cstdlib>

int roll(int die) { return rand() % die + 1; }
int statRoll() {
	int sum = 0;
	int Roll[4];
	int temp = 6;
	for (int r = 0; r <= 3; r++) {
		Roll[r] = roll(6);
		sum += Roll[r];
		if (Roll[r] < temp) { temp = Roll[r]; }
	}
	return sum - temp;
}
int rollMany(int num, int die) {
	if (num <= 0) { return 0; }
	int sum = 0;
	for (int i = 0; i < num; i++) { sum += roll(die); }
	return sum;
}