CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS =  -lraylib -lopengl32 -lgdi32 -lwinmm -lcomdlg32 -lole32

MENU_SRC = src/menu.c src/utility.c
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

TARGET = out/game

all: $(TARGET)

$(TARGET): $(OBJ) | out
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)
	./$(TARGET)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@
	
out:
	mkdir out

ifeq ($(OS),Windows_NT)
clean:
	del /q /s src\*.o out\*
else
clean:
	rm -f src/*.o out/*
endif