CC=gcc
EXECUTABLES=server client

all: $(EXECUTABLES)

server:
	$(CC) server.c -o server.out

client:
	$(CC) client.c -o client.out