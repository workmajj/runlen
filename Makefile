CC = clang
CFLAGS = -Wall -g

all: clean rungen runlen

rungen:
	$(CC) $(CFLAGS) -o rungen rungen.c

runlen:
	$(CC) $(CFLAGS) -o runlen runlen.c

clean:
	rm -f rungen
	rm -rf rungen.dSYM
	rm -f runlen
	rm -rf runlen.dSYM

.PHONY: clean
