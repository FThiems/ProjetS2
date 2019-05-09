/**
 * \file data.c
 * \brief Fonctions liées aux données du monde
 */

/**
 * \brief Definitions des constantes, des structures et des includes
 */
#include "headers/definitions.h"

/**
 * \brief Signatures des fonctions liées aux balles
 */
#include "headers/ball_functions.h"
/**
 * \brief Module de gestion des collisions
 */
#include "collision.c"


;

///// Initialisations //////////////////////////////////////////////////////////////
//! Places the collored balls at the right spot
void init_balls(world_t* world){
    int col = 1, row, nb = 1;

    //Places the white ball
    *get_px(0,world) = 385;
    *get_py(0,world) = 364;
    world->balls[0]->fell = 0;

    //Places the first ball of the triangle
    *get_px(nb,world) = 775;
    *get_py(nb,world) = 357;
    world->balls[nb]->fell = 0;

    nb++; //A ball has been placed
    while(nb < NB_BALLS){
        row = 0;
    while(nb < NB_BALLS && row < col+1){
        world->balls[nb]->fell = 0;
        *get_px(nb, world) = *get_px(1,world) + 0.8661 * BALL_SIZE * col;
        *get_py(nb, world) = *get_py(1, world) - 1.0001*BALL_SIZE / 2 * col + BALL_SIZE * row;
        nb++;
        row++;
    }
    col++;
  }
}

//Initialise le tableau des positions des trous de la table
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

//Initialise les données du monde
void init_data(world_t* world){
    int i;
    
    //Set game parameters
        world->gameover = 0;
        world->main_delay = 10; //100fps
        world->ghost = 0; //No ghost balls
        world->notBouncing = 0; //Balls shall bounce
        world->funky_overlapp = 0; //No funkyness
        world->friction = 0; //Friction for all
        world->friction_multiplier = 0.95;
    

    //Loads sprite images, they need to be freed within clean_data
    world->table = load_image("ressources/table.bmp");
    world->balls_sprite = load_image("ressources/boules.bmp");

    //Allocates memory to world->balls[0]
    world->balls = calloc(NB_BALLS,sizeof(ball_t*));
    for(i = 0; i<NB_BALLS; i++){
      world->balls[i] = calloc(NB_BALLS,sizeof(ball_t**));
    }

    //Allocation de la mémoire pour le tableau des trous
    world->holes = calloc(NB_HOLES, sizeof(holes_t*));
    for(i = 0; i<NB_HOLES; i++){
      world->holes[i] = calloc(NB_HOLES, sizeof(holes_t**));
    }


    //Places the balls at the right spot
    init_balls(world);

    //Initialise les trous dans le tableau
    init_holes(world);
}




///// Hole functions //////////////////////////////////////////////////////////////
//Distance euclidienne entre le centre de la balle et le centre du trou
int dist_ball_hole(world_t* world, int ball_number, int hole_number){
  return sqrt( (world->balls[ball_number]->x - world->holes[hole_number]->x) * (world->balls[ball_number]->x - world->holes[hole_number]->x)
           + ( (world->balls[ball_number]->y - world->holes[hole_number]->y) * (world->balls[ball_number]->y - world->holes[hole_number]->y) ) );
}


//Fonction qui teste si la ball_t doit rentrer dans le trou ou pas
bool is_falling(world_t* world, int ball_number, int hole_number){
  return(dist_ball_hole(world, ball_number, hole_number) < BALL_SIZE/2 + HOLE_RADIUS);
}


//fonction qui test à chaque fin de update data si des boules doivent tomber ou non
void all_holes(world_t* world){
  int ball_number, hole_number, i, j;

  for (i = 0; i<NB_BALLS; i++){
    for (j = 0; j<NB_HOLES; j++){
      if (is_falling(world, i, j)){
        world->balls[i]->fell = 1;
      }
    }
  }
}




///// Clean function //////////////////////////////////////////////////////////////
void clean_data(world_t* world){
    int i;
    SDL_FreeSurface(world->table);
    SDL_FreeSurface(world->balls_sprite);
    //free du tableau des boules
    for(i = 0; i< NB_BALLS; i++){
      free(world->balls[i]);
    }
    free(world->balls);
    //free du tableau des trous
    for(i = 0; i < 6; i++){
      free(world->holes[i]);
    }
    free(world->holes);
}




///// Movement functions //////////////////////////////////////////////////////////////
//!Bounce off walls
void wall_bounce(int ball_number, world_t* world){
    ball_t *current = get_ball(ball_number,world);
    
    
    //Right side
    if (current->x > BORDER_RIGHT){
        current->vx = -1 * fabs(current->vx);
        current->vRemainingX = -1 * fabs(current->vRemainingX);
    }
    //Left side
    if (current->x < BORDER_LEFT){
        current->vx = fabs(current->vx);
        current->vRemainingX = fabs(current->vRemainingX);
    }
    //Lower side + condition pour le trou du bas
    if (current->y > BORDER_DOWN && (current->x < LEFT || current->x > RIGHT)){
        current->vy = -1 * fabs(current->vy);
        current->vRemainingY = -1 * fabs(current->vRemainingY);
    }
    //Upper side + condition pour le trou du haut
    if (current->y < BORDER_UP && (current->x < LEFT || current->x > RIGHT)){
        current->vy = fabs(current->vy);
        current->vRemainingY = fabs(current->vRemainingY);
    }
}

