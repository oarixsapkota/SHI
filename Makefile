CC = clang
CFLAG = -g -O0 -Wall -Wextra
BUILD = build

HEADERS = $(wildcard *.h)
TESTS = $(patsubst %.h, $(BUILD)/test_%, $(HEADERS))

.PHONY: all debug clean format

all: prepare $(TESTS)

# Ensure build directory exists
prepare:
	mkdir -p $(BUILD)

# Build a test for headers
$(BUILD)/test_%: %.h
	$(CC) $(CFLAG) -x c -DSHI_OPA_TEST $< -o $@

# Clean build
clean:
	rm -rf $(BUILD)

# Format all header files
format:
	clang-format -i $(HEADERS)
