/**
 * \file ball_functions.c
 * \brief Ball pointer retrieving functions
 */


/**
 * \brief Imports and function headers for this file
 */
#include"headers/ball_functions.h"


//!Tells if the turn isn't over
int isTurnGoing(world_t* world){
    int ball_number; //!Current ball's index
    ball_t* current; //!Current ball's pointer

    if(world->notWaiting){
        return 0;
    }

    for (ball_number = 0; ball_number < NB_BALLS; ball_number++){
        current = get_ball(ball_number,world);
        if (current->vx>0.05 || current->vy>0.05) //if moving
            return 1;
    }

    return 0; //none was moving
}

//!Returns the distance between A and B
int distance(ball_t* A, ball_t* B){
    int dist_x = A->x - B->x;
    int dist_y = A->y - B->y;
    return sqrt(dist_x*dist_x + dist_y*dist_y);
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
