CC = gcc
CFLAGS = -Wall -Wextra
SRC_DIR = src
BUILD_DIR = build

# Create build directory if it doesn't exist
$(shell mkdir -p $(BUILD_DIR))

# Main target
all: $(BUILD_DIR)/main

# Compile the program
$(BUILD_DIR)/main: $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) $< -o $@

# Run the program
run: $(BUILD_DIR)/main
	./$(BUILD_DIR)/main

# Clean compiled files
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all run clean
