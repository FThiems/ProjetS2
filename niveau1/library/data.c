/**
 * \file data.c
 * \brief Fonctions liées aux données du monde
 */

/**
 * \brief Definitions des constantes, des structures et des includes
 */
#include "definitions.h"

/**** SIGNATURES ****/

/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */
void init_data(world_t* world);

/**
 * \brief La fonction nettoie les données du monde
 * \param world les données du monde
 */
void clean_data(world_t* world);

/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param world les données du monde
 */
void update_data(world_t* world);

/**** FONCTIONS ****/

void init_balls(world_t* world){
  int col = 1, row, nb = 1;
  //Set position of first ball
  set_x(775, nb, world);
  set_y(357, nb, world);
  nb++;
  while(nb <= NB_BALLS){
    row = 0;
    while(nb <= NB_BALLS && row < col){
      set_x( get_x(1, world) + BALL_SIZE * col, nb, world );
      set_y( get_y(1, world) - BALL_SIZE / 2 * col + BALL_SIZE * row, nb, world );
      nb++; 
      row++;
    }
    col++;
  }
  
}

void init_data(world_t* world){
    world->gameover = 0;
    int i;
    
    //Loads sprite images, they need to be freed within clean_data
    world->table = load_image("ressources/table.bmp");
    world->balls_sprite = load_image("ressources/boules.bmp");
    
    //Allocates memory to world->²balls[0]
    world->balls = calloc(NB_BALLS,sizeof(ball_t*));
    for(i = 0; i<NB_BALLS; i++){
      world->balls[i] = calloc(NB_BALLS,sizeof(ball_t**));
    }
    
    //Sets the default postions of balls
    set_x(385,0,world);
    set_y(364,0,world);

    world->balls[0]->vx = 10.;
    world->balls[0]->vy = 20.0;
}



void clean_data(world_t* world){
    int i;
    SDL_FreeSurface(world->table);
    SDL_FreeSurface(world->balls_sprite);
    for(i = 0; i< NB_BALLS; i++){
      free(world->balls[i]);
    }
    free(world->balls);
}


//void move_ball(int vx,int vy, ,world_t* world)

void update_data(world_t* world){
    //Moves balls[0] by it's vectors
    world->balls[0]->x +=  world->balls[0]->vx;
    world->balls[0]->y += world->balls[0]->vy;
    
    
    
    //Bounces off walls  //TODO Add half-vector managments for bounces (cut vector) #####################################
        //Right side
        if (world->balls[0]->x > BORDER_RIGHT)
            world->balls[0]->vx = -1 * fabs(world->balls[0]->vx);
        //Left side
        if (world->balls[0]->x < BORDER_LEFT)
            world->balls[0]->vx = fabs(world->balls[0]->vx);

        
        //Lower side
        if (world->balls[0]->y > BORDER_DOWN)
            world->balls[0]->vy = -1 * fabs(world->balls[0]->vy);
        //Upper side
        if (world->balls[0]->y < BORDER_UP)
            world->balls[0]->vy = fabs(world->balls[0]->vy);
    
    //Slows down
    world->balls[0]->vx *= 0.95;
    world->balls[0]->vy *= 0.95;

}