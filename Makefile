CC = clang
CFLAG = -g -O0 -Wall -Wextra
CMAKE = cmake
LABA = laba

.PHONY: all debug clean format

all: format
	$(CC) $(CFLAG) test.c -o $(LABA)

# Clean build
clean:
	rm -rf $(LABA)

# Format src files
format:
	clang-format -i laba.h test.c
