/**
 * \file data.c
 * \brief Fonctions liées aux données du monde
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
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */
void init_data(world_t* world);

/**
 * \brief La fonction nettoie les données du monde
 * \param world les données du monde
 */
void clean_data(world_t* world);

/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param world les données du monde
 */
void update_data(world_t* world);

