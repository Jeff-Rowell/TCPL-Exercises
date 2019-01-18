FILES = calc

CC = gcc
CFLAGS = -g

all: $(FILES)

calc: main.o getop.o getch.o stack.o 
	$(CC) -o calc main.o getop.o getch.o stack.o
	make clean

main.o: main.c calc.h

getop.o: getop.c calc.h

getch.o: getch.c calc.h

stack.o: stack.c calc.h

clean:
	rm -f *.o
