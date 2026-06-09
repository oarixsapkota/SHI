CC = clang
CMAKE = cmake
LABA = laba

.PHONY: all debug clean format

all: format
	$(CC) test.c -o $(LABA)

# Clean build
clean:
	rm -rf $(LABA)

# Format src files
format:
	clang-format -i laba.h test.c
