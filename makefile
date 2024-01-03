all: valhal

valhal: main.o todo.o
	@echo " - linking files - "
	gcc main.o todo.o -o valhal -lncurses

main.o: main.c
	@echo " - compiling main.c - "
	gcc -c main.c

todo.o: todo.c
	@echo " - compiling todo.c - "
	gcc -c todo.c

clean:
	@echo " - removing all files but source files - "
	rm main.o todo.o valhal
