#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "pcb.h"
#include "queue.h"

typedef enum {
	FCFS, //first come first serve
} SchedulingPolicy;


void scheduler_initialize();
void scheduler_set_policy(SchedulingPolicy policy);
void scheduler_add_process(PCB *pcb);
void scheduler_run(); //main scheduling loop 
int scheduler_is_running();

#endif
