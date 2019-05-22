/**
 * \file definitions.h
 * \brief Constants, structures and includes
 */


#ifndef DEFINITIONS
#define DEFINITIONS

///// Imports //////////////////////////////////////////////////////////////
#include "sdl-light.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>




///// Constants //////////////////////////////////////////////////////////////
/**
 *  \brief Screen width
 */
#define SCREEN_WIDTH 1288

/**
 *\brief Screen height
 */
#define SCREEN_HEIGHT 725

/**
 *\brief ball size
 */
#define BALL_SIZE 42
/**
 *  \brief Size of the border
 */
#define BORDER_SIZE 80
/**
 *  \brief Speed multiplier
 */
#define SPEED_COEF 0.1
/**
 *  \brief Borders
 */
#define BORDER_RIGHT (1202-BALL_SIZE/2)
#define BORDER_LEFT (85+BALL_SIZE/2)
#define BORDER_DOWN (640-BALL_SIZE/2)
#define BORDER_UP (85+BALL_SIZE/2)
/**
 * \brief Ball count
 */
#define NB_BALLS 16
/**
 * \brief Hole count
 */
#define NB_HOLES 6
/**
 * \brief Hole radius'
*/
#define HOLE_RADIUS 35
/**
 * \brief
 */
#define LEFT 625
#define RIGHT 663



///// Structures //////////////////////////////////////////////////////////////
/**
 * \brief Ball info
 */
struct ball_s{
    double x,y; /*!< Coordinates of the ball's center */
    double vx,vy; /*!< Speed vectors, on x and y */
    double vRemainingX,vRemainingY; /*!< Speed vectors that the ball still has to travel during current tic */
    bool fell; /*!< Flag to tell if a ball already fell in a hole */
};
typedef struct ball_s ball_t;


/**
 * \brief Table's holes
 */
struct holes_s{
    int x;/*!< Hole's x coordinate */
    int y;/*!< Hole's y coordinate */
};
typedef struct holes_s holes_t;


/**
 * \brief Data bundling all persistent game infos
 */
struct world_s{
    //Game infos
        //Flags
        int gameover;                /*!< Game ending variable */

        //Data
        ball_t** balls;              /*!< Balls pointer array */
        holes_t** holes;             /*!< Holes pointer array */
        //Changeable physics values
        double friction_multiplier;     /*!< Amount by which a balls speed should be multiplied each tic, if subjected to friction */
        int main_delay;              /*!< Delay between two executions of the main loop */

        //Images
        SDL_Surface* table;          /*!< SDL Surface of the table */
        SDL_Surface* balls_sprite;   /*!< SDL Surface of the 16 balls */

    //Player handling
        //Flag
        int active_player;           /*!< Active player, 0 or 1 */
        int playerChanged;           /*!< Tells if the player already changed since last turn */
        //Data
        int p0;                     /*!< Player 0's points */
        int p1;                     /*!< Player 1's points */
        int pointsBuffer;           /*!< Points buffer */
        //Images
        SDL_Surface* text_numbers0; /*!< SDL Surface of the number of points of P0 */
        SDL_Surface* text_numbers1; /*!< SDL Surface of the number of points of P1 */
        SDL_Surface* text_player; /*!< SDL Surface of the Logos of both players*/


    //Game modifiers
        //Flags
        int ghost;                   /*!< Tells if fallen balls should still be active, 1 for bouncy, 2 for showing, 3 for both*/
        int notBouncing;                /*!< Tells if balls should bounce each other */
        int funky_overlapp;          /*!< Attempts to mimic the "funky" overlapping code */
        int friction;                /*!< Tells which balls should slow down, 0 for all, 1 for white only, 2 for colored only, 3 for fallen only */
        int notWaiting;                   /*!< Tells if players should wait between two shot */
        int fight;                  /*!< Send the ghosts after get_ball(1, world) */

        //Images
        SDL_Surface* text_ghost;   /*!< SDL Surface of the ghost text */
        SDL_Surface* text_notBouncing;  /*!< SDL Surface of the not bouncing text */
        SDL_Surface* text_funky_overlapp;  /*!< SDL Surface of the funky overlapp text */
        SDL_Surface* text_friction; /*!< SDL Surface of the friction text */


};

typedef struct world_s world_t;



#endif
