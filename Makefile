UNAME_S := $(shell uname -s)

CC = gcc
CFLAGS = -nostdlib -fno-builtin -Os -Wall -Wextra

ifeq ($(UNAME_S),Darwin)
	CC = clang
	SDK_PATH := $(shell xcrun --show-sdk-path)

	CFLAGS += -arch arm64 -e __start -isysroot $(SDK_PATH) -lSystem
endif

TARGET = sleep
SRC = sleep.c
HEADERS = syscalls.h

all: $(TARGET)

$(TARGET): $(SRC) $(HEADERS)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

.PHONY: all clean