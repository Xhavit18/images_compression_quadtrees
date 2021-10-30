#ifndef __QUADTREES__
#define __QUADTREES__

#include <math.h>
#include <stdio.h>
#include <MLV/MLV_all.h>
#include <stdlib.h>


/*
 *Pixel is a structure used to represent a pixel by its rate of red, green and blue, represented here by integers
 */
typedef struct pixel{
	int r;
	int g;
	int b;
	int a;
}Pixel;

/*

 *Quadtree is a chained list which allows to represent an image by its pixels

 *@field height is an integer that represents the height of the current node in the tree
 *@field p is the pixel of the current node
 *@field a is the abscissa coordinates of the pixel
 *@field b is the ordinate coordinates of the pixel
 *@field size is the weight and height of the pixel
 *@field error is the error of the pixel relative to the area
 *@field no is the adress of the northwest area
 *@field ne is the adress of the northeast area
 *@field se is the adress of the southeast area
 *@field so is the adress of the southwest area

 */
typedef struct node{
	int height;
	Pixel p;
	int a;
	int b;
	int size;
	double error;
	struct node *no;
	struct node *ne;
	struct node *se;
	struct node *so;
}Node, *Quadtree;


/* 
 *Function to calculate the average color of an area

 *@param img is an image load by the MLV library
 *@param a is the abscissa coordinates of the area
 *@param b is the ordinate coordinates of the area
 *@return the average area
 */
Pixel average_color(MLV_Image* img, int a, int b, int size);

/*
 *Function to calculate the distance between two pixels following to the given formula

 *@param p1 is a pixel
 *@parma p2 is a pixel
 @return a double value which represents the distance
 */
double dist(Pixel p1, Pixel p2);

/*
 *Function to calculate the distance between two pixels following to the given formula

 *@param p1 is a pixel
 *@parma p2 is a pixel
 @return a double value which represents the distance
 */
double error(int a, int b, int size, MLV_Image* img);

/*
 *Function to create a new node with filled fields

 *@param x is the abscissa coordinates of the area
 *@param y is the ordinate coordinates of the area
 *@param siz is the weight and height of the area
 *@param hei is the height is in the Quadtree of this node
 *@param img is the image load by MLV library
 *@return the created node
 */
Quadtree allocateNode(int x, int y, int siz, int hei, MLV_Image* img);

/*
 *Function to allocate sons to a node

 *@param img is the image load by MLV library
 *@param *q is the adress of the Quadtree
 */
void allocateSonNode(MLV_Image* img, Quadtree *q);

/*
 *Function to calculate the area with the worst error
 *@param q is the Quadtree that represents our image
 *@return the worst area of the Quadtree
 */
Quadtree worstZone(Quadtree q);

/*
 *Function to calculate the number of leaf of the Quadtree
 *@param q is the Quadtree that represents our image
 *@return the number of leaf
 */
int numberLeaf(Quadtree q);

/*
 *Function to say if we have reached a leaf
 *@param q is the Quadtree that represents our image
 *@return 1 if it's a leaf, 0 otherwise
 */
int isLeaf(Quadtree q);

/*
 *Function to compare the worst error between two area of the Quadtree
 *@param a is the Quadtree that represents an area
 *@param b is the Quadtree that represents an area
 *@return the area with the biggest error
 */
Quadtree worstError(Quadtree a, Quadtree b);

/*
 *Function to calculate which is the leaf of the Quadtree with the biggest error
 *@param q is the Quadtree that represents our image
 *@return the leaf with the biggest error in the Quadtree
 */
Quadtree worstLeaf(Quadtree q);

/*
 *Function to allocate the Quadtree that represents the entire image
 *@param q is the adress of the Quadtree that represents our image
 *@param img is the image load by MLV library
 *@param subDivision is the number of division made
 */
void allocateQuadtree(Quadtree *q, MLV_Image* img, int subDivision);

/*
 *Function to convert RGBA to GreyScale
 *@param p is a Pixel
 *@return the average of the pixel
 */
int BlackWhite(Pixel p);


/*
 Function to convert a Quadtree in color to black and white Quadtree
 *@param *tmp is the adress of the copy of the inital Quadtree
 */
void QuadtreeBlackWhite(Quadtree *tmp);

/**
 *Function that determinates the difference rate between two Quadtrees.
 *@param T is the Quadtree that represents our image
 *@param Q is the Quadtree that represents our image
 */
double distQuadTree(Quadtree T, Quadtree Q);



#endif