CC = gcc
CFLAGS = -Wall -Wextra
SRC_DIR = src
BUILD_DIR = build

# Create build directory if it doesn't exist
$(shell mkdir -p $(BUILD_DIR))

# Main target
all: $(BUILD_DIR)/ohsh

# Compile the program
$(BUILD_DIR)/ohsh: $(SRC_DIR)/main.c
	$(CC) $(CFLAGS) $< -o $@

# Run the program
run: $(BUILD_DIR)/ohsh
	./$(BUILD_DIR)/ohsh

# Clean compiled files
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all run clean
