CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS =  -lraylib -lopengl32 -lgdi32 -lwinmm

SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

TARGET = out/game

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET)