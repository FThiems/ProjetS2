/**
 * \file main.c 
* \brief Billard
 */



#include "library/headers/data.h" //World editing functions
#include "library/headers/graphics.h" //Display functions
#include "library/headers/events.h" //Player input event handling



/**
 *  \brief Main program
 */
int main( int argc, char* args[] )
{
    SDL_Event event;
    world_t world;
    SDL_Surface *screen;

    screen = init_sdl(SCREEN_WIDTH, SCREEN_HEIGHT);
    init_data(&world);
    init_graphics(screen,&world);

    while(!world.gameover){
        handle_events(&event,&world);
        update_data(&world);
        refresh_graphics(screen,&world);
        SDL_Delay(world.main_delay);
    }

    clean_data(&world);
    quit_sdl();


    return 0;
}
