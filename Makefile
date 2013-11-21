CC = gcc -g
OBJECTS = main.o \
	file_io.o \
	functions.o \
	linked_list_function.o 

all: BEGIN $(OBJECTS)
	@$(CC) -o main $(OBJECTS)
	@echo Compilation is done.

BEGIN:
	@echo Compilation will start soon..

main.o : main.c
	@$(CC) -c main.c

functions.o : functions.c
	@$(CC) -c functions.c

file_io.o : file_io.c
	@$(CC) -c file_io.c

linked_list_function.o : linked_list_function.c
	@$(CC) -c linked_list_function.c

clean :
	@rm -rf $(OBJECTS)
