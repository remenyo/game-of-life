OBJS	= main.o menu.o
SOURCE	= main.c menu.c
HEADER	= menu.h
OUT	= main
CC	 = gcc
FLAGS	 = -g -c -Wall -Wextra
LFLAGS	 = -lncursesw


all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)


# create/compile the individual files >>separately<<
main.o: main.c
	$(CC) $(FLAGS) main.c -std=c99

menu.o: menu.c
	$(CC) $(FLAGS) menu.c -std=c99


# clean house
clean:
	rm -f $(OBJS) $(OUT)