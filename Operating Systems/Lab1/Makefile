CC = gcc
CFLAGS = -Wall -Wextra -Wsign-conversion -Wconversion -pedantic -std=c11

SRC_DIR = src
BUILD_DIR = build

SRCS = $(wildcard $(SRC_DIR)/*.c)
EXES = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%)

$(BUILD_DIR)/%: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

all: $(EXES)

clean:
	rm -f $(BUILD_DIR)/*
