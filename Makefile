CC = cc
CFLAGS = -Wall -Wextra -Iinclude -O2
ifeq ($(OS),Windows_NT) 
	LDFLAGS = -lraylib -lopengl32 -lgdi32 -lwinmm -lcomdlg32 -lole32
	R_LDFLAGS = out/lib/libraylib.a -lopengl32 -lgdi32 -lwinmm -lcomdlg32 -lole32
else
	LDFLAGS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
	R_LDFLAGS = out/lib/libraylib.a -lGL -lm -lpthread -ldl -lrt -lX11
endif
SRC = $(wildcard src/*.c)
OBJ = $(patsubst src/%.c,out/obj/%.o,$(SRC))

TARGET = out/game

.PHONY: debug build release run clean assets

$(TARGET): $(OBJ) | out
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS) $(PFLAGS)

debug: clean
	$(MAKE) CFLAGS="$(CFLAGS) -DDEBUG -g -O0" PFLAGS= $(TARGET)

build: clean assets
	$(MAKE) CFLAGS="$(CFLAGS)" PFLAGS=-mwindows $(TARGET)

# for github action
release: assets
	$(MAKE) CFLAGS="$(CFLAGS) -DRELEASE" PFLAGS=-mwindows LDFLAGS="$(R_LDFLAGS)" $(TARGET)

assets: out/utils
	python src/bin2c.py

run:
	./$(TARGET)

	
out/obj/%.o: src/%.c | out/obj
	$(CC) $(CFLAGS) -c $< -o $@
	

out:
	-mkdir out

ifeq ($(OS),Windows_NT)
out/obj: out
	-mkdir out\obj

out/utils: out
	-mkdir out\utils
else
out/obj: out
	mkdir -p out/obj

out/utils: out
	mkdir -p out/utils
endif

ifeq ($(OS),Windows_NT)
clean:
	-rmdir /s /q out
else
clean:
	rm -rf out
endif