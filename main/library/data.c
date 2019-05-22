/**
 * \file data.c
 * \brief World editing functions
 */


/**
 * \brief Imports and function headers for this file
 */
#include "headers/data.h"



///// Initialisations //////////////////////////////////////////////////////////////
//!Sets world's parameters
void init_parameters(world_t* world){
    world->gameover = 0; //do start the game
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
}

//! Places the white ball
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

//! Places all balls at the right spot
void init_balls(world_t* world){
    int col = 1, row, nb = 1;
    ball_t *current;

    //Place the white ball
    init_white(world);

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

//!Places holes
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

//!Loads all game images
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

//Initialise les scores des joueurs
void init_score(world_t* world){
    world->p0 = 0;
    world->p1 = 0;
    world->pointsBuffer = 0;
}

//!Initializes all of world's fields
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
//!Calculates the distance between the corresponding ball and hole s
int dist_ball_hole(world_t* world, int ball_number, int hole_number){
  return sqrt( (world->balls[ball_number]->x - world->holes[hole_number]->x) * (world->balls[ball_number]->x - world->holes[hole_number]->x)
           + ( (world->balls[ball_number]->y - world->holes[hole_number]->y) * (world->balls[ball_number]->y - world->holes[hole_number]->y) ) );
}


//!Function checking if the corresponding ball should fall in the hole or not
bool is_falling(world_t* world, int ball_number, int hole_number){
    if(!(world->balls[ball_number]->fell)){
        return(dist_ball_hole(world, ball_number, hole_number) < BALL_SIZE/2 + HOLE_RADIUS);
    }
}


//Function checking if any ball should fall in any hole and making them fall
void all_holes(world_t* world){
  int ball_number, hole_number;

  for (ball_number = 0; ball_number<NB_BALLS; ball_number++){
    for (hole_number = 0; hole_number<NB_HOLES; hole_number++){
      if (is_falling(world, ball_number, hole_number)){
        world->balls[ball_number]->fell = 1;
        scoring(world, ball_number);
      }
    }
  }
}

//Adds the fallen ball's points to the turn point buffer
void scoring(world_t* world, int ball_number){
    world->pointsBuffer += ball_number;
}

//Transfers the content of the point buffer when the turn is over
void pointsTransfer(world_t* world){
    if((world->balls[0]->fell + world->active_player)%2)
        world->p0 += world->pointsBuffer;
    else
        world->p1 += world->pointsBuffer;
    world->pointsBuffer = 0;
}



///// Clean function //////////////////////////////////////////////////////////////
//!Cleans all mallocs and callocs
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
//!Moves ball toward x,y
void target(int x, int y, ball_t* ball){
    //Right side
    if (x < ball->x){
        //Go left
        ball->vx -= 0.1;
    }
    //Left side
    if (ball->x < x){
        //Go right
        ball->vx += 0.1;
    }

    //Bellow
    if (y < ball->y){
        ball->vy -= 0.1;
    }

    //Above
    if (ball->y < y){
        ball->vy += 0.1;
    }
}

//!Moves ball toward x,y
void flee(int x, int y, ball_t* ball){
    //Right side
    if (x < ball->x){
        //Go right
        ball->vx += 0.1;
    }
    //Left side
    if (ball->x < x){
        //Go left
        ball->vx -= 0.1;
    }

    //Bellow
    if (y < ball->y){
        ball->vy += 0.1;
    }

    //Above
    if (ball->y < y){
        ball->vy -= 0.1;
    }
}

//Ghost tic
void ghost_attack(world_t* world){
    if (!world->fight)
        return;

    //fighting on

    ball_t* pacman = get_ball(1, world);


    //Blinky move toward pacman
    target(pacman->x, pacman->y, get_ball(3,world));

    //Pinky move to the front
    target(pacman->x + pacman->vx*2 +BALL_SIZE, pacman->y + pacman->vy*2 + BALL_SIZE, get_ball(11,world));

    //Inky move...
    target(pacman->x + pacman->vx*2 +BALL_SIZE + get_ball(3,world)->x -pacman->x,
        pacman->y + pacman->vy*2 + BALL_SIZE * get_ball(3,world)->y -pacman->y,
        get_ball(10,world));

    //Clyde
    ball_t* Clyde = get_ball(5,world);
    if (distance(pacman, Clyde) > BALL_SIZE*5){
        target(pacman->x,pacman->y,Clyde);
    }
    else {
        flee(pacman->x,pacman->y,Clyde);
    }



    //pacman
    if (distance(pacman, Clyde) < 10*BALL_SIZE)
        flee(Clyde->x,Clyde->y,pacman);
    else{
        target(1228/2,400,pacman);
        target(1228/2,400,pacman);
        target(1228/2,400,pacman);
    }

    //Screen wrap
    if (pacman->x<BORDER_LEFT+BALL_SIZE)
        pacman->x= BORDER_RIGHT-BALL_SIZE*2;
    else
        if (pacman->x>BORDER_RIGHT-BALL_SIZE)
            pacman->x= BORDER_LEFT+BALL_SIZE*2;


    if (pacman->y<BORDER_UP+BALL_SIZE)
        pacman->y= BORDER_DOWN-BALL_SIZE*2;
    else
        if (pacman->y>BORDER_DOWN-BALL_SIZE)
            pacman->y= BORDER_UP+BALL_SIZE*2;

}

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
    if( fabs(current->vx)  <0.01)
        current->vx =0;
    if( fabs(current->vy)  <0.01)
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

    //Inactive balls friction
    if (world->friction == 3 && !world->ghost){
        for (ball_number = 0; ball_number < NB_BALLS; ball_number++){
            if ( get_ball(ball_number,world)->fell )
                friction_ball( get_ball(ball_number,world) ,world);
        }
    }
}

//!Everything that happens when a turn ends
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
    ball_t *current;
    
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

    //Ghosts tic
    ghost_attack(world);

    //If turn is over
    if(!isTurnGoing(world) && !world->playerChanged){
        world->playerChanged = 1;
        turnOver(world);
    }

}











