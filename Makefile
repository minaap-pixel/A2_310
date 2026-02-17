CC=gcc
CFLAGS=
FMT=indent

mysh: shell.o interpreter.o shellmemory.o pcb.o queue.o scheduler.o
	$(CC) $(CFLAGS) -o mysh shell.o interpreter.o shellmemory.o pcb.o queue.o scheduler.o

shell.o: shell.c shell.h
	$(CC) $(CFLAGS) -c shell.c

interpreter.o: interpreter.c interpreter.h
	$(CC) $(CFLAGS) -c interpreter.c

shellmemory.o: shellmemory.c shellmemory.h
	$(CC) $(CFLAGS) -c shellmemory.c

pcb.o: pcb.c pcb.h
	$(CC) $(CFLAGS) -c pcb.c

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c

scheduler.o: scheduler.c scheduler.h
	$(CC) $(CFLAGS) -c scheduler.c

style: shell.c shell.h interpreter.c interpreter.h shellmemory.c shellmemory.h pcb.c pcb.h queue.c queue.h scheduler.c scheduler.h
	$(FMT) $?

clean: 
	$(RM) mysh; $(RM) *.o; $(RM) *~
