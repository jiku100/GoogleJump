#ifndef QUEUE_H
#define QUEUE_H

#include <stdlib.h>
#include <stdio.h>
#include "random.h"

#define MAX_SIZE 41

typedef int boolean;

typedef struct circleQueue{
	int front;
	int rear;
	int size;
	int data[MAX_SIZE];
} Queue;

Queue* init_queue(void);	// init Queue
boolean isEmptyQueue(Queue* q);	// check Queue is Empty
boolean isFullQueue(Queue* q);	// check Queue is Full
void enqueue(Queue* q, int data);
int dequeue(Queue* q);
int getSize(Queue* q);		// Get Queue size
void printQueue(Queue* q);	// Print Queue data
void clearQueue(Queue* q);	// Clear Queue
#endif

