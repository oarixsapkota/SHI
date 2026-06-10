CC = clang
CFLAG = -g -O0 -Wall -Wextra
CMAKE = cmake
SHI = shi

.PHONY: all debug clean format

all: format
	$(CC) $(CFLAG) test.c -o $(SHI)

alaba: format
	$(CC) $(CFLAG) -x c -DLABA_IMPLEMENTATION shi_opa.h -o $(SHI)

# Clean build
clean:
	rm -rf $(SHI)

# Format src files
format:
	clang-format -i shi_opa.h test.c
