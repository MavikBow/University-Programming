CC = gcc
CFLAGS = -Wall -Wextra -Wsign-conversion -Wconversion -pedantic -std=c11
SRC = $(wildcard *.c)
EXECUTABLES = $(SRC:.c=.exe)

.PHONY: all clean

all: $(EXECUTABLES)

%.exe: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf build *.exe
