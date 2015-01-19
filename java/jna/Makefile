# windows: xxx.dll, mac: libxxx.dylib, linux: libxxx.so
TARGET = libtest.dylib
DST_DIR = lib
DST = $(DST_DIR)/$(TARGET)
SRCS := $(wildcard src/main/c/*.c)

CC = gcc
CFLAGS = -fPIC
LDFLAGS = -shared

all: $(TARGET)

$(TARGET):
	-mkdir $(DST_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(DST) $(SRCS)

clean:
	rm $(DST)
