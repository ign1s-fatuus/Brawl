CC = gcc
CFLAGS = -lm -lncurses -I$(IDIR)


IDIR = ./include/
SRCDIR = ./src/

SOURCES = $(SRCDIR)*.c

all: clean brawl run 

brawl: 
	$(CC) $(SOURCES) $(CFLAGS) -o $@

run:
	./brawl

clean:
	rm brawl
