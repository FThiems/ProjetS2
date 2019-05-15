/**
 * \file collision.h
 * \brief Signatures des fonctions de collision.c
 */

/**
  * \brief calcule le produit scalaire de deux vecteurs V1 et V2
  * \param x1 abscisse de V1
  * \param y1 ordonnée de V1
  * \param x2 abscisse de V2
  * \param y2 ordonnée de V2
  */
double dot_product(double x1, double y1, double x2, double y2);

/**
  * \brief modifie les vitesses de deux boules B1 et B2, après collision
  * \param x1 abscisse de B1 au moment de la collision
  * \param y1 ordonnée de B1 au moment de la collision
  * \param v1x adresse de la vitesse horizontale de B1
  * \param v1y adresse de la vitesse verticale de B1
  * \param x2 abscisse de B2 au moment de la collision
  * \param y2 ordonnée de B2 au moment de la collision
  * \param v2x adresse de la vitesse horizontale de B2
  * \param v2y adresse de la vitesse verticale de B2
  */
void collision(double x1, double y1, double* vx1, double* vy1, double x2, double y2, double* vx2, double* vy2);