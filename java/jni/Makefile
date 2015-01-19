# windows: xxx.dll, mac: libxxx.dylib, linux: libxxx.so
TARGET = liblib_TestLibrary.dylib
DST_DIR = lib
DST = $(DST_DIR)/$(TARGET)
SRCS = src/main/c/lib_TestLibrary.c
JAVA_INCLUDE = /System/Library/Frameworks/JavaVM.framework/Headers

CC = gcc
CFLAGS = -fPIC -I$(JAVA_INCLUDE)
LDFLAGS = -shared

all: $(TARGET)

$(TARGET):
	-mkdir $(DST_DIR)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(DST) $(SRCS)

clean:
	rm $(DST)
