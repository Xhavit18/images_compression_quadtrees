#ifndef __COMPRESSION__
#define __COMPRESSION__

#include "Quadtrees.h"

/*
 *Function to calculate the height of the Quadtree
 *@param q is the Quadtree that represents our image
 *@param *max is the adress of the height value of the Quadtree 
 */
void maxHeight(Quadtree q, int *max);

/*
 *Function to check if two pixels are the same
 *@param p1 is a pixel
 *@param p2 is a pixel
 @return 1 if they're the same, 0 otherwise
 */
int compareColor(Pixel p1, Pixel p2);

/*
 *Function to check if a node has all his sons with the same pixels
 *@param q is the Quadtree that represents our image
 */
int sameSonColor(Quadtree q);

/*
 *Function to copy the pixel of source to destination
 *@param source is a Quadtree
 *@param *destination is the adress of a Quadtree 
 */
void copy_color(Quadtree source, Quadtree *destination);

/*
 *Function to check if there is a node which has all his sons with the same pixels
 *@param q is the Quadtree that represents our image
 *@param max is the height of the Quadtree q
 *@return 1 if the function find a node with the property, 0 otherwise
 */
int existNode(Quadtree q, int max);

/*
 *Function to suppress a node which has all his sons with the same pixels and has heightMax - 1
 *@param q is the adress of teh Quadtree that represents our image
 *@param max is the height of the Quadtree q
 */
void suppressNode(Quadtree *q, int max);

/*
 Function to minimize the Quadtree without losses
 *@param q is the adress of teh Quadtree that represents our image
 */
void compressQuadtreeWithoutLosses(Quadtree *q);

#endif