/**
 * \file graphics.c
 * \brief Fonctions liées aux éléments graphiques du jeu
 */

/**
 * \brief Definitions des constantes, des structures et des includes
 */
#include "headers/definitions.h"
/**
 * \brief Fonctions liées aux balles
 */
#include "headers/ball_functions.h"


/**** FONCTIONS ****/

void  init_graphics(SDL_Surface* screen, world_t* world){
    set_transparence(screen,world->balls_sprite,255,0,255);
    set_transparence(screen, world->text_funky_overlapp, 204, 0, 204);
    set_transparence(screen, world->text_notBouncing, 204, 0, 204);
    set_transparence(screen, world->text_ghost, 204, 0, 204);
    set_transparence(screen, world->text_friction, 204, 0, 204);
}

void refresh_graphics(SDL_Surface* screen, world_t* world){
    apply_surface(world->table,screen,0,0);

    int ball_number,on_screen_x,on_screen_y;
    for (ball_number = 0; ball_number < NB_BALLS; ball_number++){
        on_screen_x = *get_px(ball_number,world)-BALL_SIZE/2;
        on_screen_y = *get_py(ball_number,world)-BALL_SIZE/2;
        if(!world->balls[ball_number]->fell || world->ghost>=2){
          apply_sub_surface(world->balls_sprite,screen,ball_number*BALL_SIZE,0,BALL_SIZE,BALL_SIZE, on_screen_x, on_screen_y);
        }
    }
    
     //Game modifiers display
     apply_sub_surface(world->text_ghost,screen,0,((world->ghost)%6)*29,108,29, 240, 693);
     apply_sub_surface(world->text_notBouncing,screen,0,((world->notBouncing)%6)*29,108,29, 400, 693);
     apply_sub_surface(world->text_funky_overlapp,screen,0,((world->funky_overlapp)%6)*29,108,29, 800, 686);
     apply_sub_surface(world->text_friction,screen,0,((world->friction)%6)*29,108,29, 950, 693);
    refresh_surface(screen);
}
