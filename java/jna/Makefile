# windows: xxx.dll, mac: libxxx.dylib, linux: libxxx.so
TARGET = libtest.dylib
DST = src/main/resources/$(TARGET)
SRCS := $(wildcard src/main/c/*.c)

CC = gcc
CFLAGS = -fPIC
LDFLAGS = -shared

all: $(TARGET)

$(TARGET):
		$(CC) $(CFLAGS) $(LDFLAGS) -o $(DST) $(SRCS)

clean:
		rm $(DST)
