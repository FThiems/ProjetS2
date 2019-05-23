/**
 * \file initialisation.h
 * \brief Initialisations of different components
 */


#ifndef INITIALISATION_H_123
#define INITIALISATION_H_123

///// Imports //////////////////////////////////////////////////////////////
#include "ball_functions.h" //Ball handling functions




///// Signatures //////////////////////////////////////////////////////////////
///// Initialisations ////////////////////////////////////////////////
/**
 * \brief Sets world's parameters
 * \param world Data bundling all persistent game infos
 */
void init_parameters(world_t* world);

/**
 * \brief Places the white ball
 * \param world Data bundling all persistent game infos
 */
void init_white(world_t* world);

/**
 * \brief Places all balls at the right spot
 * \param world Data bundling all persistent game infos
 */
void init_balls(world_t* world);

/**
 * \brief Places holes
 * \param world Data bundling all persistent game infos
 */
void init_holes(world_t* world);

/**
 * \brief Places holes
 * \param world Data bundling all persistent game infos
 */
void init_sdl_surfaces(world_t* world);

/**
 * \brief Initialises the players scores
 * \param world Data bundling all persistent game infos
 */
void init_score(world_t* world);




#endif