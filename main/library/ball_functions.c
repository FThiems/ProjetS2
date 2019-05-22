/**
 * \file ball_functions.c
 * \brief Ball pointer retrieving functions
 */


/**
 * \brief Imports and function headers for this file
 */
#include"headers/ball_functions.h"


//!Tells if some balls are still moving
bool anyMoving(world_t* world){
    int ball_number; //!Current ball's index
    ball_t* current; //!Current ball's pointer

    if(world->notWaiting){
        return true;
    }

    for (ball_number = 0; ball_number < NB_BALLS; ball_number++){
        current = get_ball(ball_number,world);
        if (current->vx>0.05 || current->vy>0.05) //if moving
            return true;
    }

    return false; //none was moving
}

// Pointer
ball_t* get_ball(int ball_number,world_t* world){
    return world->balls[ball_number];
}




////// Deprecated
// Positions
double* get_px(int ball_number,world_t* world){
    return &(world->balls[ball_number]->x);
}
double* get_py(int ball_number,world_t* world){
    return &(world->balls[ball_number]->y);
}


//Speeds
double* get_pvx(int ball_number,world_t* world){
    return &(world->balls[ball_number]->vx);
}
double* get_pvy(int ball_number,world_t* world){
    return &(world->balls[ball_number]->vy);
}

//Remaining Speeds
double* get_p_Remaining_vx(int ball_number,world_t* world){
    return &(world->balls[ball_number]->vRemainingX);
}
double* get_p_Remaining_vy(int ball_number,world_t* world){
    return &(world->balls[ball_number]->vRemainingY);
}
