#include <stdlib.h>
#include <stdio.h>
#include "pcb.h"

PCB* pcb_create(int pid, int start, int end) {
	PCB *pcb = (PCB*)malloc(sizeof(PCB));
	//if pcb is null, return nothing
	if (pcb == NULL) {
		return NULL;
	}

	pcb->pid = pid;
	pcb->pc = start; //execute from first line
	pcb->start = start;
	pcb->end = end;
	pcb->job_elngth_score = end - start + 1;
	pcb->next = NULL;

	return pcb;
}

void pcb_destroy(PCB *pcb) {
	if (pcb != NULL) {
		free(pcb); //clean up PCB
	}
}

