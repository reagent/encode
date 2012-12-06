PREFIX?=./vendor
CFLAGS=-g -Wall -I${PREFIX}/apr/include/apr-1
LDFLAGS=-L${PREFIX}/apr/lib -lapr-1 -pthread

all: encode

encode: source.o char.o

check:
	./test/encode-test

clean:
	rm -rf encode *.o *.dSYM