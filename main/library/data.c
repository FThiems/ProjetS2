/**
 * \file data.c
 * \brief World editing functions
 */


#include "headers/data.h" //Imports and function headers for this file

//Initializes all of world's fields
void init_data(world_t* world){
    int i;

    //Allocates memory to world->balls[0]
    world->balls = calloc(NB_BALLS,sizeof(ball_t*));
    for(i = 0; i<NB_BALLS; i++){
      world->balls[i] = calloc(1,sizeof(ball_t));
    }

    //Allocation de la mémoire pour le tableau des trous
    world->holes = calloc(NB_HOLES, sizeof(holes_t*));
    for(i = 0; i<NB_HOLES; i++){
      world->holes[i] = calloc(1, sizeof(holes_t));
    }

    //Set world's parameters
    init_parameters(world);

    //Load all game images
    init_sdl_surfaces(world);

    //Place all balls at the right spot
    init_balls(world);

    //Place holes
    init_holes(world);

    //Init score
    init_score(world);
}




///// Hole functions //////////////////////////////////////////////////////////////
//Calculates the distance between the corresponding ball and hole s
int dist_ball_hole(world_t* world, int ball_number, int hole_number){
  return sqrt( (world->balls[ball_number]->x - world->holes[hole_number]->x) * (world->balls[ball_number]->x - world->holes[hole_number]->x)
           + ( (world->balls[ball_number]->y - world->holes[hole_number]->y) * (world->balls[ball_number]->y - world->holes[hole_number]->y) ) );
}


//Function checking if the corresponding ball should fall in the hole or not
bool is_falling(world_t* world, int ball_number, int hole_number){
    if(!(world->balls[ball_number]->fell)){
        return(dist_ball_hole(world, ball_number, hole_number) < BALL_SIZE/2 + HOLE_RADIUS);
    }
}


//Function checking if any ball should fall in any hole and making them fall
void all_holes(world_t* world){
  int ball_number, hole_number;
  ball_t* current;

    for (ball_number = 0; ball_number<NB_BALLS; ball_number++){ //For each ball
        for (hole_number = 0; hole_number<NB_HOLES; hole_number++){ //For each hole
            
            //Regular hole physics
            if (is_falling(world, ball_number, hole_number)){ //If in the hole
                current = get_ball(ball_number,world); //Retrieve pointer
                current->fell = 1;
                
                //Imobilize ball
                current->vx=0;
                current->vy=0;
                current->vRemainingX=0;
                current->vRemainingY=0;
                if (!world->playerChanged){
                scoring(world, ball_number);}
            }
            
            //Black holes modifier handling
            if (world->black_holes){ //If black_holes mod activated
                if (dist_ball_hole(world, ball_number, hole_number) < BALL_SIZE *3){ //If close enough
                    if (dist_ball_hole(world, ball_number, hole_number) > BALL_SIZE){ //But not too much
                        current = get_ball(ball_number,world); //Retrieve pointer
                        if (!current->fell || world->ghost){ //if not fallen, unless ghost
                            target(world->holes[hole_number]->x, world->holes[hole_number]->y, current); //Fall into the hole
                            
                        }
                    }
                    
                }
            }
        }
    }
  

}

//Adds the fallen ball's points to the turn point buffer
void scoring(world_t* world, int ball_number){
    world->pointsBuffer += ball_number;
    if (!ball_number) //White ball penalty
        world->pointsBuffer += 7;
}

//Transfers the content of the point buffer when the turn is over
void pointsTransfer(world_t* world){
    if((world->balls[0]->fell + world->active_player)%2){
        world->p1 += world->pointsBuffer;
    }
    else{
        world->p0 += world->pointsBuffer;
    }
    world->pointsBuffer = 0;
}



///// Clean function //////////////////////////////////////////////////////////////
//Cleans all mallocs and callocs
void clean_data(world_t* world){
    int i;
    SDL_FreeSurface(world->table);
    SDL_FreeSurface(world->balls_sprite);

    SDL_FreeSurface(world->text_numbers0);
    SDL_FreeSurface(world->text_numbers1);
    SDL_FreeSurface(world->text_player);
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
    
    SDL_FreeSurface(world->text_notBouncing);
    SDL_FreeSurface(world->text_friction);
    SDL_FreeSurface(world->text_ghost);
    SDL_FreeSurface(world->text_funky_overlapp);
}




