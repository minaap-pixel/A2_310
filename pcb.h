#ifndef PCB_H
#define PCB_H

typedef struct PCB {
	int pid; //process id
	int pc; //program counter
	int start; //start position in shell memory
	int end; //end position in shell memory
	int job_length_score; //for SJF scheduling
	struct PCB *next; //queue linking
} PCB;

//pcb management (creation and destruction)
PCB* pcb_create(int pid, int start, int end);
void pcb_destroy(PCB *pcb);

#endif
