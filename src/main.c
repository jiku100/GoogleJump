//-------| src/main.c |-------//
#include "main.h"


static int fd;
static int map_counter = 0;
static void * map_data[100];

int main(int argc, char* argv[]) {
	
	short * clcd_cmd, * clcd_data;
	
	fd = open("/dev/mem", O_RDWR|O_SYNC);
	if (fd == -1) {
		fprintf(stderr, "Cannot open /dev/mem file");
		exit(EXIT_FAILURE);
	}
	clcd_cmd  = mapper(IEB_CLCD_CMD);
	clcd_data = mapper(IEB_CLCD_DATA);

	init_clcd(clcd_cmd, clcd_data);
	
	init_seed();
	gameProgress();
	
	unmapper();
	close(fd);
	return 0;
}

short * mapper(off_t offset) {
	map_data[map_counter] = mmap(NULL, sizeof(short), PROT_WRITE, MAP_SHARED, fd, offset);
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
	for(int i = 0; i<15;i++){
		enqueue(obstacles, '.');
	}

	clcd_entry_mode_set(1, 0);
	clcd_set_DDRAM(0x00);
	clcd_write_data('R');
	clcd_set_DDRAM( 0x40 );
	clcd_write_data('R');
	int key;
	int shape = 82; 
	while(1) 
	{ 
		// 아무키나 눌렸다면 출력 후 종료. 
		if(kbhit()) 
		{ 
				// 입력된 키정보 얻기. 
				key = _getch(); 
				switch (key)
				{
				case 'w':
				case 'W':
					shape = 74;
					break;
				case 's':
				case 'S':
					shape = 83;

				default:
					break;
				}
		}
		else{
			dequeue(obstacles);
			enqueue(obstacles, show_obstacle());
			int i = obstacles->front;
			int cmd = 0;

			switch (shape)
			{
			case 82:
				clcd_set_DDRAM(0x00);
				clcd_write_data('R');
				clcd_set_DDRAM( 0x40 );
				clcd_write_data('R');
				break;
			case 74:
				clcd_set_DDRAM(0x00);
				clcd_write_data('J');
				clcd_set_DDRAM( 0x40 );
				clcd_write_data(' ');
				break;
			case 83:
				clcd_set_DDRAM(0x00);
				clcd_write_data(' ');
				clcd_set_DDRAM( 0x40 );
				clcd_write_data('S');
				break;
			default:
				break;
			}
			
			do
			{
				i = (i + 1) % MAX_SIZE;
				int c = obstacles->data[i];
				if(c == '#'){
					clcd_write_data(' ');
					clcd_set_DDRAM(0x01 + cmd);
					clcd_write_data(c);
					clcd_set_DDRAM(0x41 + cmd + 1);
				}
				else{
					clcd_set_DDRAM(0x01 + cmd);
					clcd_write_data(' ');
					clcd_set_DDRAM(0x41 + cmd);
					clcd_write_data(c);
				}
				if(i == obstacles->rear)
					break;
				cmd++;
			} while (i != obstacles->front);
			shape = 82;
			usleep(100000);
		}
	}		
	return SUCCESS;
}

int show_obstacle(){
	int obstacle = create_obstacle();
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