/**
 * \file main.c 
 * \brief Billard
 */

#include "sdl-light.h"
#include <math.h>

/**
 *  \brief Largeur de l'écran de jeu 
 */
#define SCREEN_WIDTH 1288

/**
 *\brief Hauteur de l'écran de jeu 
 */
#define SCREEN_HEIGHT 725

/**
 *\brief Taille d'une boule 
 */
#define BALL_SIZE 42
/**
 *  \brief Size of the border
 */
#define BORDER_SIZE 80
/**
 *  \brief Speed multiplier
 */
#define SPEED_COEF 0.1
/**
 *  \brief Borders
 */
#define BORDER_RIGHT (SCREEN_WIDTH-BALL_SIZE/2-BORDER_SIZE)
#define BORDER_LEFT (BORDER_SIZE+BALL_SIZE/2)
#define BORDER_DOWN (SCREEN_HEIGHT-BALL_SIZE/2-BORDER_SIZE)
#define BORDER_UP (BORDER_SIZE+BALL_SIZE/2)


/**
 * \brief Ball info
 */
struct ball_s{
    double x,y;
    double vx,vy;
    };

typedef struct ball_s ball_t;


/**
 * \brief Représentation du monde du jeu
 */
struct world_s{
    int gameover;
    SDL_Surface* table;
    SDL_Surface* balls_sprite ;
    ball_t* white_ball;
    
    };

typedef struct world_s world_t;





/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */
void init_data(world_t* world){
    world->gameover = 0;
    
    //Loads sprite images, they need to be freed within clean_data
    world->table = load_image("ressources/table.bmp");
    world->balls_sprite = load_image("ressources/boules.bmp");
    
    //Allocates memory to world->white_ball
    world->white_ball = calloc(4,sizeof(double));
    
    //Sets the default postions of balls
    world->white_ball->x = 385;
    world->white_ball->y = 364;

    world->white_ball->vx = 10.;
    world->white_ball->vy = 20.0;
}



/**
 * \brief La fonction nettoie les données du monde
 * \param world les données du monde
 */
void clean_data(world_t* world){
    SDL_FreeSurface(world->table);
    SDL_FreeSurface(world->balls_sprite);
    free(world->white_ball);
}




/**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world les données du monde
 * \return 1 si le jeu est fini, 0 sinon
 */
int is_game_over(world_t* world){
    return world->gameover;
}


/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param world les données du monde
 */
void update_data(world_t* world){
    //Moves white_ball by it's vectors
    world->white_ball->x +=  world->white_ball->vx;
    world->white_ball->y += world->white_ball->vy;
    
    
    
    //Bounces off walls  //TODO Add half-vector managments for bounces (cut vector) #####################################
        //Right side
        if (world->white_ball->x > BORDER_RIGHT)
            world->white_ball->vx = -1 * fabs(world->white_ball->vx);
        //Left side
        if (world->white_ball->x < BORDER_LEFT)
            world->white_ball->vx = fabs(world->white_ball->vx);

        
        //Lower side
        if (world->white_ball->y > BORDER_DOWN)
            world->white_ball->vy = -1 * fabs(world->white_ball->vy);
        //Upper side
        if (world->white_ball->y < BORDER_UP)
            world->white_ball->vy = fabs(world->white_ball->vy);
    
    //Slows down
    world->white_ball->vx *= 0.95;
    world->white_ball->vy *= 0.95;

}


/**
 * \brief La fonction initialise les transparences des différentes surfaces
 * \param screen la surface correspondant à l'écran de jeu
 * \param world les données du monde
 */
void  init_graphics(SDL_Surface* screen, world_t* world){
    set_transparence(screen,world->balls_sprite,255,0,255);
}



/**
 * \brief La fonction rafrachit l'écran en fonction de l'état des données du monde
 * \param screen la surface de l'écran de jeu
 * \param world les données du monde
 */

void refresh_graphics(SDL_Surface* screen, world_t* world){
    apply_surface(world->table,screen,0,0);
    apply_sub_surface(world->balls_sprite,screen,0,0,BALL_SIZE,BALL_SIZE,world->white_ball->x-BALL_SIZE/2,world->white_ball->y-BALL_SIZE/2);
    refresh_surface(screen);
}



/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */


void handle_events(SDL_Event* event,world_t* world){
    int mouseX,mouseY;
    while( SDL_PollEvent( event ) ) {
        //Si l'utilisateur a cliqué sur le X de la fenêtre
        if( event->type == SDL_QUIT ) {
            //On quitte le programme
            world->gameover = 1;
        }
    
        if( event->type == SDL_MOUSEBUTTONUP ){
            SDL_GetMouseState(&mouseX,&mouseY);
            world->white_ball->vx = (mouseX - world->white_ball->x) *SPEED_COEF;
            world->white_ball->vy = (mouseY - world->white_ball->y) *SPEED_COEF;
        }
        
    }
    
}

/**
 *  \brief programme principal qui implémente la boucle du jeu
 */


int main( int argc, char* args[] )
{
    SDL_Event event;
    world_t world;
    SDL_Surface *screen;

    screen = init_sdl(SCREEN_WIDTH, SCREEN_HEIGHT);
    init_data(&world);
    init_graphics(screen,&world);
    
    while(!is_game_over(&world)){
        handle_events(&event,&world);
        update_data(&world);
        refresh_graphics(screen,&world);
        SDL_Delay(10);
    }
    
    clean_data(&world);
    quit_sdl();
    
    
    return 0;
}
