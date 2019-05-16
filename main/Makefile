SRC=main.c $(LIB)sdl-light.c $(LIB)ball_functions.o $(LIB)data.o $(LIB)events.o $(LIB)graphics.o $(LIB)collision.o
HEADERS=$(LIBH)sdl-light.h $(LIBH)graphics.h $(LIBH)events.h $(LIBH)data.h $(LIBH)definitions.h
BIN=billard
LIBS=-L/usr/lib/x86_64-linux-gnu -lsndfile -lm
#raccourcis
LIB=library/
LIBH=library/headers/
CHECK_SDL=./Check_sdl.sh

$(BIN): $(SRC) $(HEADERS)
	clear;clear;make check;gcc -Wall -g  -std=c99 $(SRC) -lm `sdl-config --cflags --libs` -o $(BIN)

ball_functions.o: $(LIB)ball_functions.c
	gcc -Wall -g `sdl-config --cflags --libs` -c ball_functions.c -o ball_functions.o

data.o: $(LIBH)data.c $(LIB)ball_functions.o $(LIBH)ball_functions.h $(LIBH)defintions.h
	gcc -Wall -g `sdl-config --cflags --libs` -c data.c -o data.o

events.o: $(LIBH)definitions.h $(LIB)events.c $(LIB)ball_functions.c
	gcc -Wall -g `sdl-config --cflags --libs` -c events.c -o events.o

graphics.o: $(LIBH)ball_functions.h $(LIBH)definitions.h $(LIB)graphics.c
	gcc -Wall -g `sdl-config --cflags --libs`-c graphics.c -o graphics.o
	
collision.o: $(LIBH)collision.h $(LIB)collision.c
	gcc -Wall -g `sdl-config --cflags --libs`-c collision.c -o collision.o

clean: clean_o
	rm -f $(BIN); make clean_o

clean_o:
	cd library;rm -f ball_functions.o; rm -f data.o; rm -f events.o; rm -f graphics.o; cd ..

kate:
	kate Makefile main.c library/* library/headers/*

check:
	$(CHECK_SDL)
