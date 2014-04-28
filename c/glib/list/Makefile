SHELL = /bin/sh

TARGET = a.out
SRCS := $(wildcard *.c)
OBJS := $(subst .c,.o,$(SRCS))

CC = gcc
CFLAGS = -Wall $(shell pkg-config --cflags glib-2.0)
LIBS = $(shell pkg-config --libs glib-2.0)

.SUFFIXES: .c .o

all: $(TARGET)

$(TARGET): $(OBJS)
		$(CC) -o $@ $^ $(LIBS)

.c.o: $<
		$(CC) -c $(CFLAGS) $<

clean:
		rm $(TARGET) $(OBJS)
