/**
 * \file data.c
 * \brief Signatures des fonctions liées aux balles
 */

/**
 * \brief Definitions des constantes, des structures et des includes
 */
#include "definitions.h"


#ifndef BF_VVVV
#define BF_VVVV
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