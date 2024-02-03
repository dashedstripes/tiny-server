EXECUTABLES=server client

all: $(EXECUTABLES)

server:
	gcc server.c -o server.out

client:
	gcc client.c -o client.out