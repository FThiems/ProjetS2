/**
 * \file events.c
 * \brief Fonctions liées à la gestion des evenements 
 */

/**
 * \brief Definitions des constantes, des structures et des includes
 */
#include "definitions.h"

/**** SIGNATURES ****/

/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */
void handle_events(SDL_Event* event,world_t* world);
