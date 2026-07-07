CC = gcc
TARGET = visualizer

RAYLIB  ?= ./libs/raylib/src/
LIBI = -I./cfft/include/
INCLUDES = -I./include/ -I$(KISSFFT) -I$(RAYLIB) $(LIBI)
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c, build/%.o, $(SRC))

LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -lcfft
CFLAGS = $(INCLUDES) -std=c11 -O2

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -L$(RAYLIB) -L./libs/ $(LIBS) -o $(TARGET)

build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

build:
	mkdir -p build

lib:
	mkdir -p ./cfft/build
	$(CC) $(CFLAGS) $(LIBI) -c ./cfft/src/complex.c -o ./cfft/build/complex.o
	$(CC) $(CFLAGS) $(LIBI) -c ./cfft/src/cfft.c -o ./cfft/build/cfft.o
	ar rcs ./libs/libcfft.a ./cfft/build/complex.o ./cfft/build/cfft.o 

clean:
	rm -rf build $(TARGET)
