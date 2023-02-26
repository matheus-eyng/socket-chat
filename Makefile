CC=gcc
CFLAGS=-O2 -Wall
CLIBS=-pthread
SRC=src

all: server

# Link libraries
server: server.o client.o
	$(CC) $(CFLAGS) $(CLIBS) server.o -o server.out
	$(CC) $(CFLAGS) $(CLIBS) client.o -o client.out
	
# Compile but don't link
server.o: $(SRC)/server.c
	$(CC) $(CFLAGS) -c $(SRC)/server.c
	#
# Compile but don't link
client.o: $(SRC)/client.c
	$(CC) $(CFLAGS) -c $(SRC)/client.c
	
# PHONY denotes a label, ignoring files of the same name
.PHONY: clean
clean:
	rm -f *.o *.out