#include "../include/compression.h"

void maxHeight(Quadtree q, int *max){
	if(q == NULL)
		return;
	if(q->height > *max && isLeaf(q))
		*max = q->height;
	if(q->ne != NULL){
		maxHeight(q->ne, max);
	}
	if(q->se != NULL){
		maxHeight(q->se, max);
	}
	if(q->no != NULL){
		maxHeight(q->no, max);
	}
	if(q->so != NULL){
		maxHeight(q->so, max);
	}
}

int compareColor(Pixel p1, Pixel p2){
	if(p1.r == p2.r && p1.g == p2.g && p1.b == p2.b)
		return 1;
	return 0;
}

int sameSonColor(Quadtree q){
	if(q == NULL || isLeaf(q))
		return 0;
	if(compareColor(q->no->p, q->ne->p) == 1 && compareColor(q->no->p, q->so->p) && compareColor(q->no->p, q->se->p) == 1)
		return 1;
	return 0;
}

int existNode(Quadtree q, int max){
	if(sameSonColor(q) && q->height == max - 1)
		return 1;
	if(isLeaf(q) || q == NULL)
		return 0;
	return existNode(q->no, max) || existNode(q->ne, max) || existNode(q->se, max) || existNode(q->so, max);
}

void copy_color(Quadtree source, Quadtree *destination){
	(*destination)->p.r = source->p.r;
	(*destination)->p.g = source->p.g;
	(*destination)->p.b = source->p.b;
	(*destination)->p.a = source->p.a;
}

void suppressNode(Quadtree *q, int max){
	if(*q == NULL || isLeaf(*q))
		return;
	if(sameSonColor(*q) && (*q)->height == max - 1){
		copy_color((*q)->no, &(*q));
		free((*q)->no);
		(*q)->no = NULL;
		free((*q)->so);
		(*q)->so = NULL;
		free((*q)->se);
		(*q)->se = NULL;
		free((*q)->ne);	
		(*q)->ne = NULL;
		return;
	}
	if((*q)->no != NULL){
		suppressNode(&((*q)->no), max);
	}
	if((*q)->ne != NULL){
		suppressNode(&((*q)->ne), max);
	}
	if((*q)->so != NULL){
		suppressNode(&((*q)->so), max);
	}
	if((*q)->se != NULL){
		suppressNode(&((*q)->se), max);
	}
}

void compressQuadtreeWithoutLosses(Quadtree *q){
	int max = 0;
	maxHeight(*q, &max);
	while(existNode(*q, max)){
	 	suppressNode(&(*q), max);
	 	max = 0;
	 	maxHeight(*q, &max);
	}
}