/**
 * \file graphics.c
 * \brief Display functions
 */


#include "headers/graphics.h" //Imports and function headers for this file



///// Initialisation //////////////////////////////////////////////////////////////
//Sets the different images transparency values
void  init_graphics(SDL_Surface* screen, world_t* world){
    //Modifiers
    set_transparence(screen,world->balls_sprite,255,0,255);
    set_transparence(screen, world->text_funky_overlapp, 204, 0, 204);
    set_transparence(screen, world->text_notBouncing, 204, 0, 204);
    set_transparence(screen, world->text_ghost, 204, 0, 204);
    set_transparence(screen, world->text_friction, 204, 0, 204);

    //Numbers
    set_transparence(screen, world->text_numbers0, 204, 0, 204);
    set_transparence(screen, world->text_numbers1, 204, 0, 204);

    //Active player
    set_transparence(screen, world->text_player, 204, 0, 204);
}




///// Element displays //////////////////////////////////////////////////////////////
//Displays every ball_t on the table
void refresh_balls(SDL_Surface* screen, world_t* world){
    int ball_number,on_screen_x,on_screen_y;
    ball_t* current;

    
    ball_number = world->bottom_ball;
    current = get_ball(ball_number, world);

    //First ball
    if(!current->fell || world->ghost>=2){ //is displayable
            //Calculate render position
            on_screen_x = current->x-BALL_SIZE/2;
            on_screen_y = current->y-BALL_SIZE/2;

            //Paints the ball_t
            apply_sub_surface(world->balls_sprite,screen,ball_number*BALL_SIZE,0,BALL_SIZE,BALL_SIZE, on_screen_x, on_screen_y);
    }
    
    for (ball_number = (world->bottom_ball+1)%NB_BALLS; ball_number != world->bottom_ball; ball_number= (ball_number+1)%NB_BALLS){ //for each other ball, starting at next one
        current = get_ball(ball_number, world);
        if(!world->balls[ball_number]->fell || world->ghost>=2){ //is displayable
            //Calculate render position
            on_screen_x = current->x-BALL_SIZE/2;
            on_screen_y = current->y-BALL_SIZE/2;

            //Paints the ball_t
            apply_sub_surface(world->balls_sprite,screen,ball_number*BALL_SIZE,0,BALL_SIZE,BALL_SIZE, on_screen_x, on_screen_y);
        }
    }
}

//Displays game modifiers
void refresh_modifiers(SDL_Surface* screen, world_t* world){
    int maxStates; //don't create an sdl error by fetching things outside the image

    int width = 108; //Text width
    int height = 28; //Text height

    int inImageX = 0; //Position within world->text_ ...
    int on_screen_y = 693;


    apply_sub_surface(world->text_ghost         , screen, inImageX, /*in image y*/((world->ghost)         %maxStates)*height, width, height, /* on screen x*/ 240, on_screen_y);
    apply_sub_surface(world->text_notBouncing   , screen, inImageX, /*in image y*/((world->notBouncing)   %maxStates)*height, width, height, /* on screen x*/ 400, on_screen_y);
    apply_sub_surface(world->text_funky_overlapp, screen, inImageX, /*in image y*/((world->funky_overlapp)%maxStates)*height, width, height, /* on screen x*/ 800, on_screen_y-10);
    apply_sub_surface(world->text_friction      , screen, inImageX, /*in image y*/((world->friction)      %maxStates)*height, width, height, /* on screen x*/ 950, on_screen_y);

    //Player points
    maxStates = 62;
    width = 22;
    height = 56;
    int inImageY = 0;
    on_screen_y = 8;


    apply_sub_surface(world->text_numbers0      , screen, /*in image x*/((world->p0) %maxStates)*width, inImageY , width, height, /* on screen x*/ 108, on_screen_y);
    apply_sub_surface(world->text_numbers1      , screen, /*in image x*/((world->p1) %maxStates)*width, inImageY , width, height, /* on screen x*/ 1105, on_screen_y);

    //Active player display
    maxStates = 2;
    width = 44;
    int on_screen_x = (int) SCREEN_WIDTH/2- width/2 /*(center)*/ +(width*1.5* (world->active_player*2-1)) ;
    apply_sub_surface(world->text_player      , screen, /*in image x */((world->active_player) %maxStates)*width, inImageY , width, height, on_screen_x, on_screen_y);
}




///// Refresh Graphics //////////////////////////////////////////////////////////////
//Function called each tic to process display output
void refresh_graphics(SDL_Surface* screen, world_t* world){
    //Paints the table
    apply_surface(world->table,screen,0,0);

    //Displays every ball_t on the table
    refresh_balls(screen, world);
    
    //!Displays game modifiers
    refresh_modifiers(screen, world);

    refresh_surface(screen);
}
