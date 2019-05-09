/**
 * \file graphics.c
 * \brief Fonctions liées aux éléments graphiques du jeu
 */

/**
 * \brief Definitions des constantes, des structures et des includes
 */
#include "headers/definitions.h"
/**
 * \brief Fonctions liées aux balles
 */
#include "headers/ball_functions.h"

/**** SIGNATURES ****/

/**
 * \brief La fonction initialise les transparences des différentes surfaces
 * \param screen la surface correspondant à l'écran de jeu
 * \param world les données du monde
 */
void  init_graphics(SDL_Surface* screen, world_t* world);

/**
 * \brief La fonction rafrachit l'écran en fonction de l'état des données du monde
 * \param screen la surface de l'écran de jeu
 * \param world les données du monde
 */
void refresh_graphics(SDL_Surface* screen, world_t* world);

/**** FONCTIONS ****/

void  init_graphics(SDL_Surface* screen, world_t* world){
    set_transparence(screen,world->balls_sprite,255,0,255);
}

void refresh_graphics(SDL_Surface* screen, world_t* world){
    apply_surface(world->table,screen,0,0);

    int ball_number,on_screen_x,on_screen_y;
    for (ball_number = 0; ball_number < NB_BALLS; ball_number++){
        on_screen_x = *get_px(ball_number,world)-BALL_SIZE/2;
        on_screen_y = *get_py(ball_number,world)-BALL_SIZE/2;
        if(world->balls[ball_number]->fell == false){
          apply_sub_surface(world->balls_sprite,screen,ball_number*BALL_SIZE,0,BALL_SIZE,BALL_SIZE, on_screen_x, on_screen_y);
        }
    }
    refresh_surface(screen);
}
