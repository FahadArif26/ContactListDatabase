CC = gcc
CFLAGS = -ansi -Wall -I$(IDIR) -g

IDIR = ./includes/
SRCDIR = ./src/
BINDIR = ./bin/

SOURCES = $(SRCDIR)*.c

all: $(BINDIR)contactList

$(BINDIR)contactList: $(BINDIR)main.o $(BINDIR)contacts.o
	$(CC) $(BINDIR)main.o $(BINDIR)contacts.o -o $@

$(BINDIR)main.o: $(SRCDIR)main.c
	$(CC) $(CFLAGS) -c $(SRCDIR)main.c -o $@

$(BINDIR)contacts.o: $(SRCDIR)contacts.c
	$(CC) $(CFLAGS) -c $(SRCDIR)contacts.c -o $@

run:
	./contactList

clean:
	rm $(BINDIR)*.o ./bin/contactList $(BINDIR)*.db
