EXECUTABLES=server client

all: $(EXECUTABLES)

server:
	gcc server.c -o server

client:
	gcc client.c -o client