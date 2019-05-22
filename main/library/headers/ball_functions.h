/**
 * \file ball_functions.h
 * \brief Ball pointer retrieving functions
 */


#ifndef BF_VVVV
#define BF_VVVV

///// Imports //////////////////////////////////////////////////////////////
/**
 * \brief Constants, structures and includes
 */
#include "definitions.h"




///// Signatures //////////////////////////////////////////////////////////////
/**
 * \brief Tells if the turn isn't over
 * \param world Data bundling all persistent game infos
 */

int isTurnOver(world_t* world);

//! returns a pointer to ball_number
ball_t* get_ball(int ball_number,world_t* world);


// Positions
double* get_px(int ball_number,world_t* world);

double* get_py(int ball_number,world_t* world);



//Speeds
double* get_pvx(int ball_number,world_t* world);

double* get_pvy(int ball_number,world_t* world);


//Remaining Speeds
double* get_p_Remaining_vx(int ball_number,world_t* world);

double* get_p_Remaining_vy(int ball_number,world_t* world);

#endif