CC			= gcc
CFLAGS		= $(INCLUDE) -std=c99 -Wall -O3

SOURCES		= $(wildcard *.c)
OBJECTS		= $(SOURCES:.c=.o)
INCLUDE		= -I.

all: main

.c.o:
	$(CC) $(CFLAGS) $< -c -o $@

build: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o main

main: build
	./main

debug: CFLAGS += -DDEBUG
debug: main

.PHONY: clean

clean:
	rm -f $(OBJECTS) main
