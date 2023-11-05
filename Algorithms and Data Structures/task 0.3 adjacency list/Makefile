CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c89
SRC = $(wildcard *.c)
EXECUTABLES = $(SRC:.c=.exe)

.PHONY: all clean

all: $(EXECUTABLES)

%.exe: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf build *.exe
