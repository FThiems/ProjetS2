/**
 * \file events.c
 * \brief Player input event handling
 */


#include "headers/events.h" //Imports and function headers for this file

///// Inputs //////////////////////////////////////////////////////////////
//Handles a mouse intput
void mouse_input(world_t* world){
    int mouseX,mouseY;

    if (!moving_or_not_waiting(world)){ //If still or the notWaiting flag is on
        SDL_GetMouseState(&mouseX,&mouseY);
        //Give the white ball a speed
        world->balls[0]->vx = (mouseX - world->balls[0]->x) *SPEED_COEF;
        world->balls[0]->vy = (mouseY - world->balls[0]->y) *SPEED_COEF;
        //A new turn starts
        world->playerChanged = 0;
    }
}

//Handles keyboard input
void keyboard_input(Uint8* keystates, world_t* world){
    //ghost
    if( keystates[ SDLK_a ] || keystates[ SDLK_g ] )
        world->ghost = (world->ghost +1)%4;                   // Tells if fallen balls should still be active, 1 for bouncy, 2 for showing, 3 for both
    
    //notBouncing
    if( keystates[ SDLK_z ] || keystates[ SDLK_b ] )
        world->notBouncing = (world->notBouncing +1)%2;             // Tells if balls should bounce each other
    
    //funky_overlapp
    if( keystates[ SDLK_e ] || keystates[ SDLK_f ] )
        world->funky_overlapp = (world->funky_overlapp +1)%2; // Attempts to mimic the "funky" overlapping code
    
    //friction
    if( keystates[ SDLK_r ]  )
        world->friction = (world->friction +1)%4;              // Tells which balls should slow down, 0 for all, 1 for white only, 2 for colored only, 3 for none
    world->notWaiting = world->friction;

    //fight
    if( keystates[ SDLK_t ]  )
        world->fight = (world->fight +1)%2;              // Send the ghosts after get_ball(1, world)

    //screen_wrap
    if( keystates[ SDLK_y ]  )
        world->screen_wrap = (world->screen_wrap +1)%2;              // Tells if balls should hit the walls (0) or teleport on the other side (1)

    //black_holes
    if( keystates[ SDLK_u ]  )
        world->black_holes = (world->black_holes+1)%2;              // Balls fall into the holes from further away
        
    //loop delay
    if( keystates[ SDLK_UP ]  )
        world->main_delay *= 2;              // Slower
    if( keystates[ SDLK_DOWN ]  )
        world->main_delay = (int) world->main_delay /2;              // Faster

    //Reset
    if( keystates[ SDLK_i ] || keystates[ SDLK_ESCAPE ]  ){
        init_parameters(world);
        init_white(world);
        init_balls(world);
        init_score(world);
    }
            
    
}

///// Handle events //////////////////////////////////////////////////////////////
//Function called each tic to process player inputs
void handle_events(SDL_Event* event,world_t* world){
    //Input variables
    Uint8* keystates;
    
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
        
        //Keyboard input
        keystates = SDL_GetKeyState( NULL );
        keyboard_input(keystates, world); 
        
    }

}
