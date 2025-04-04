# Compiler and flags
CC = gcc
CFLAGS = -Iinclude -Wall -Werror -Wextra -Wpedantic

# Directories and source files
SOURCE_DIR = source
BUILD = build
SOURCES = $(wildcard $(SOURCE_DIR)/*.c)

# Target executable
TARGET = $(BUILD)/memallocsim.exe

# Default target
all: $(TARGET)

# Create the build directory if it doesn't exist
$(BUILD):
	@if not exist $(BUILD) mkdir $(BUILD)

# Build target
$(TARGET): $(SOURCES) | $(BUILD)
	$(CC) $(CFLAGS) $^ -o $@

# Run the program after building
run: $(TARGET)
	@$(TARGET)

# Delete the build directory
clean:
	rmdir /S /Q $(BUILD)

.PHONY: all clean run