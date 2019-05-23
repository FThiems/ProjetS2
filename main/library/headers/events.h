/**
 * \file events.h
 * \brief Player input event handling
 */


#ifndef EVENTSFLAG
#define EVENTSFLAG

///// Imports //////////////////////////////////////////////////////////////
#include "initialisation.h" //Imports and function headers for this file




///// Signatures //////////////////////////////////////////////////////////////

/**
 * \brief Handles a mouse intput
 * \param world Data bundling all persistent game infos
 */
void mouse_input(world_t* world);

/**
 * \brief Handles keyboard input
 * \param keystates SDL keystates
 * \param world Data bundling all persistent game infos
 */
void keyboard_input(Uint8* keystates, world_t* world);

/**
 * \brief Function called each tic to process player inputs
 * \param event SDL's events
 * \param world Data bundling all persistent game infos
 */
void handle_events(SDL_Event* event,world_t* world);


#endif
