#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

//initialize an empty queue
void queue_init(ReadyQueue *q) {
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
}

//add PCB to the tail of the queue
void queue_enqueue(ReadyQueue *q, PCB *pcb) {
    if (pcb == NULL) return;
    
    pcb->next = NULL;  // next is NULL
    
    if (q->tail == NULL) {
        //queue is empty
        q->head = pcb;
        q->tail = pcb;
    } else {
        //add to tail
        q->tail->next = pcb;
        q->tail = pcb;
    }
    
    q->size++;
}

// remove and return PCB from head of queue
PCB* queue_dequeue(ReadyQueue *q) {
    if (q->head == NULL) {
        return NULL;  // queue is empty
    }
    
    PCB *pcb = q->head;
    q->head = q->head->next;
    
    if (q->head == NULL) {
        // queue is now empty
        q->tail = NULL;
    }
    
    q->size--;
    pcb->next = NULL;  // disconnect from queue
    
    return pcb;
}

// look at head without removing
PCB* queue_peek(ReadyQueue *q) {
    return q->head;
}

// check if queue is empty
int queue_is_empty(ReadyQueue *q) {
    return q->head == NULL;
}

// get queue size
int queue_size(ReadyQueue *q) {
    return q->size;
}
