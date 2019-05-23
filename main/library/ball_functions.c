/**
 * \file ball_functions.c
 * \brief Ball handling functions
 */


#include"headers/ball_functions.h" //Imports and function headers for this file

///// Ball info //////////////////////////////////////////////////////////////
//Tells if the turn isn't over
int moving_or_not_waiting(world_t* world){
    int ball_number; //Current ball's index
    ball_t* current; //Current ball's pointer

    if(world->notWaiting){
        return 0;
    }

    for (ball_number = 0; ball_number < NB_BALLS; ball_number++){
        current = get_ball(ball_number,world);
        if (!current->fell || world->ghost){
            if (current->vx || current->vy) //if moving
                return 1;
        }
    }

    return 0; //none was moving
}

//Returns the distance between A and B
int distance(ball_t* A, ball_t* B){
    int dist_x = A->x - B->x;
    int dist_y = A->y - B->y;
    return sqrt(dist_x*dist_x + dist_y*dist_y);
}




///// Ball instructions //////////////////////////////////////////////////////////////
//Moves ball toward x,y
void target(int x, int y, ball_t* ball){
    //Right side
    if (x < ball->x-1){
        //Go left
        ball->vx -= 0.1;
    }
    //Left side
    if (ball->x < x-1){
        //Go right
        ball->vx += 0.1;
    }

    //Bellow
    if (y < ball->y-1){
        ball->vy -= 0.1;
    }

    //Above
    if (ball->y < y-1){
        ball->vy += 0.1;
    }
}

//Moves ball toward x,y
void flee(int x, int y, ball_t* ball){
    //Right side
    if (x < ball->x){
        //Go right
        ball->vx += 0.1;
    }
    //Left side
    if (ball->x <= x){
        //Go left
        ball->vx -= 0.1;
    }

    //Bellow
    if (y < ball->y){
        ball->vy += 0.1;
    }

    //Above
    if (ball->y <= y){
        ball->vy -= 0.1;
    }
}




///// Ball retrieval //////////////////////////////////////////////////////////////
//Given ball
ball_t* get_ball(int ball_number,world_t* world){
    if (ball_number >= NB_BALLS){
        printf("\n\n\n\n");
        printf("###############\n");
        printf("get ball() error : get_ball(%i) of an inexisting ball! \n",ball_number);
        printf("###############\n");
        printf("\n\n\n\n");
        exit(404);
    }
    return world->balls[ball_number];
}

//Returns a random non-fallen ball (or any i ghost is activated), white if none was eligible
ball_t* get_random_ball(world_t* world){
    int ball_number; //Current ball's index
    ball_t* current; //Current ball's pointer
    
    int alive_count; //How many balls are eligible
    int chosen_one;

    
    //How many do we pick from?
    if (world->ghost)
        alive_count = NB_BALLS;
    else //Count how many balls are eligible
        for (ball_number = 0; ball_number < NB_BALLS; ball_number++){
            current = get_ball(ball_number,world);
            if (!current->fell) //if moving
                alive_count++;
        }

    
    chosen_one = (random() + time(NULL))% NB_BALLS;
    for (ball_number = 0; ball_number < NB_BALLS; ball_number++){
        chosen_one--;
        if (chosen_one <1)
            return get_ball(ball_number, world);
    }
}


























