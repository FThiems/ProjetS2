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
      *get_px(nb, world) = *get_px(1,world) + 0.8661 * BALL_SIZE * col;
      *get_py(nb, world) = *get_py(1, world) - 1.0001*BALL_SIZE / 2 * col + BALL_SIZE * row;
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

    //Allocates memory to world->balls[0]
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
    //int i;
    //SDL_FreeSurface(world->table);
    //SDL_FreeSurface(world->balls_sprite);
    /*for(i = 0; i< NB_BALLS; i++){
      free(world->balls[i]);
    }
    free(world->balls);*/
}



void update_data(world_t* world){
    double *px, *py, *pvx, *pvy, *prvx, *prvy; //p = pointer, v = velocity, r = remaining
    double *pwx, *pwy, *pwvx, *pwvy, *pwrvx, *pwrvy; //w = watched
    double distance_x, distance_y, distance_xy;
    double overlapped_x, overlapped_y;
    double highest_speed = 0, calculated_speed;

    int ball_number, watched_ball_number;

    int remaining_baby_steps,total_baby_steps;

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
    remaining_baby_steps = total_baby_steps;
    printf("%i\n",total_baby_steps);

    //Small movements loop
    while (remaining_baby_steps >0){
        remaining_baby_steps--;

        //For each ball
        for (ball_number = 0; ball_number < NB_BALLS; ball_number++){
            //Get current ball's pointers
            px = get_px(ball_number,world);
            py = get_py(ball_number,world);
            pvx = get_pvx(ball_number,world);
            pvy = get_pvy(ball_number,world);
            prvx = get_p_Remaining_vx(ball_number,world);
            prvy = get_p_Remaining_vy(ball_number,world);

            // if is moving
            if (*prvx || *prvy){

                //Moves balls[ball_number] by it's vectors
                *px += *prvx / remaining_baby_steps;
                *py += *prvy / remaining_baby_steps;

                //Removes moved distance
                *prvx -= *prvx / remaining_baby_steps;
                *prvy -= *prvy / remaining_baby_steps;


                //Bounce off walls
                    //Right side
                    if (*px > BORDER_RIGHT){
                        *pvx = -1 * fabs(*pvx);
                        *prvx = -1 * fabs(*prvx);
                    }
                    //Left side
                    if (*px < BORDER_LEFT){
                        *pvx = fabs(*pvx);
                        *prvx = fabs(*prvx);
                    }

                    //Lower side
                    if (*py > BORDER_DOWN){
                        *pvy = -1 * fabs(*pvy);
                        *prvy = -1 * fabs(*prvy);
                    }
                    //Upper side
                    if (*py < BORDER_UP){
                        *pvy = fabs(*pvy);
                        *prvy = fabs(*prvy);
                    }


                //Bounce off other balls

                    for (watched_ball_number = ball_number+1; watched_ball_number < NB_BALLS; watched_ball_number++){
                        //Get current ball's pointers
                        pwx = get_px(watched_ball_number,world);
                        pwy = get_py(watched_ball_number,world);
                        pwvx = get_pvx(watched_ball_number,world);
                        pwvy = get_pvy(watched_ball_number,world);
                        pwrvx = get_p_Remaining_vx(watched_ball_number,world);
                        pwrvy = get_p_Remaining_vy(watched_ball_number,world);

                        //Distances between ball and watched ball
                        distance_x = *px - *pwx;
                        distance_y = *py - *pwy;
                        distance_xy = sqrt(distance_x * distance_x + distance_y * distance_y);

                        //Check collision
                        if (distance_xy < BALL_SIZE){
                            //Retreat to not overlap
                            overlapped_x = distance_x / distance_xy * BALL_SIZE;
                            overlapped_y = distance_y / distance_xy * BALL_SIZE;

                            *px = *pwx - overlapped_x;
//                             *prvx += overlapped_x;

                            *py = *pwy - overlapped_y;
//                             *prvy += overlapped_y;

                            //if colliding with moving ball //TODO
                            if (*pwvx || *pwvy){

                            }
                            else { //if still
                                //TODO make copy!! best code ever!!
                                //btw, there is a colision from the top right corner
                                 //*pwrvx = *prvx/2;
                                 //*pwvx = *pwrvx;
                                 //*pwrvy = *prvy/2;
                                 //*pwvy = *pwrvy;

                                 //*pvx = -1 * *pwrvx ;
                                 //*pvy = *pwrvy *-1;


                            }
                        }
                    }
            }//end if is moving
        }

    }




    //Slows down
    world->balls[0]->vx *= 0.95;
    world->balls[0]->vy *= 0.95;

}
