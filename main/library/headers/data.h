/**
 * \file data.h
 * \brief World editing functions
 */


#ifndef DATA
#define DATA

///// Imports //////////////////////////////////////////////////////////////
/**
 * \brief Constants, structures and includes
 */
#include "definitions.h"

/**
 * \brief Ball pointer retrieving functions
 */
#include "ball_functions.h"

/**
 * \brief Signatures des fonctions de gestion des collisions
 */
#include "collision.h"




///// Signatures //////////////////////////////////////////////////////////////
///// Initialisations ////////////////////////////////////////////////
/**
 * \brief Sets world's parameters
 * \param world Data bundling all persistent game infos
 */
void init_parameters(world_t* world);

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
 * \brief Places holes
 * \param world Data bundling all persistent game infos
 */
void init_data(world_t* world);




///// Hole functions ////////////////////////////////////////////////
/**
 * \brief Calculates the distance between the corresponding ball and hole s
 * \param world Data bundling all persistent game infos
 * \param ball_number Index of the working ball
 * \param hole_number Index of the working hole
 * \return The distance between the corresponding ball and hole s
 */
int dist_ball_hole(world_t* world, int ball_number, int hole_number);

/**
 * \brief Function checking if the corresponding ball should fall in the hole or not
 * \param world Data bundling all persistent game infos
 * \param ball_number Index of the working ball
 * \param hole_number Index of the working hole
 * \return (int) the ball is falling in the hole
*/
bool is_falling(world_t* world, int ball_number, int hole_number);

/**
 * \brief Function checking if any ball should fall in any hole and making them fall
 * \param world Data bundling all persistent game infos
 */
void all_holes(world_t* world);

/**
 * \brief Adds the fallen ball's points to the turn point buffer
 * \param world Data bundling all persistent game infos
 * \param ball_number Index of the working ball
 */
void scoring(world_t* world, int ball_number);

/**
 * \brief Transfers the content of the point buffer
 * \param world Data bundling all persistent game infos
 */

void pointsTransfer(world_t* world);



///// Clean function ////////////////////////////////////////////////
/**
 * \brief Cleans all mallocs and callocs
 * \param world Data bundling all persistent game infos
 */
void clean_data(world_t* world);



///// Movement functions ////////////////////////////////////////////////
/**
 * \brief Moves ball toward x,y
 * \param current Pointer of the working ball
 */
void target(int x, int y, ball_t* ball);

/**
 * \brief Moves ball toward x,y
 * \param current Pointer of the working ball
 */
void flee(int x, int y, ball_t* ball);

/**
 * \brief Bounce off walls
 * \param ball_number Index of the working ball
 * \param world Data bundling all persistent game infos
 */
void wall_bounce(int ball_number, world_t* world);

/**
 * \brief Bounce off other balls
 * \param ball_number Index of the working ball
 * \param watched_ball_number Index of the watched ball (the ball we may be colliding with)
 * \param world Data bundling all persistent game infos
 */
void ball_bounce(int ball_number, int watched_ball_number, world_t* world);

/**
 * \brief Moves ball by tiny vectors until they travelled their respective remaining vx/vy, checks bounces
 * \param remaining_baby_steps Amount of steps this tic should be split in
 * \param world Data bundling all persistent game infos
 */
void baby_loop(int remaining_baby_steps, world_t* world);

/**
 * \brief Slows ball by world->friction_multiplier
 * \param current Pointer of the working ball
 * \param world Data bundling all persistent game infos
 */
void friction_ball(ball_t* current,world_t* world);

/**
 * \brief Slows the right balls by world->friction_multiplier
 * \param world Data bundling all persistent game infos
 */
void friction(world_t* world);

/**
 * \brief Everything that happens when a turn ends
 * \param world Data bundling all persistent game infos
 */
void turnOver(world_t* world);


///// Update Data ////////////////////////////////////////////////
/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param world Data bundling all persistent game infos
 */
void update_data(world_t* world);


#endif
