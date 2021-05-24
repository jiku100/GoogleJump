//-------| src/fnd.c |-------//
#include "fnd.h"

static unsigned short fnd_decimal[11] = {
	0x3F, // 0
	0x06, // 1
	0x5B, // 2
	0x4F, // 3
	0x66, // 4
	0x6D, // 5
	0x7D, // 6
	0x07, // 7
	0x7F, // 8
	0x67, // 9
	0x00  // blank
};

static short * fnd[MAX_FND];

void init_fnd(short * address[]) {
	int i;
	for( i=0; i<MAX_FND; i++ ) {
		fnd[i] = address[i];
	}
}

void fnd_clear() {
	int i;
	for(i=0; i<MAX_FND; i++){
		*fnd[i] = 0;
	}
}

void fnd_all() {
	int i;
	for(i=0; i<MAX_FND; i++){
		*fnd[i] = 0xFF;
	}
}

void fnd_write(int decimal, int fnd_num) {
	*fnd[fnd_num] = fnd_decimal[decimal];
}

void fnd_dec_number(unsigned long number) {
	int i;
	int write_number = 0;
	for(i=0; i<MAX_FND; i++){
		write_number = number % 10;
		fnd_write( (short)(write_number), i);
		number /= 10;
	}
}