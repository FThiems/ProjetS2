/**
 * \file data.c
 * \brief Signatures des fonctions liées aux données du monde
 */

#ifndef DATA
#define DATA
/**
 * \brief Definitions des constantes, des structures et des includes
 */
#include "definitions.h"

/**** SIGNATURES ****/

/**
 * \brief Fonction qui initalise la position des boules sur le billard
 * \param world les données du monde
 */
void init_balls(world_t* world);

/**
 * \brief Fonction qui initialise le tableau contenant les trous de la table
 * \param world données du monde
 */
void init_holes(world_t* world);

/**
 * \brief Fonction qui calcule la distance euclidienne entre une boule choisie et un trou
 * \param world données du monde
 * \param ball_number indice de la boule dans le tableau des boules
 * \param hole_number indice du trou dans le tableau des trous
 * \return la distance euclidienne entre le centre du trou choisi et de la boule choisie
 */
int dist_ball_hole(world_t* world, int ball_number, int hole_number);

/**
 * \brief Fonction qui test si une balle tombe dans un trou
 * \param world données du monde
 * \param ball_number indice de la boule dans le tableau des boules
 * \param hole_number indice du trou dans le tableau des trous
 * \return true si la boule tombe, false sinon
*/
bool is_falling(world_t* world, int ball_number, int hole_number);

/**
 * \brief Fonction qui teste toutes les boules pour tous les trous pour voir si elles doivent tomber dedans
 * \param world données du monde
 */
void test_is_falling(world_t* world);

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

#endif
