CC      = cc
CFLAGS  = -Wall -Wextra
LDFLAGS =
SRC     = src/rands.c

all: rands

o: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -c

rands: o
	$(CC) $(LDFLAGS) *.o -o rands

install: rands
	cp rands /usr/local/bin/rands

uninstall:
	rm -f /usr/local/bin/rands

clean:
	rm -f *.o rands

.PHONY: all clean

