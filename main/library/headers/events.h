/**
 * \file events.h
 * \brief Player input event handling
 */


#ifndef EVENTSFLAG
#define EVENTSFLAG

///// Imports //////////////////////////////////////////////////////////////
/**
 * \brief Constants, structures and includes
 */
#include "definitions.h"

/**
 * \brief Ball pointer retrieving functions
 */
#include "ball_functions.h"




///// Signatures //////////////////////////////////////////////////////////////

/**
 * \brief Tells if some balls are still moving
 * \param world Data bundling all persistent game infos
 */

int anyMoving(world_t* world);

/**
 * \brief Handles a mouse intput
 * \param world Data bundling all persistent game infos
 */
void mouse_input(world_t* world);

/**
 * \brief Function called each tic to process player inputs
 * \param event SDL's events
 * \param world Data bundling all persistent game infos
 */
void handle_events(SDL_Event* event,world_t* world);


#endif
