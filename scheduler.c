#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scheduler.h"
#include "shellmemory.h"
#include "shell.h"

//scheduler state
static ReadyQueue ready_queue;
static SchedulingPolicy current_policy = FCFS;
static int next_pid = 1;
static int is_running = 0;

// initialize the scheduler
void scheduler_initialize() {
    queue_init(&ready_queue);
    next_pid = 1;
    is_running = 0;
}

// set scheduling policy
void scheduler_set_policy(SchedulingPolicy policy) {
    current_policy = policy;
}

// add process to the ready queue
void scheduler_add_process(PCB *pcb) {
    if (pcb == NULL) return;
    
    // assign unique PID
    if (pcb->pid == 0) {
        pcb->pid = next_pid++;
    }
    
    queue_enqueue(&ready_queue, pcb);
}

// check if scheduler is running
int scheduler_is_running() {
    return is_running;
}

// main scheduler loop - FCFS policy
void scheduler_run() {
    is_running = 1;
    
    while (!queue_is_empty(&ready_queue)) {
        //get the process at the head (FCFS)
        PCB *current_process = queue_dequeue(&ready_queue);
        
        if (current_process == NULL) {
            break;
        }
        
        //one instruction
        char *instruction = mem_get_code_line(current_process->pc);
        
        if (instruction != NULL) {
            // parse and execute the instruction
            parseInput(instruction);
            
            //next instruction
            current_process->pc++;
            
            //check if process is done
            if (current_process->pc > current_process->end) {
                // clean up if done
                mem_free_code(current_process->start, current_process->end);
                pcb_destroy(current_process);
            } else {
                // process not done - put back in queue (FCFS runs to completion)
                // keep executing until done
                queue_enqueue(&ready_queue, current_process);
            }
        } else {
            // no instruction - process is done
            mem_free_code(current_process->start, current_process->end);
            pcb_destroy(current_process);
        }
    }
    
    is_running = 0;
}
