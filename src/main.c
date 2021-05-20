//-------| src/main.c |-------//
#include "main.h"

static off_t IEB_DOT[MAX_DOT] = {
	IEB_DOT1,
	IEB_DOT2,
	IEB_DOT3,
	IEB_DOT4,
	IEB_DOT5
};

static int fd;
static int map_counter = 0;
static void * map_data[100];

int main(int argc, char* argv[]) {
	Player* head = read_savefile();
	printPlayerList(head, stdout);
	Player* player = search_player(head, "HyunJun");
	printPlayerInfo(player);
	setStage(player, 3);
	setLife(player, 2);
	printPlayerList(head, stdout);
	write_savefile(head);
	// int i;
	// short * led, * dot[MAX_DOT];
	// short * clcd_cmd, * clcd_data;
	
	// fd = open("/dev/mem", O_RDWR|O_SYNC);
	// if (fd == -1) {
	// 	fprintf(stderr, "Cannot open /dev/mem file");
	// 	exit(EXIT_FAILURE);
	// }
	// led = mapper(IEB_LED, PROT_WRITE);
	// for( i=0; i<MAX_DOT; i++ ) {
	// 	dot[i] = mapper(IEB_DOT[i], PROT_WRITE); 
	// }
	// clcd_cmd  = mapper(IEB_CLCD_CMD, PROT_WRITE);
	// clcd_data = mapper(IEB_CLCD_DATA, PROT_WRITE); 

	// init_led(led);
	// init_dot(dot);
	// init_clcd(clcd_cmd, clcd_data);

	// init_seed();
	// gameProgress();
	// unmapper();
	// close(fd);
	return 0;
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

error_t gameProgress() {
	Queue* obstacles = init_queue();
	create_obstacles(obstacles, 10);
	write_obstacles(obstacles);
	usleep(1000000);
	int shift = 0;
	for(shift; shift < 40; shift++){
		dot_clear();
		dot_write(shift % 2);
		clcd_shift(1, 0);	
		usleep(50000);
	}
	// while(1) 
	// { 
	// 	if(kbhit()) 
	// 	{ 
	// 			// 입력된 키정보 얻기. 
	// 			key = _getch(); 
	// 			switch (key)
	// 			{
	// 			case 'w':
	// 			case 'W':
	// 				shape = 74;
	// 				break;
	// 			case 's':
	// 			case 'S':
	// 				shape = 83;

	// 			default:
	// 				break;
	// 			}
	// 	}
	// 	else{
	// 	}
	// }	
	return SUCCESS;
}

int show_obstacle(){
	int obstacle = make_obstacle();
	switch (obstacle)
	{
	case 0:
		return '.';
	case 1:
		return '@';
	case 2:
		return '#';
	default:
		break;
	}
}

void error() {
	clcd_clear_display();
	clcd_set_DDRAM(0x40);
	clcd_write_string("  !! ERROR !!");
}

truth_t inputter() {
	int input_int;
	printf("\n");
	printf("***************************************\n");
	printf("*     Please type a number            *\n");
	printf("*     1 : Display shift (left)        *\n");
	printf("*     2 : Display shift (right)       *\n");
	printf("*     3 : Display On                  *\n");
	printf("*     4 : Display Off                 *\n");
	printf("*     0 : EXIT                        *\n");
	printf("***************************************\n\n");
	scanf("%d", &input_int);
	
	switch(input_int) {
		case 1 :
			clcd_shift(1, 0);
			clcd_shift(1, 0);
			break;
		case 2 :
			clcd_shift(1, 1);
			clcd_shift(1, 1);
			break;
		case 3 :
			clcd_display_control(1, 0, 0);
			break;
		case 4 :
			clcd_display_control(0, 0, 0);
			break;
		case 0 :
			return FALSE;
		default :
			break;
	}
	return TRUE;
}