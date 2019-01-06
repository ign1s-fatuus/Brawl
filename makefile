CC = gcc
CFLAGS = -lm -lncursesw -I$(IDIR)


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
