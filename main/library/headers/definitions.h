/**
 * \file definitions.h
 * \brief Definitions des constantes, des structures et des includes
 */

#ifndef DEFINITIONS
#define DEFINITIONS

#include "sdl-light.h"
#include <stdlib.h>
#include <stdio.h>
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
#define BORDER_RIGHT (1202-BALL_SIZE/2)
#define BORDER_LEFT (85+BALL_SIZE/2)
#define BORDER_DOWN (640-BALL_SIZE/2)
#define BORDER_UP (85+BALL_SIZE/2)
/**
 * \brief Number of balls
 */
#define NB_BALLS 16
 /**
 * \brief Ball info
 */
struct ball_s{
    double x,y; /*!< Coordonnées du centre de la balle */
    double vx,vy; /*!< Vecteurs vitesse sur x et y */
    double vRemainingX,vRemainingY; /*!< Vecteurs vitesse restants à parcourir durant le rafraîchissment */
    };

typedef struct ball_s ball_t;


/**
 * \brief Représentation du monde du jeu
 */
struct world_s{
    int gameover; /*!< Variable de fin de jeu */
    SDL_Surface* table; /*!< Surface SDL de la table de billard */
    SDL_Surface* balls_sprite; /*!< Surface SDL des boules de billard */
    ball_t** balls; /*!< Tableau de pointeurs sur les boules de billard */
    
    };

typedef struct world_s world_t;

#endif