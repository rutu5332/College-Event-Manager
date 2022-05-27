
CC = gcc
CFLAGS = -lpthread
DEPS = myHeader.h
SOBJ = Server.o Admin.o User.o Functions.o
COBJ = Client.o Admin.o User.o Functions.o

all: server client

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)
	
server: $(SOBJ) 
	$(CC) -o $@ $^ $(CFLAGS)

client: $(COBJ) 
	$(CC) -o $@ $^ $(CFLAGS)


.PHONY: clean

clean: 
	rm -f server client
	