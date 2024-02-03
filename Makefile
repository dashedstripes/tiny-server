CC=gcc
EXECUTABLES=server client
OUT_DIR=bin

all: $(EXECUTABLES)

server:
	$(CC) server.c -o $(OUT_DIR)/server.out

client:
	$(CC) client.c -o $(OUT_DIR)/client.out
