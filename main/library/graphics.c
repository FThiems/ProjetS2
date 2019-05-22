/**
 * \file graphics.c
 * \brief Display functions
 */

/**
 * \brief Imports and function headers for this file
 */
#include "headers/graphics.h"



///// Initialisation //////////////////////////////////////////////////////////////
//!Sets the different images transparency values
void  init_graphics(SDL_Surface* screen, world_t* world){
    set_transparence(screen,world->balls_sprite,255,0,255);
    set_transparence(screen, world->text_funky_overlapp, 204, 0, 204);
    set_transparence(screen, world->text_notBouncing, 204, 0, 204);
    set_transparence(screen, world->text_ghost, 204, 0, 204);
    set_transparence(screen, world->text_friction, 204, 0, 204);
    set_transparence(screen, world->text_numbers0, 204, 0, 204);
    set_transparence(screen, world->text_numbers1, 204, 0, 204);
}




///// Element displays //////////////////////////////////////////////////////////////
//!Displays every ball_t on the table
void refresh_balls(SDL_Surface* screen, world_t* world){
    int ball_number,on_screen_x,on_screen_y;

    for (ball_number = 0; ball_number < NB_BALLS; ball_number++){ //for each ball
        if(!world->balls[ball_number]->fell || world->ghost>=2){ //is displayable
            //Calculate render position
            on_screen_x = *get_px(ball_number,world)-BALL_SIZE/2;
            on_screen_y = *get_py(ball_number,world)-BALL_SIZE/2;

            //Paints the ball_t
            apply_sub_surface(world->balls_sprite,screen,ball_number*BALL_SIZE,0,BALL_SIZE,BALL_SIZE, on_screen_x, on_screen_y);
        }
    }
}

//!Displays game modifiers
void refresh_modifiers(SDL_Surface* screen, world_t* world){
    int maxStates; //don't create an sdl error by fetching things outside the image

    int width = 108; //!Text width
    int height = 28; //!Text height

    int inImageX = 0; //!Position within world->text_ ...
    int on_screen_y = 693;


    apply_sub_surface(world->text_ghost         , screen, inImageX, /*in image y*/((world->ghost)         %maxStates)*height, width, height, 240, on_screen_y);
    apply_sub_surface(world->text_notBouncing   , screen, inImageX, /*in image y*/((world->notBouncing)   %maxStates)*height, width, height, 400, on_screen_y);
    apply_sub_surface(world->text_funky_overlapp, screen, inImageX, /*in image y*/((world->funky_overlapp)%maxStates)*height, width, height, 800, on_screen_y-10);
    apply_sub_surface(world->text_friction      , screen, inImageX, /*in image y*/((world->friction)      %maxStates)*height, width, height, 950, on_screen_y);

    width = 22;
    height = 56;
    int inImageY = 0;
    on_screen_y = 8;
    maxStates = 62;

    apply_sub_surface(world->text_numbers0      , screen, /*in image x*/((world->p0)      %maxStates)*width, inImageY , width, height, 108, on_screen_y);
    apply_sub_surface(world->text_numbers1      , screen, /*in image x*/((world->p1)      %maxStates)*width, inImageY , width, height, 1105, on_screen_y);
}




///// Refresh Graphics //////////////////////////////////////////////////////////////
//!Function called each tic to process display output
void refresh_graphics(SDL_Surface* screen, world_t* world){
    //Paints the table
    apply_surface(world->table,screen,0,0);

    //Displays every ball_t on the table
    refresh_balls(screen, world);
    
    //!Displays game modifiers
    refresh_modifiers(screen, world);

    refresh_surface(screen);
}
