TARGET = libhello.a
SRCS := $(wildcard *.c)
OBJS := $(subst .c,.o,$(SRCS))

CC = gcc
CFLAGS = -Wall

.SUFFIXES: .c .o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(AR) r $@ $^

.c.o: $<
	$(CC) -c $(CFLAGS) $<

clean:
	rm $(TARGET) $(OBJS)