//!Bounce off other balls
void ball_bounce(int ball_number, int watched_ball_number, world_t* world){
    double distance_x, distance_y, distance_xy;
    double overlapped_x, overlapped_y;
    ball_t *current,*watched;
    
    
    //Get ball's pointers
    current = get_ball(ball_number,world);
    watched = get_ball(watched_ball_number,world);

    //Calculates distances between ball and watched ball
    distance_x = current->x - watched->x;
    distance_y = current->y - watched->y;
    distance_xy = sqrt(distance_x * distance_x + distance_y * distance_y);
    
    //Check collision
    if (distance_xy < BALL_SIZE){
        //Funky_overlapp modifier activated?
        if (!world->funky_overlapp){ //Not activated
            //Retreat to not overlap
                //Calculates wanted separating vector between the two balls
                overlapped_x = distance_x / distance_xy * BALL_SIZE;
                overlapped_y = distance_y / distance_xy * BALL_SIZE;
                
                
                //Move backward
                current->x +=  overlapped_x-distance_x;
                current->y +=  overlapped_y-distance_y;
                
                //Re-add the distance to the remaining vector
                current->vRemainingX -= overlapped_x-distance_x;
                current->vRemainingY -= overlapped_y-distance_y;
        }
        else { //Funky_overlapp modifier activated
            overlapped_x = distance_x / distance_xy;
            overlapped_y = distance_y / distance_xy;
            
            current->x -= overlapped_x;
            current->vRemainingX += overlapped_x;
            
            current->y -= overlapped_y;
            current->vRemainingY += overlapped_y;
            
        }
        
        //Actual ball bouncing
        if (!world->notBouncing){
            collision(current->x,current->y,&(current->vx),&(current->vy),watched->x,watched->y,&(watched->vx),&(watched->vy));
            collision(current->x,current->y,&(current->vRemainingX),&(current->vRemainingY),watched->x,watched->y,&(watched->vRemainingX),&(watched->vRemainingY));
        }
        
    }
}

//!Moves ball by tiny vectors until they travelled their respective remaining vx/vy, checks bounces
void baby_loop(int remaining_baby_steps, world_t* world){
    ball_t *current,*watched;
    int ball_number, watched_ball_number;
    
    //Small movements loop
    while (remaining_baby_steps >1){
        remaining_baby_steps--;

        //For each ball
        for (ball_number = 0; ball_number < NB_BALLS; ball_number++){
            //Get current ball's pointer
            current = get_ball(ball_number,world);

            //Moves balls[ball_number] by it's vectors
            current->x += current->vRemainingX / remaining_baby_steps;
            current->y += current->vRemainingY / remaining_baby_steps;
            
            //Removes moved distance
            current->vRemainingX -= current->vRemainingX / remaining_baby_steps;
            current->vRemainingY -= current->vRemainingY / remaining_baby_steps;

            //!Bounce off walls
            wall_bounce(ball_number,world);

            //Bounce off other balls
            for (watched_ball_number = 0; watched_ball_number < NB_BALLS; watched_ball_number++){
                watched = get_ball(watched_ball_number,world);
                
                if (watched_ball_number!=ball_number) //no self-colisions
                    if ((!watched->fell && !current->fell) || world->ghost==1 || world->ghost==3) //if not an fallen ball, or if ghost mode is on
                        ball_bounce( ball_number, watched_ball_number, world);
            }
        }
        //On regarde quelles boules tombent
        all_holes(world);

    }
    //fin while
}

//!Slows ball by world->friction_multiplier
void friction_ball(ball_t* current,world_t* world){
    //multiplication
    current->vx *= world->friction_multiplier;
    current->vy *= world->friction_multiplier;
        
    //Set to 0 if really small, to fasten up immobilisation
    if( fabs(current->vx)  <0.1)
        current->vx =0;
    if( fabs(current->vy)  <0.1)
        current->vy = 0;
}

//!Slows the right balls by world->friction_multiplier
void friction(world_t* world){
    // world->friction tells which balls should slow down, 0 for all, 1 for white only, 2 for colored only, 3 for fallen only */
    
    //Variables
    int ball_number; //Index of the current ball worked on
    

    //White ball friction
    if (world->friction == 0 || world->friction == 1)
        friction_ball(get_ball(0,world) ,world);
    
    
    //Colored balls friction
    if (world->friction == 0 || world->friction == 2){
        for (ball_number = 1; ball_number < NB_BALLS; ball_number++){
            friction_ball( get_ball(ball_number,world) ,world);
        }
    }
    
    //Fallen balls friction
    if (world->friction == 3){
        for (ball_number = 0; ball_number < NB_BALLS; ball_number++){
            if ( get_ball(ball_number,world)->fell )
                friction_ball( get_ball(ball_number,world) ,world);
        }
    }
}




///// Update Data //////////////////////////////////////////////////////////////
void update_data(world_t* world){
    double highest_speed = 0, calculated_speed;
    int ball_number;
    int total_baby_steps;
    
    //Sets all the balls' Remaining vx and vy to their vx and vy values
    for (ball_number = 0; ball_number < NB_BALLS; ball_number++){
        *get_p_Remaining_vx(ball_number,world) = *get_pvx(ball_number,world);
        *get_p_Remaining_vy(ball_number,world) = *get_pvy(ball_number,world);

        calculated_speed = sqrt( *get_pvx(ball_number,world) * *get_pvx(ball_number,world) + *get_pvy(ball_number,world) * *get_pvy(ball_number,world) );
        if (calculated_speed > highest_speed)
            highest_speed = calculated_speed;
    }

    //Every step needs to be the same for a ball, and smaller than (BALL_SIZE/2) (radius)
    total_baby_steps = (int) highest_speed % (BALL_SIZE/2) +2;

    
    //Moves ball by tiny vectors until they travelled their respective remaining vx/vy, checks bounces
    baby_loop(total_baby_steps, world);


    //Slows down
    friction(world);

}











