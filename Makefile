# --- Configuration ---
CC      := clang
CFLAGS  := -g -O0 -Wall -Wextra
BUILD   := build

HEADERS := $(wildcard *.h)
TESTS   := $(patsubst %.h, $(BUILD)/%, $(HEADERS))

.PHONY: all clean format prepare

all: prepare format $(TESTS)

prepare: | $(BUILD)

$(BUILD):
	@mkdir -p $@

$(BUILD)/%: %.h
	@echo "Compiling $< -> $@"
	@$(CC) $(CFLAGS) -x c -DSHI_TEST $< -o $@

# Clean build
clean:
	@echo "Cleaning build artifacts..."
	@rm -rf $(BUILD)

# Format all header files
format:
	@echo "Formatting headers..."
	@clang-format -i $(HEADERS)
