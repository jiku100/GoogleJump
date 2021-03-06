//-------| src/main.c |-------//
#include "main.h"

static off_t IEB_DOT[MAX_DOT] = {
	IEB_DOT1,
	IEB_DOT2,
	IEB_DOT3,
	IEB_DOT4,
	IEB_DOT5
};

static off_t IEB_FND[MAX_FND] = {
	IEB_FND0,
	IEB_FND1,
	IEB_FND2,
	IEB_FND3,
	IEB_FND4,
	IEB_FND5,
	IEB_FND6,
	IEB_FND7
};

static int fd;
static int map_counter = 0;
static void * map_data[100];

int main(int argc, char* argv[]) {
	if(argc != 2){	// 이름이 입력이 안되면 프로그램 종료
		fprintf(stderr, "Please Input Your Name!!");
		return 0;
	}
	else{
		int i;
		short * led, * dot[MAX_DOT], * fnd[MAX_FND];
		short * clcd_cmd, * clcd_data;
		
		fd = open("/dev/mem", O_RDWR|O_SYNC);
		if (fd == -1) {
			fprintf(stderr, "Cannot open /dev/mem file");
			exit(EXIT_FAILURE);
		}
		led = mapper(IEB_LED, PROT_WRITE);
		for( i=0; i<MAX_DOT; i++ ) {
			dot[i] = mapper(IEB_DOT[i], PROT_WRITE); 
		}
		for( i=0; i<MAX_FND; i++ ) {
			fnd[i] = mapper(IEB_FND[i], PROT_WRITE);
		}
		clcd_cmd  = mapper(IEB_CLCD_CMD, PROT_WRITE);
		clcd_data = mapper(IEB_CLCD_DATA, PROT_WRITE); 

		init_led(led);
		init_dot(dot);
		init_clcd(clcd_cmd, clcd_data);
		init_fnd(fnd);
		init_seed();
		mainGame(argv[1]);	// 이름에 해당하는 부분을 argument로 넘김
		unmapper();
		close(fd);
		return 0;
	}
}

short * mapper(off_t offset, int prot) {
	map_data[map_counter] = mmap(NULL, sizeof(short), prot, MAP_SHARED, fd, offset);
	if ( map_data[map_counter] == MAP_FAILED ) {
		fprintf(stderr, "Cannot do mmap()");
		emergency_closer();
	}
	return (short *)map_data[map_counter++];
}

void unmapper() {
	int i;
	for( i=0; i<map_counter; i++) {
		munmap(map_data[i], sizeof(short));
	}
	map_counter = 0;
}

void emergency_closer() {
	unmapper();
	close(fd);
	exit(EXIT_FAILURE);
}

void error() {
	clcd_clear_display();
	clcd_set_DDRAM(0x40);
	clcd_write_string("  !! ERROR !!");
}