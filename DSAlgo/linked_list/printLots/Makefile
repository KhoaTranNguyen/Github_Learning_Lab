# Compiler
CC = gcc

# Compiler flags
CFLAGS = -Wall -Wextra -g

# Source files
SRC = printLots.c

# Output executable name
TARGET = student

# Default target
all: $(TARGET)

# Rule to build the target
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

# Rule to run the program
run: $(TARGET)
	./$(TARGET)

# Rule to clean up generated files
clean:
	rm -f $(TARGET)

# Phony targets
.PHONY: all run clean