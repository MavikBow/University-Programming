CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c89
SRC = $(wildcard *.c)
EXECUTABLES = $(SRC:.c=.exe)

.PHONY: all clean

build:
    if [ ! -d "build" ]; then \
        mkdir build; \
    fi

all: $(EXECUTABLES)

%.exe: %.c
	$(CC) $(CFLAGS) $< -o build/$@

clean:
	rm -rf build *.exe
