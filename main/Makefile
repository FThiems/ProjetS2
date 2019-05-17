SRC=main.c $(LIB)sdl-light.c $(LIB)ball_functions.o $(LIB)data.o $(LIB)events.o $(LIB)graphics.o $(LIB)collision.o
HEADERS=$(LIBH)sdl-light.h $(LIBH)graphics.h $(LIBH)events.h $(LIBH)data.h $(LIBH)definitions.h $(LIBH)collision.h
BIN=billard
LIBS=-L/usr/lib/x86_64-linux-gnu -lsndfile -lm

#folders
LIB=library/
LIBH=library/headers/

#shortcuts
DEFH=$(LIBH)definitions.h $(LIBH)sdl-light.h
BALLF=$(LIB)ball_functions.o
COMPILE=gcc -Wall -g `sdl-config --cflags --libs`
CLEEAAR=clear;clear;clear


############################## Main
$(BIN): $(SRC) $(HEADERS)
	$(Main)

Main=$(CLEEAAR);$(Check);$(Main_c)

Main_c=gcc -Wall -g $(SRC) -lm `sdl-config --cflags --libs` -o $(BIN)


############################## Lib
ball_functions.o:  $(LIB)ball_functions.c  $(LIBH)ball_functions.h   $(DEFH)
	$(COMPILE)    -c ball_functions.c      -o ball_functions.o

data.o:            $(LIB)data.c            $(LIBH)data.h             $(DEFH)  $(BALLF)  collision.o
	$(COMPILE)    -c data.c                -o data.o

events.o:          $(LIB)events.c          $(LIBH)events.h           $(DEFH)  $(BALLF)
	$(COMPILE)    -c events.c              -o events.o

graphics.o:        $(LIB)graphics.c        $(LIBH)graphics.h         $(DEFH)  $(BALLF)
	$(COMPILE)    -c graphics.c            -o graphics.o

collision.o:       $(LIB)collision.c       $(LIBH)collision.h
	$(COMPILE)    -c collision.c           -o collision.o


############################## Clean
clean:
	$(Clean_all)

Clean_all = $(Clean_bin); $(Clean_o)
Clean_bin = rm -f $(BIN)
Clean_o   = rm -f $(LIB)ball_functions.o; rm -f $(LIB)data.o; rm -f $(LIB)events.o; rm -f $(LIB)graphics.o


############################## Start
start: $(BIN)
	$(Start)

z:
	make force;make start

Start=$(Main);./$(BIN)

############################## IDE
kate:
	$(Clean_all);kate Makefile main.c library/* library/headers/*


############################## Debug
force:
	$(Clean_all);make

CHECK_SDL=./Check_sdl.sh
Check=$(CHECK_SDL)
