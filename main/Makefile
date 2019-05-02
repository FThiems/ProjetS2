SRC=main.c library/sdl-light.c library/ball_functions.c library/data.c library/events.c library/graphics.c
HEADERS=library/headers/sdl-light.h
BIN=billard
LIBS=-L/usr/lib/x86_64-linux-gnu -lsndfile -lm

$(BIN): $(SRC) $(HEADERS)
	clear;clear;gcc -Wall -g  -std=c99 $(SRC) -lm `sdl-config --cflags --libs` -o $(BIN)

clean:
	rm -f $(BIN)
