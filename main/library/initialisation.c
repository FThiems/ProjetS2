/**
 * \file initialisation.c
 * \brief Initialisations of different components
 */


#include "headers/initialisation.h" //Imports and function headers for this file

//Sets world's parameters
void init_parameters(world_t* world){
    world->gameover = 0; //do start the game
    world->bottom_ball= time(NULL) % NB_BALLS; //chosen at random
    world->active_player=0; //Player 0 is starting...
    world->playerChanged=1; //... for real
    world->main_delay = 10; //100fps

    //Game modifiers
    world->ghost = 0; //No ghost balls
    world->notBouncing = 0; //Balls shall bounce
    world->funky_overlapp = 0; //No funkyness
    world->friction = 0; //Friction for all
    world->friction_multiplier = 0.95;
    world->notWaiting = 0; //Do wait between shots
    world->fight = 0; //Don't unleach the ghosts right away
    world->screen_wrap = 0; //Bounce of walls
    world->black_holes = 0; //Use normal distances
    world->exchange = 0; //Dont swap balls
}

//Places the white ball
void init_white(world_t* world){
    ball_t *current = get_ball(0,world);

    current->x = 385;
    current->y = 364;
    current->vx = 0;
    current->vy = 0;
    current->vRemainingX = 0;
    current->vRemainingY = 0;
    current->fell = 0;
}

//Places all balls at the right spot
void init_balls(world_t* world){
    int col = 1, row, nb = 1;
    ball_t *current, *first;

    //Place the white ball
    init_white(world);


    //Triangle creation
        //Places the first ball of the triangle
        current = get_ball(nb, world);
        current->x = 775;
        current->y = 357;
        current->fell = 0;

        first= current; //Store the first ball placed


        nb++; //A ball has been placed

        while(nb < NB_BALLS){ //While there are balls remaining to be placed
            row = 0;
            while(nb < NB_BALLS && row < col+1){
                current = get_ball(nb, world);

                current->x = first->x + 0.8661 * BALL_SIZE * col;
                current->y = first->y - 1.0001*BALL_SIZE / 2 * col + BALL_SIZE * row;
                current->fell = 0;

                nb++;
                row++;
            }
            col++;
        }
}

//Places holes
void init_holes(world_t* world){
  world->holes[0]->x = 75;
  world->holes[0]->y = 75;
  world->holes[1]->x = 644;
  world->holes[1]->y = 40;
  world->holes[2]->x = 1213;
  world->holes[2]->y = 75;
  world->holes[3]->x = 1213;
  world->holes[3]->y = 650;
  world->holes[4]->x = 644;
  world->holes[4]->y = 685;
  world->holes[5]->x = 75;
  world->holes[5]->y = 650;
}

//Loads all game images
void init_sdl_surfaces(world_t* world){
  //Loads sprite images, they need to be freed within clean_data
    //Modifiers
    world->table = load_image("ressources/table.bmp");
    world->balls_sprite = load_image("ressources/boules.bmp");
    world->text_ghost = load_image("ressources/Ghost.bmp");
    world->text_notBouncing = load_image("ressources/Bouncy.bmp");
    world->text_funky_overlapp = load_image("ressources/Funky.bmp");
    world->text_friction = load_image("ressources/Friction.bmp");

    //Numbers
    world->text_numbers0 = load_image("ressources/numb.bmp");
    world->text_numbers1 = load_image("ressources/numb1.bmp");

    //Active player
    world->text_player = load_image("ressources/player.bmp");
}

//Initialises the players scores
void init_score(world_t* world){
    world->p0 = 0;
    world->p1 = 0;
    world->pointsBuffer = 0;
}

