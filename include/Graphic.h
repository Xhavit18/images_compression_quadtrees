#ifndef __GRAPHIC__
#define __GRAPHIC__

#include "Quadtrees.h"


/*
 *Function to draw a Quadtree with MLV library
 *@param q is the Quadtree that represents our image
 */
void drawQuadtree(Quadtree q);

/* 
 *Function to draw the Quadtree during his allocation
 *@param *q is the adress of the Quadtree that represents our image
 *@param img is the image load by MLV library
 *@param subDivision is the number of division made
 */
void drawQuadtreeInTime(Quadtree *q, MLV_Image* img, int subDivision);

/*
 *Function to display the image bank
 */
void drawChoice();

/*
 *Function to display the options of the program
 */
void drawOptions();

#endif