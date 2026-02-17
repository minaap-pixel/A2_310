#ifndef QUEUE_H
#define QUEUE_H
#include "pcb.h"

typedef struct {
	PCB *head;
	PCB *tail;
	int size;
} ReadyQueue;

void queue_init(ReadyQueue *q);
void queue_enqueue(ReadyQueue *q, PCB *pcb);
PCB *queue_dequeue(ReadyQueue *q);
int queue_is_empty(ReadyQueue *q);
PCB* queue_peek(ReadyQueue *q);
int queue_is_empty(ReadyQueue *q);
int queue_size(ReadyQueue *q);

#endif
