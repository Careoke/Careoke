CC = cc
CFLAGS = -Wall -Wextra -Iinclude -O2
ifeq ($(OS),Windows_NT)
	LDFLAGS =  -lraylib -lopengl32 -lgdi32 -lwinmm -lcomdlg32 -lole32
else
	LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
endif
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c,out/obj/%.o,$(SRC))

TARGET = out/game

all: $(TARGET)

$(TARGET): $(OBJ) | out
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

	
out/obj/%.o: src/%.c | out/obj
	$(CC) $(CFLAGS) -c $< -o $@
	

out:
	mkdir out

out/obj:
	mkdir out\obj

ifeq ($(OS),Windows_NT)
clean:
	rmdir /s /q out
else
clean:
	rm -rf out
endif