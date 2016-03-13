CC = gcc
CFLAGS = -Wall -std=c99 -pedantic -lwiringPi

.PHONY: all clean

morsePI:
		$(CC) $(CFLAGS) -o morsePI morse.c

all: morsePI

clean:
	rm -f morsePI
