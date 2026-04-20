CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS =  -lraylib -lopengl32 -lgdi32 -lwinmm

MENU_SRC = src/menu.c src/utility.c
SRC = $(wildcard src/*.c)
OBJ = $(SRC:.c=.o)

TMENU = out/menu
TARGET = out/game

all: $(TARGET)

menu: $(TMENU)
	./$(TMENU)

$(TMENU): $(MENU_SRC)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

src/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o $(TARGET)