///// Movement functions //////////////////////////////////////////////////////////////
//Ghost tic
void ghost_attack(world_t* world){
    if (!world->fight)
        return;
    
    //Fighting on
    world->screen_wrap=1;
    
    ball_t* pacman = get_ball(1, world);


    //Blinky move toward pacman
    ball_t* Blinky = get_ball(3,world);
    target(pacman->x, pacman->y, Blinky);

    //Pinky move to the front
    ball_t* Pinky = get_ball(11,world);
    target(pacman->x + pacman->vx*5 +BALL_SIZE, pacman->y + pacman->vy*5 + BALL_SIZE, Pinky);

    //Inky move...
    ball_t* Inky = get_ball(10,world);
    target(pacman->x + pacman->vx  + Blinky->x -pacman->x,
        pacman->y + pacman->vy  + Inky->y -pacman->y,
        Inky);

    //Clyde does... yeah...
    ball_t* Clyde = get_ball(5,world);
    if (distance(pacman, Clyde) > BALL_SIZE*5){
        target(pacman->x,pacman->y,Clyde);
    }
    else {
        flee(pacman->x,pacman->y,Clyde);
    }



    //pacman
        ball_t* white = get_ball(0,world);
        //AI
        if (distance(pacman, Blinky) < 6*BALL_SIZE)
            flee(Blinky->x,Blinky->y,pacman);
        else{
            target(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,pacman);
        }
        if (distance(pacman, Pinky) < 6*BALL_SIZE)
            flee(Pinky->x,Pinky->y,pacman);
        else{
            target(SCREEN_WIDTH/2,SCREEN_HEIGHT/2,pacman);
        }
        if (distance(pacman, Inky) < 6*BALL_SIZE)
            flee(Inky->x,Inky->y,pacman);
        else{
            target(white->x,white->y,pacman);
        }
        if (distance(pacman, Clyde) < 6*BALL_SIZE)
            flee(Clyde->x,Clyde->y,pacman);
        else{
            target(Clyde->x,Clyde->y,pacman);
        }


}

//Bounce off walls
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

    //Lower side + mid hole
    if ( (current->y > (BORDER_DOWN + HOLE_RADIUS)) //if way too far down
        || //or if just too far away
        (
            (current->y > (BORDER_DOWN + 0))
            && (current->x < LEFT || current->x > RIGHT) //but not in the middle
        )
    )
    {   //go up
        current->vy = -1 * fabs(current->vy);
        current->vRemainingY = -1 * fabs(current->vRemainingY);
    }

    //Upper side + mid hole
    if ( (current->y < (BORDER_UP - HOLE_RADIUS)) //if way too far up
        || //or if just too far away
        (
            (current->x < LEFT || current->x > RIGHT) //but not in the middle
            && (current->y < (BORDER_UP - 0))
        )
    )
    {   //go down
        current->vy = fabs(current->vy);
        current->vRemainingY = fabs(current->vRemainingY);
    }
}

//Screen wrap
void screen_wrap(int ball_number, world_t* world){
    ball_t* current = get_ball(ball_number,world);
    
    if (current->x<BORDER_LEFT)
        current->x= BORDER_RIGHT-2;
    else
        if (current->x>BORDER_RIGHT)
            current->x= BORDER_LEFT+2;


    if (current->y<BORDER_UP)
        current->y= BORDER_DOWN-2;
    else
        if (current->y>BORDER_DOWN)
            current->y= BORDER_UP+2;
}

//Bounce off other balls
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

//Moves ball by tiny vectors until they travelled their respective remaining vx/vy, checks bounces
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

            //Bounce off walls
            if (!world->screen_wrap)
                wall_bounce(ball_number,world);
            else //Or wrap around the screen
                screen_wrap(ball_number,world);

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
  
//Slows ball by world->friction_multiplier
void friction_ball(ball_t* current,world_t* world){
    //multiplication
    current->vx *= world->friction_multiplier;
    current->vy *= world->friction_multiplier;
        
    //Set to 0 if really small, to fasten up immobilisation
    if( fabs(current->vx)  <0.01)
        current->vx =0;
    if( fabs(current->vy)  <0.01)
        current->vy = 0;
}

//Slows the right balls by world->friction_multiplier
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

    //Inactive balls friction
    if (world->friction == 3 && !world->ghost){
        for (ball_number = 0; ball_number < NB_BALLS; ball_number++){
            if ( get_ball(ball_number,world)->fell )
                friction_ball( get_ball(ball_number,world) ,world);
        }
    }
}

//Everything that happens when a turn ends
void turnOver(world_t* world){
    //Transfer the content of the point buffer
    pointsTransfer(world);

    //If the white ball fell
    if(get_ball(0, world)->fell && !world->ghost){
        //Replace the white ball
        init_white(world);
    }

    //Switch active player
    world->active_player = (world->active_player+1)%2;
}


///// Update Data //////////////////////////////////////////////////////////////
void update_data(world_t* world){
    double highest_speed = 0, calculated_speed;
    int ball_number;
    int total_baby_steps;
    ball_t* current;
    
    //Sets all the balls' Remaining vx and vy to their vx and vy values
    for (ball_number = 0; ball_number < NB_BALLS; ball_number++){
        current = get_ball(ball_number, world); //Retrieve pointer

        current->vRemainingX = current->vx;
        current->vRemainingY = current->vy;

        calculated_speed = sqrt( current->vx * current->vx + current->vy * current->vy );
        if (calculated_speed > highest_speed)
            highest_speed = calculated_speed;
    }

    //Every step needs to be the same for a ball, and smaller than (BALL_SIZE/2) (radius)
    total_baby_steps = (int) highest_speed % (BALL_SIZE/2) +2;

    
    //Moves ball by tiny vectors until they travelled their respective remaining vx/vy, checks bounces
    baby_loop(total_baby_steps, world);

    //Slows down
    friction(world);

    //Ghosts tic
    ghost_attack(world);

    //If turn is over
    if(!moving_or_not_waiting(world) && !world->playerChanged){
        world->playerChanged = 1;
        turnOver(world);
    }

}











