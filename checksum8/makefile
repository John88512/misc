# Simple Makefile Template for a basic C program
# Compiles main.c into executable 'program' with warnings and debug info
# Usage: make (builds), make clean (removes binary)

CC = gcc                  # Compiler to use (gcc for standard C)
CFLAGS = -Wall -g -O2     # Flags: -Wall (warnings), -g (debug), -O2 (optimization)
TARGET = test_checksum         # Name of the output executable

# Default target: build the program
all: $(TARGET)

# Rule to link object files into executable
# $^ = all prerequisites (main.c), $@ = target (program)
$(TARGET): test_checksum.c
	$(CC) $(CFLAGS) -o $@ $^

# Clean target: remove generated files
clean:
	rm -f $(TARGET)

# Declare phony targets (not files)
.PHONY: all clean
