/**
 * \file data.c
 * \brief Fonctions liées aux données du monde
 */

/**
 * \brief Definitions des constantes, des structures et des includes
 */
#include "definitions.h"

/**
 * \brief Fonctions liées aux balles
 */
#include "ball_functions.c"

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

//! Places the collored balls at the right spot
void init_balls(world_t* world){
  int col = 1, row, nb = 1;
  //Set position of first ball
  *get_px(nb,world) = 775;
  *get_py(nb,world) = 357;
  nb++; //A ball has been placed
  while(nb < NB_BALLS){
    row = 0;
    while(nb < NB_BALLS && row < col+1){
      *get_px(nb, world) = *get_px(1,world) + BALL_SIZE * col;
      *get_py(nb, world) = *get_py(1, world) - BALL_SIZE / 2 * col + BALL_SIZE * row;
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
    
    //Sets the default positions of balls
    *get_px(0,world) = 385;
    *get_py(0,world) = 364;
    
    //Places the collored balls at the right spot
    init_balls(world);
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



void update_data(world_t* world){
    double *px, *py, *pvx, *pvy, *prvx, *prvy;
    double highest_speed = 0, temp;
    
    int ball_number,remaining_baby_steps,total_baby_steps;
    //Sets all the balls' Remaining vx and vy to their vx and vy values
    for (ball_number = 0; ball_number < NB_BALLS; ball_number++){
        *get_p_Remaining_vx(ball_number,world) = *get_pvx(ball_number,world);
        *get_p_Remaining_vy(ball_number,world) = *get_pvy(ball_number,world);
        
        temp = sqrt( *get_pvx(ball_number,world) * *get_pvx(ball_number,world) + *get_pvy(ball_number,world) * *get_pvy(ball_number,world) );
        if (temp > highest_speed)
            highest_speed = temp;
    }
    
    //Every needs to be the same for a ball, and smaller than (BALL_SIZE/2) (radius)
    total_baby_steps = (int) highest_speed / (BALL_SIZE/2) +1;
    remaining_baby_steps = total_baby_steps;
    
    //Small movements loop
    while (remaining_baby_steps !=0){
        remaining_baby_steps--;
        
        for (ball_number = 0; ball_number < NB_BALLS; ball_number++){
            //Get current ball's pointers
            px = get_px(ball_number,world);
            py = get_py(ball_number,world);
            prvx = get_prvx(ball_number,world);
            prvy = get_prvy(ball_number,world);
            
            //Moves balls[ball_number] by it's vectors
            *px+=*prvx / total_baby_steps;
            *py+=*prvy / total_baby_steps;
            
            //Removes moved distance
            *prvx -= *prvx / total_baby_steps;
            *prvy -= *prvy / total_baby_steps;
        
            
            //Bounces off walls  //TODO Add half-vector managments for bounces (cut vector) #####################################
                //Right side
                if (*px > BORDER_RIGHT)
                    *pvx = -1 * fabs(*pvx);
                //Left side
                if (*px < BORDER_LEFT)
                    *pvx = fabs(*pvx);

                
                //Lower side
                if (*py > BORDER_DOWN)
                    *pvy = -1 * fabs(*pvy);
                //Upper side
                if (world->balls[0]->y < BORDER_UP)
                    world->balls[0]->vy = fabs(world->balls[0]->vy);
                } //FIXME
        
    }

    

    
    //Slows down
    world->balls[0]->vx *= 0.95;
    world->balls[0]->vy *= 0.95;

}



















