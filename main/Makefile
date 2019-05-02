SRC=main.c $(LIB)sdl-light.c $(LIB)ball_functions.c $(LIB)data.c $(LIB)events.c $(LIB)graphics.c
HEADERS=$(LIBH)sdl-light.h $(LIBH)graphics.h $(LIBH)events.h $(LIBH)data.h $(LIBH)definitions.h
BIN=billard
LIBS=-L/usr/lib/x86_64-linux-gnu -lsndfile -lm
LIB=library/
LIBH=library/headers/

$(BIN): $(SRC) $(HEADERS)
	clear;clear;gcc -Wall -g  -std=c99 $(SRC) -lm `sdl-config --cflags --libs` -o $(BIN)
	
ball_functions.o: $(LIB)ball_functions.c
	gcc -Wall -g $(LIBS) `sdl-config --cflags --libs` -c ball_functions.c -o ball_functions.o
	
data.o: $(LIBH)data.c $(LIBH)data.h $(LIB)ball_functions.o $(LIBH)ball_functions.h $(LIBH)defintions.h
	gcc -Wall -g $(LIBS) `sdl-config --cflags --libs` -c data.c -o data.o

clean:
	rm -f $(BIN)
	
kate:
	kate Makefile $(SRC)  
