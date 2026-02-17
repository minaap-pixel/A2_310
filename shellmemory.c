#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "shellmemory.h"

struct memory_struct {
    char *var;
    char *value;
};

struct memory_struct shellmemory[MEM_SIZE];

// program ocde storage
char *program_store[FRAME_STORE_SIZE];
int program_store_initialized = 0;

// Helper functions
int match(char *model, char *var) {
    int i, len = strlen(var), matchCount = 0;
    for (i = 0; i < len; i++) {
        if (model[i] == var[i])
            matchCount++;
    }
    if (matchCount == len) {
        return 1;
    } else
        return 0;
}


// Shell memory functions

void mem_init() {
    
	mem_init_code();
	int i;
    for (i = 0; i < MEM_SIZE; i++) {
        shellmemory[i].var = "none";
        shellmemory[i].value = "none";
    }
}

// Set key value pair
void mem_set_value(char *var_in, char *value_in) {
    int i;

    for (i = 0; i < MEM_SIZE; i++) {
        if (strcmp(shellmemory[i].var, var_in) == 0) {
            shellmemory[i].value = strdup(value_in);
            return;
        }
    }

    //Value does not exist, need to find a free spot.
    for (i = 0; i < MEM_SIZE; i++) {
        if (strcmp(shellmemory[i].var, "none") == 0) {
            shellmemory[i].var = strdup(var_in);
            shellmemory[i].value = strdup(value_in);
            return;
        }
    }

    return;
}

//get value based on input key
char *mem_get_value(char *var_in) {
    int i;

    for (i = 0; i < MEM_SIZE; i++) {
        if (strcmp(shellmemory[i].var, var_in) == 0) {
            return strdup(shellmemory[i].value);
        }
    }
    return NULL;
}
// initialize program memory
void mem_init_code() {
    if (program_store_initialized) return;

    for (int i = 0; i < FRAME_STORE_SIZE; i++) {
        program_store[i] = NULL;
    }
    program_store_initialized = 1;
}

// load script file into memory
int mem_load_code(char *filename, int *start, int *end) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        return -1;
    }

    // find first free spot
    int first_free = -1;
    for (int i = 0; i < FRAME_STORE_SIZE; i++) {
        if (program_store[i] == NULL) {
            first_free = i;
            break;
        }
    }

    if (first_free == -1) {
        fclose(file);
        return -1;  // no space convention
    }

    *start = first_free;
    int current = first_free;
    char line[100];

    // read file line by line
    while (fgets(line, sizeof(line), file) != NULL && current < FRAME_STORE_SIZE) {
        // remove newline
        line[strcspn(line, "\n")] = 0;

        // store the line
        program_store[current] = strdup(line);
        current++;
    }

    *end = current - 1;
    fclose(file);

    return 0;  // good
}

// get a code line at index
char* mem_get_code_line(int index) {
    if (index < 0 || index >= FRAME_STORE_SIZE) {
        return NULL;
    }
    return program_store[index];
}

// free code lines from start to end
void mem_free_code(int start, int end) {
    for (int i = start; i <= end && i < FRAME_STORE_SIZE; i++) {
        if (program_store[i] != NULL) {
            free(program_store[i]);
            program_store[i] = NULL;
        }
    }
}
