CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
ifeq ($(OS),Windows_NT)
	LDFLAGS =  -lraylib -lopengl32 -lgdi32 -lwinmm -lcomdlg32 -lole32
else
	LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
endif
MENU_SRC = src/menu.c src/utility.c
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

TARGET = out/game

all: $(TARGET)

$(TARGET): $(OBJ) | out
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

run:
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