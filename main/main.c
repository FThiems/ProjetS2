/**
 * \file main.c
 * \brief Billard
 */

/**
 * \brief Definitions des constantes, des structures et des includes
 */
#include "library/headers/definitions.h"

/**
 *\brief Signatures des fonctions de data.c
 */
#include "library/headers/data.h"

/**
 * \brief Fonctions liées aux éléments graphiques du jeu
 */
#include "library/headers/graphics.h"

/**
 * \brief Fonctions liées aux éléments graphiques du jeu
 */
#include "library/headers/events.h"

/**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world les données du monde
 * \return 1 si le jeu est fini, 0 sinon
 */
int is_game_over(world_t* world){
    return world->gameover;
}

/**
 *  \brief programme principal qui implémente la boucle du jeu
 */


int main( int argc, char* args[] )
{
    SDL_Event event;
    world_t world;
    SDL_Surface *screen;

    screen = init_sdl(SCREEN_WIDTH, SCREEN_HEIGHT);
    init_data(&world);
    init_graphics(screen,&world);

    while(!is_game_over(&world)){
        handle_events(&event,&world);
        update_data(&world);
        refresh_graphics(screen,&world);
        SDL_Delay(world.main_delay);
    }

    clean_data(&world);
    quit_sdl();


    return 0;
}
