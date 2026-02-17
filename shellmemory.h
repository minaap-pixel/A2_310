#define MEM_SIZE 1000
void mem_init();
char *mem_get_value(char *var);
void mem_set_value(char *var, char *value);

#define FRAME_STORE_SIZE 1000

void mem_init_code();
int mem_load_code(char *filename, int *start, int *end);
char* mem_get_code_line(int index);
void mem_free_code(int start, int end);
