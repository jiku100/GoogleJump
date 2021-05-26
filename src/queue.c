#include "queue.h"

Queue* init_queue(void){
	Queue* q = (Queue*)malloc(sizeof(Queue));
	q->front = q->rear = 0;
	q->size = 0;
}

boolean isEmptyQueue(Queue* q){
	if(q->size == 0)
		return 1;
	else
		return 0;
}

boolean isFullQueue(Queue* q){
	if(q->size == MAX_SIZE - 1)
		return 1;
	else
		return 0;
}

void enqueue(Queue* q, int data){
	if(isFullQueue(q)){
		printf("Queue is full \n");
	}
	else{
		q->rear = (q->rear + 1) % MAX_SIZE;	// 원형 큐의 enqueue 방식
		q->data[q->rear] = data;
		q->size++;
	}
}

int dequeue(Queue* q){
	if(isEmptyQueue(q)){
		printf("Queue is Empty \n");
		exit(1);
	}
	else{
		q->front = (q->front + 1) % MAX_SIZE;
		q->size--;
		return q->data[q->front];
	}
}

int getSize(Queue* q){
	return q->size;
}

void printQueue(Queue* q){
	if(isEmptyQueue(q)){
		printf("Queue is Empty \n");
		exit(1);
	}
	else{
		int i = q->front;
		printf("Queue: ");
		do
		{
			i = (i + 1) % MAX_SIZE;
			printf("%d ", q->data[i]);
			if(i == q->rear)
				break;
		} while (i != q->front);
		printf("\n");
	}
}

void clearQueue(Queue* q){
	free(q);
	q = init_queue();
}