PREFIX?=./vendor
CFLAGS=-g -Wall -I${PREFIX}/apr/include/apr-1
LDFLAGS=-L${PREFIX}/apr/lib -lapr-1 -pthread

all: encode

clean:
	rm -rf encode *.o *.dSYM