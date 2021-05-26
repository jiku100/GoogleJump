#include "save.h"

/* savefile로부터 Player info 읽어오는 함수 */
Player* read_savefile(){
    char* originalSaveFilePath = "./savefile/savefile.txt"; // 저장된 savefile 위치
    FILE* in;
    makeSaveDir();  // savefile directory가 존재하지 않는다면 폴더 생성
    if((in = fopen(originalSaveFilePath, "r")) == NULL){    // savefile을 read 모드로 파일을 연다.
        // 파일이 존재하지 않는다면 NULL 반환       
        return NULL;
    }
    // 파일이 존재한 경우
    Player* head = NULL;
    char line[60];
    char name[20];
    int stage, score;

    fgets(line, 60, in);    // 처음 설명 string 읽기
    fgets(line, 60, in);    // 그 다음부터 읽기
    while (!feof(in)) {
		sscanf(line, "%17s%3d%13d", name, &stage, &score);  // 일정 형식 대로 file로부터 읽어 각각 name, stafge, score에 저장
		head = append(head, create_node(name, stage, score));   // head에 node 추가
        fgets(line, 60, in);    // 다음 줄 읽기
	}
    return head;
}

/* savefile을 쓰는 함수 */
error_t write_savefile(Player* head){   
    char* tempSaveFilePath = "./savefile/tmp.txt";  // 임시 savefile 위치
    FILE* out;

    if((out = fopen(tempSaveFilePath, "w")) == NULL){   // 임시 savefile을 write 모드로 열기
        printf("Can't open %s file\n", tempSaveFilePath);
        exit(1);
    }
	fprintf(out, "%7s%15s%14s\n", "Name", "Stage", "Score");    // 먼저 category 줄 출력
    printPlayerList(head, out); // out stream에 head Linked List 출력
    fclose(out);
    system("mv ./savefile/tmp.txt ./savefile/savefile.txt");    // 임시 savefile을 원래 savefile로 덮어 씌우기
}

/* savefile로부터 플레이어를 찾는 함수 */
Player* search_player(Player* head, char name[]){
    if (head == NULL) { // 읽어온 Player가 없다면
	    head = append(head, create_node(name, 0, 0)); // 새로 만들어 head를 return
        return head;
	}
	else {  // 읽어온 Player가 존재한다면
        do
        {
            if(strcmp(head->name, name) == 0){  // 이름을 비교해 일치하면 해당 node 반환
                return head;
            }
            if(head->next == NULL){ // 만약 끝까지 검사해도 node가 존재하지 않는다면 새로 만들어서 반환
                head = append(head, create_node(name, 0, 0));
                head = head->next;
                return head;
            }
            else{
                head = head->next;
            }
        } while (head != NULL);
	}
}

/* Save directory 존재 확인 여부 검사 및 생성 함수 */
void makeSaveDir(){
    int r = 0;
    r = access("./savefile", F_OK); // r에 현재 파일/디렉토리 상태 저장
    if(r<0){    // r < 0의 의미는 현재 해당 디렉토리가 존재하지 않는다는 의미
        system("mkdir savefile");   // 디렉토리 생성
    }
}