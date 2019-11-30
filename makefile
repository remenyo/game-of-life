OBJS	= main.o menu.o file.o pattern.o status.o input.o play.o edit.o
SOURCE	= main.c menu.c file.c pattern.c status.c input.c play.c edit.c
HEADER	= menu.h file.h pattern.h input.h play.h edit.h debugmalloc.h
OUT	= debug
CC	 = gcc
FLAGS	 = -g3 -c -Wall -Wextra -std=c99
LFLAGS	 = -lncurses

all: $(OBJS)
	$(CC) $(OBJS) -o $(OUT) $(LFLAGS)

release:
	gcc -Wall -Wextra -v -std=c99 -o release *.c $(LFLAGS)
	# windows : x86_64-w64-mingw32-gcc -v -Wall -Wextra -std=c99 -o release.exe *.c -L./ -lpdcurses

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

play.o: play.c
	$(CC) $(FLAGS) play.c

pattern.o: pattern.c
	$(CC) $(FLAGS) pattern.c

edit.o: edit.c
	$(CC) $(FLAGS) edit.c

clean:
	rm -f $(OBJS) $(OUT) release release.exe