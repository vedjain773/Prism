CC = gcc
TARGET = visualizer

RAYLIB  ?= ./libs/raylib/src/
INCLUDE  = ./include/
SRC      = $(wildcard src/*.c)
OBJ      = $(patsubst src/%.c, build/%.o, $(SRC))

LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
CFLAGS = -I$(RAYLIB) -I$(INCLUDE) -std=c11

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -L$(RAYLIB) $(LIBS) -o $(TARGET)

build/%.o: src/%.c | build
	$(CC) $(CFLAGS) -c $< -o $@

build:
	mkdir -p build

clean:
	rm -rf build $(TARGET)
