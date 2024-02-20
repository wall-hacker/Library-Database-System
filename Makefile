# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99

# define targets
TARGETS=main

build: $(TARGETS)

main: main.c ll.h ht.h struct.h commands.h
	$(CC) $(CFLAGS) main.c -o main ll.c ht.c commands.c

pack:
	zip -FSr 311CA_AndreiCalinMihail_Tema2.zip README Makefile main.c ll.c ht.c commands.c ll.h ht.h struct.h commands.h

clean:
	rm -f $(TARGETS) *.o

.PHONY: pack clean