TARGET = a.out
SRCS := $(wildcard *.c)
OBJS := $(subst .c,.o,$(SRCS))

CC = gcc
INCLUDES = -I /usr/local/include
CFLAGS = -Wall -std=c99 $(INCLUDES)
LIBS = -L /usr/local/lib \
-lopencv_core \
-lopencv_highgui

.SUFFIXES: .c .o

all: $(TARGET)

$(TARGET): $(OBJS)
		$(CC) -o $@ $^ $(LIBS)

.c.o: $<
		$(CC) -c $(CFLAGS) $<

clean:
		rm $(TARGET) $(OBJS)
