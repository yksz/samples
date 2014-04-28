# windows: xxx.dll, mac: libxxx.dylib, linux: libxxx.so
TARGET = libtest.dylib
DST = ../resources/$(TARGET)
SRCS := $(wildcard *.c)

CC = gcc

all: $(TARGET)

$(TARGET):
		$(CC) -fPIC -shared -o $(TARGET) $(SRCS)
		mv $(TARGET) $(DST)

clean:
		rm $(DST)
