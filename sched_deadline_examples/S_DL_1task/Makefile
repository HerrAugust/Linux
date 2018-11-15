PROGS=main

CFLAGS=-Wall -Wno-variadic-macros -pedantic
LDLIBS=-lrt # librt, libposix4 - POSIX.1b Realtime Extensions library

.PHONY: all
all: $(PROGS)

.PHONY: clean
clean:
	rm -f *~ *.bak *.o $(PROGS)
