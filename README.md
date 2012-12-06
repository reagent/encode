# encode.c

A simple C program to shift characters found in an input stream.

## Usage

Basic usage:

    echo 'hi there' | ./encode

Changing the number of characters to shift:

    echo 'hi there' | ./encode -n2

Decoding a string:

    echo 'ij uifsf' | ./encode -d

Reading from a file:

    ./encode -f input.txt

# Building

All you need to do is run `make` from the root directory.  You can run `make check` to ensure it's working properly.
