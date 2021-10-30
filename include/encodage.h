#ifndef __ENCODAGE__
#define __ENCODAGE__

#include "Quadtrees.h"

/*
 *Function to convert from a pixel filed to binary
 *@param c is a pixel field
 *@param f is a file
 */
void binaryConvert(uint8_t c, FILE *f);

/*
 *Function to convert pixel in binary
 *@param c is a pixel
 *@param f is a file
 */
void fromPixeltoBin(Pixel c, FILE* f);

/*
 *Function to encode the Quadtree in binary
 *@param q is the Quadtree that represents our image
 *@param f is a file
 */
void encodingQuadtree(Quadtree q, FILE *f);

#endif