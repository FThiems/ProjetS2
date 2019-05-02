/**
 * \file graphics.c
 * \brief Signatures des fonctions liées aux éléments graphiques du jeu
 */

/**
 * \brief Definitions des constantes, des structures et des includes
 */
#include "definitions.h"
/**
 * \brief Fonctions liées aux balles
 */
#include "ball_functions.h"

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
