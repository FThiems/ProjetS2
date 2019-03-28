/**
 * \file graphics.c
 * \brief Fonctions liées aux éléments graphiques du jeu
 */

/**
 * \brief Definitions des constantes, des structures et des includes
 */
#include "definitions.h"

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
    apply_sub_surface(world->balls_sprite,screen,0,0,BALL_SIZE,BALL_SIZE,world->balls[0]->x-BALL_SIZE/2,world->balls[0]->y-BALL_SIZE/2);
    refresh_surface(screen);
}