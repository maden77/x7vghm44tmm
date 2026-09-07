CC = gcc
CFLAGS = -Wall -O2 -I./lib
LDFLAGS = -lfio -lpthread -lm

all: server

server: main.c
	$(CC) $(CFLAGS) -o server main.c $(LDFLAGS)

clean:
	rm -f server
