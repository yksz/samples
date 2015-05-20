CC = gcc
CFLAGS = -Wall

.SUFFIXES: .c .o

all: unix

unix: main.o impl_unix.o
	$(CC) -o a.out $(LDFLAGS) $^

windows: main.o impl_windows.o
	$(CC) -o a.out $(LDFLAGS) $^

.c.o: $<
	$(CC) -c $(CFLAGS) $<

clean:
	rm $(TARGET) $(OBJS)
