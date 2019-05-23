/**
 * \file graphics.h
 * \brief Display functions
 */


#ifndef GRAPHICSFLAG
#define GRAPHICSFLAG

///// Imports //////////////////////////////////////////////////////////////
#include "ball_functions.h" //Ball handling functions




///// Signatures //////////////////////////////////////////////////////////////

/**
 * \brief Sets the different images transparency values
 * \param screen Screen surface
 * \param world Data bundling all persistent game infos
 */
void init_graphics(SDL_Surface* screen, world_t* world);

/**
 * \brief Displays every ball_t on the table
 * \param screen Screen surface
 * \param world Data bundling all persistent game infos
 */
void refresh_balls(SDL_Surface* screen, world_t* world);

/**
 * \brief Displays game modifiers
 * \param screen Screen surface
 * \param world Data bundling all persistent game infos
 */
void refresh_modifiers(SDL_Surface* screen, world_t* world);

/**
 * \brief Function called each tic to process display output
 * \param screen Screen surface
 * \param world Data bundling all persistent game infos
 */
void refresh_graphics(SDL_Surface* screen, world_t* world);


#endif