# windows: xxx.dll, mac: libxxx.dylib, linux: libxxx.so
TARGET = liblib_TestLibrary.dylib
DST = src/main/resources/$(TARGET)
SRCS = src/main/c/lib_TestLibrary.c
JAVA_INCLUDE = /System/Library/Frameworks/JavaVM.framework/Headers

CC = gcc
INCLUDES = -I $(JAVA_INCLUDE)
CFLAGS = -fPIC -shared $(INCLUDES)

all: $(TARGET)

$(TARGET):
		$(CC) $(CFLAGS) -o $(DST) $(SRCS)

clean:
		rm $(DST)
