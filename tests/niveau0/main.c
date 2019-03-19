/**
 * \file main.c
 * \brief Programme principal du niveau 0, à compléter
 * \author Mathieu Constant
 * \version 0.1
 * \date 13 mars 2019
 */

#include "sdl-light.h"

/**
 * \brief Largeur de l'écran de jeu
 */
#define SCREEN_WIDTH 640

/**
 * \brief Hauteur de l'écran de jeu
 */
#define SCREEN_HEIGHT 480

/**
 * \brief Taille d'une bulle
 */
#define BUB_SIZE 40

/**
 * \brief Taille du bonhomme (sprite)
 */
#define SPRITE_SIZE 32

/**
 * \brief Pas de déplacement du sprite
 */

#define MOVING_STEP 5

/**
 * \brief Vitesse du vent
 */

#define WIND_VX 3


/**
 * \brief Représentation du monde du jeu
 */

struct world_s{
    SDL_Surface* background;
    int gameover;
    SDL_Surface* sprite;
    int pos_x;//Position x du sprite
    int pos_y;//Position y du sprite
    int posb_x;
    int posb_y;
    SDL_Surface* bubbles;
    };

typedef struct world_s world_t;



/**
 * \brief La fonction initialise les données du monde du jeu
 * \param world les données du monde
 */


void init_data(world_t * world){
    world->background = load_image( "ressources/background.bmp" );
    world->gameover = 0;
    world->sprite = load_image( "ressources/sprite.bmp" );
    world->bubbles = load_image( "ressources/bub_blue.bmp" );
    
}


/**
 * \brief La fonction nettoie les données du monde
 * \param world les données du monde
 */


void clean_data(world_t *world){
    SDL_FreeSurface(world->background);
    SDL_FreeSurface(world->sprite);
    SDL_FreeSurface(world->bubbles);
}




/**
 * \brief La fonction indique si le jeu est fini en fonction des données du monde
 * \param world les données du monde
 * \return 1 si le jeu est fini, 0 sinon
 */

int is_game_over(world_t *world){
    return world->gameover;
}


/**
 * \brief La fonction met à jour les données en tenant compte de la physique du monde
 * \param les données du monde
 */

void update_data(world_t *world){
  if(world->posb_x < world->posb_x + WIND_VX){
    world->posb_x += WIND_VX;
  }
}


/**
 * \brief La fonction initialise les transparences des différentes surfaces
 * \param screen la surface correspondant à l'écran de jeu
 * \param world les données du monde
 */

void  init_graphics(SDL_Surface *screen, world_t *world){
    set_transparence(screen, world->sprite, 255, 0, 255);
    set_transparence(screen, world->bubbles, 255, 0, 255);
    world->pos_x = SCREEN_WIDTH/2 - SPRITE_SIZE/2;
    world->pos_y = SCREEN_HEIGHT/2 - SPRITE_SIZE/2;
    world->posb_x = 150;
    world->posb_y = 100;
}


/**
 * \brief La fonction applique la surface de l'image de fond à quatre positions différentes sur l'écran de jeu, de sorte de complètement couvrir ce dernier
 * \param screen l'écran de jeu
 * \param bg la surface de l'image de fond
 */
void apply_background(SDL_Surface *bg, SDL_Surface *screen){
    apply_surface(bg,screen,0,0);
    apply_surface(bg, screen,SCREEN_WIDTH/2, 0);
    apply_surface(bg, screen, 0, SCREEN_HEIGHT/2 );
    apply_surface(bg, screen, SCREEN_WIDTH/2, SCREEN_HEIGHT/2 );
}





/**
 * \brief La fonction rafrachit l'écran en fonction de l'état des données du monde
 * \param screen la surface de l'écran de jeu
 * \param world les données du monde
 */

void refresh_graphics(SDL_Surface *screen, world_t *world){
    apply_background(world->background,screen);
    apply_surface(world->sprite, screen, world->pos_x, world->pos_y);
    apply_sub_surface(world->bubbles, screen, 0, 0, BUB_SIZE, BUB_SIZE, world->posb_x, world->posb_y);
    
    refresh_surface(screen);
}



/**
 * \brief La fonction gère les évènements ayant eu lieu et qui n'ont pas encore été traités
 * \param event paramètre qui contient les événements
 * \param world les données du monde
 */


void handle_events(SDL_Event *event,world_t *world){
    Uint8 *keystates;
    int mouseX, mouseY;
    while( SDL_PollEvent( event ) ) {
        //Si l'utilisateur a cliqué sur le X de la fenêtre
        if( event->type == SDL_QUIT ) {
            //On quitte le programme
            world->gameover = 1;
        }
        
        /* gestion des evenements clavier */
        keystates = SDL_GetKeyState( NULL );
        /* Fleche du haut */
        if( keystates[ SDLK_UP ] ) {
            world->pos_y -= MOVING_STEP;
        }
        /* Fleche du bas */
        if( keystates[ SDLK_DOWN ] ) {
            world->pos_y += MOVING_STEP;
        }
        /* Fleche du droite */
        if( keystates[ SDLK_RIGHT ] ) {
            world->pos_x += MOVING_STEP;
        }
        /* Fleche de gauche */
        if( keystates[ SDLK_LEFT ] ) {
            world->pos_x -= MOVING_STEP;
        }
        
        /* gestion de l'événement souris:
	   bouton de la souris relaché après un clic */
	if(event->type == SDL_MOUSEBUTTONUP){//on recupère les coordonnées de le souris
	  SDL_GetMouseState(&mouseX, &mouseY);
	  world->posb_x = mouseX;
	  world->posb_y = mouseY;
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
