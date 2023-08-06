CC=gcc
CFLAGS=

OBJS= src/main.o \
	src/proc.o \
	src/mail.o \
	src/network.o \

OBJS_TEST= src/test.o \
	src/proc.o \
	src/mail.o \
	src/network.o \

build: $(OBJS)
	$(CC) -o target/LINUX-PROC-MONITOR $(OBJS) $(CFLAGS)

all: clean build
	./target/LINUX-PROC-MONITOR > main.txt

build-test: $(OBJS_TEST)
	$(CC) -o target/test $(OBJS_TEST) $(CFLAGS)

test: clean build-test
	./target/test

$(OBJS_TEST):%.o:%.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJS):%.o:%.c
	$(CC) -c $< -o $@ $(CFLAGS)

build-simulation:
	$(CC) simulation/simulate.c -o simulation/simulate
	
simulation:build-simulation
	./simulation/simulate

clean:
	rm -f target/*
	rm -f src/*.o
	rm -f *.txt
	rm -f simulation/simulate