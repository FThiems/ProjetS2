/**
 * \file ball_functions.h
 * \brief Ball handling functions
 */


#ifndef BF_VVVV
#define BF_VVVV

///// Imports //////////////////////////////////////////////////////////////
#include "definitions.h" //Constants, structures and includes




///// Signatures //////////////////////////////////////////////////////////////


///// Ball info //////////////////////////////////////////////////////////////
/**
 * \brief Tells if the turn isn't over
 * \param world Data bundling all persistent game infos
 */

int moving_or_not_waiting(world_t* world);

/**
 * \brief Returns the distance between A and B
 * \param A First ball
 * \param B Second ball
 */
int distance(ball_t* A, ball_t* B);


///// Ball instructions //////////////////////////////////////////////////////////////
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


///// Ball retrieval //////////////////////////////////////////////////////////////
/**
 * \brief returns a pointer to ball_number
 * \param ball_number Index of the working ball
 * \param world Data bundling all persistent game infos
 */
ball_t* get_ball(int ball_number,world_t* world);

/**
 * \brief Returns a random non-fallen ball (or any i ghost is activated), white if none was eligible
 * \param world Data bundling all persistent game infos
 */
ball_t* get_random_ball(world_t* world);


#endif