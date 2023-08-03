CC=gcc
CFLAGS=

OBJS= src/main.o \
	src/proc.o \

OBJS_TEST= src/test.o \
	src/proc.o \

build: $(OBJS)
	$(CC) -o target/LINUX-PROC-MONITOR $(OBJS) $(CFLAGS)

all: clean build
	./target/LINUX-PROC-MONITOR > main.txt

build-test: $(OBJS_TEST)
	$(CC) -o target/test $(OBJS_TEST) $(CFLAGS)

test: clean build-test
	./target/test > test.txt

$(OBJS_TEST):%.o:%.c
	$(CC) -c $< -o $@ $(CFLAGS)

$(OBJS):%.o:%.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f target/*
	rm -f src/*.o