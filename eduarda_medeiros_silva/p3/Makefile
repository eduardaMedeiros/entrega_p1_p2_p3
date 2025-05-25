CC = gcc
CFLAGS = -Wall -Wextra -O2

all: bfc bfe

bfc: bfc.c
	$(CC) $(CFLAGS) -o bfc bfc.c

bfe: bfe.c
	$(CC) $(CFLAGS) -o bfe bfe.c

clean:
	rm -f bfc bfe

.PHONY: all clean
