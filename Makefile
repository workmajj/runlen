CC = clang
CFLAGS = -MD -Wall -Werror -std=c99

.PHONY: all
all: rungen runlen

.PHONY: clean
clean:
	rm -f rungen runlen
	rm -f ./*.o ./*.d
