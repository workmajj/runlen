CC = clang
CFLAGS = -MD -Wall -Werror -std=c99

all: rungen runlen

.PHONY: clean
clean:
	rm -f rungen
	rm -f runlen
	rm -f ./*.o ./*.d
