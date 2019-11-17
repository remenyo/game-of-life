OBJS	= main.o menu.o file.o status.o input.o play.o
SOURCE	= main.c menu.c file.c status.c input.c play.c
HEADER	= menu.h file.h pattern.h input.h play.h debugmalloc.h
OUT	= main
CC	 = gcc
FLAGS	 = -g -c -Wall -Wextra -std=c99
LFLAGS	 = -lncurses

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.c
	$(CC) $(FLAGS) main.c

menu.o: menu.c
	$(CC) $(FLAGS) menu.c

file.o: file.c
	$(CC) $(FLAGS) file.c

status.o: status.c
	$(CC) $(FLAGS) status.c

input.o: input.c
	$(CC) $(FLAGS) input.c

clean:
	rm -f $(OBJS) $(OUT)