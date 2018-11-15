SRC=main.c SCHED_DEADLINE.c
BIN=main

CFLAGS=-Wall -Wno-variadic-macros -pedantic
LDLIBS=-lpthread -lrt # librt, libposix4 - POSIX.1b Realtime Extensions library

.PHONY: all
all: $(SRC)
	gcc -o $(BIN) $(SRC) $(LDLIBS)

.PHONY: clean
clean:
	rm -f *~ *.bak *.o $(PROGS)

.PHONY: rebuild
rebuild: clean all
