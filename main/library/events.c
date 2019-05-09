/**
 * \file events.c
 * \brief Fonctions liées à la gestion des evenements
 */

/**
 * \brief Definitions des constantes, des structures et des includes
 */
#include "headers/definitions.h"

/**** FONCTIONS ****/

void handle_events(SDL_Event* event,world_t* world){
    //Input variables
    int mouseX,mouseY;
    Uint8 *keystates;
    
    while( SDL_PollEvent( event ) ) {
        //If attempt to close
        if( event->type == SDL_QUIT ) {
            //Close
            world->gameover = 1;
        }
        
        //On any mouse button up
        if( event->type == SDL_MOUSEBUTTONUP ){
            //Give the white ball a speed
            SDL_GetMouseState(&mouseX,&mouseY);
            world->balls[0]->vx = (mouseX - world->balls[0]->x) *SPEED_COEF;
            world->balls[0]->vy = (mouseY - world->balls[0]->y) *SPEED_COEF;
        }
        
        keystates = SDL_GetKeyState( NULL );
        
        //Cycle different game modifiers
        if( keystates[ SDLK_a ] || keystates[ SDLK_g ] )
            world->ghost = (world->ghost +1)%4;                   // Tells if fallen balls should still be active, 1 for bouncy, 2 for showing, 3 for both*/
        
        if( keystates[ SDLK_z ] || keystates[ SDLK_b ] )
            world->notBouncing = (world->notBouncing +1)%2;             // Tells if balls should bounce each other */
        if( keystates[ SDLK_e ] || keystates[ SDLK_f ] )
            world->funky_overlapp = (world->funky_overlapp +1)%2; // Attempts to mimic the "funky" overlapping code */
        if( keystates[ SDLK_r ]  )
            world->friction = (world->friction +1)%4;              // Tells which balls should slow down, 0 for all, 1 for white only, 2 for colored only, 3 for fallen only */
    }

}
