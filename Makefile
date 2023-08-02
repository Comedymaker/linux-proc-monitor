CC=gcc
CFLAGS=

build:
	$(CC) src/main.c -o target/LINUX-PROC-MONITOR

all: clean build
	./target/LINUX-PROC-MONITOR

build-test:
	$(CC) src/test.c -o target/test

test: build-test
	./target/test 

clean:
	rm -f target/*