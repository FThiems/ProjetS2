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
    int mouseX,mouseY;
    while( SDL_PollEvent( event ) ) {
        //Si l'utilisateur a cliqué sur le X de la fenêtre
        if( event->type == SDL_QUIT ) {
            //On quitte le programme
            world->gameover = 1;
        }

        if( event->type == SDL_MOUSEBUTTONUP ){
            SDL_GetMouseState(&mouseX,&mouseY);
            world->balls[0]->vx = (mouseX - world->balls[0]->x) *SPEED_COEF;
            world->balls[0]->vy = (mouseY - world->balls[0]->y) *SPEED_COEF;
        }

//         if( event->type == SDL_KEY_UP )
//             printf("\n");
    }

}
