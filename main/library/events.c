/**
 * \file events.c
 * \brief Fonctions liées à la gestion des evenements
 */

/**
 * \brief Definitions des constantes, des structures et des includes
 */
#include "headers/definitions.h"

/**
 * \brief Signatures des fonctions liées aux balles
 */
#include "headers/ball_functions.h"

/**** FONCTIONS ****/
//!Tells if some balls are still moving
int anyMoving(world_t* world){
    int ball_number; //!Current ball's index
    ball_t* current; //!Current ball's pointer

    for (ball_number = 0; ball_number < NB_BALLS; ball_number++){
        current = get_ball(ball_number,world);
        if (current->vx>0.05 || current->vy>0.05) //if moving
            return 1;
    }

    return 0; //none was moving
}

///// Inputs //////////////////////////////////////////////////////////////
//!Handles a mouse intput
void mouse_input(world_t* world){
    int mouseX,mouseY;

    if (!anyMoving(world) || world->notWaiting){ //If still or the notWaiting flag is on
        SDL_GetMouseState(&mouseX,&mouseY);
        //Give the white ball a speed
        world->balls[0]->vx = (mouseX - world->balls[0]->x) *SPEED_COEF;
        world->balls[0]->vy = (mouseY - world->balls[0]->y) *SPEED_COEF;

        world->active_player = (world->active_player+1)%2; //Switch player
    }
}

///// Handle events //////////////////////////////////////////////////////////////
//!Function called
void handle_events(SDL_Event* event,world_t* world){
    //Input variables
    Uint8 *keystates;
    
    while( SDL_PollEvent( event ) ) {
        //If attempt to close
        if( event->type == SDL_QUIT ) {
            //Close
            world->gameover = 1;
        }
        
        //On any mouse button up
        if( event->type == SDL_MOUSEBUTTONUP ){
            mouse_input(world);
        }
        
        keystates = SDL_GetKeyState( NULL );
        
        //Cycle different game modifiers
        //ghost
        if( keystates[ SDLK_a ] || keystates[ SDLK_g ] )
            world->ghost = (world->ghost +1)%4;                   // Tells if fallen balls should still be active, 1 for bouncy, 2 for showing, 3 for both*/
        //notBouncing
        if( keystates[ SDLK_z ] || keystates[ SDLK_b ] )
            world->notBouncing = (world->notBouncing +1)%2;             // Tells if balls should bounce each other */
        //funky_overlapp
        if( keystates[ SDLK_e ] || keystates[ SDLK_f ] )
            world->funky_overlapp = (world->funky_overlapp +1)%2; // Attempts to mimic the "funky" overlapping code */
        //friction
        if( keystates[ SDLK_r ]  )
            world->friction = (world->friction +1)%4;              // Tells which balls should slow down, 0 for all, 1 for white only, 2 for colored only, 3 for fallen only */
    }

}
