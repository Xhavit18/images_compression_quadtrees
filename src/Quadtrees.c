#include "../include/Quadtrees.h"


double dist(Pixel p1, Pixel p2){
	return sqrt(pow(p1.r - p2.r, 2) + pow(p1.g - p2.g, 2) + pow(p1.b - p2.b, 2) + pow(p1.a - p2.a, 2));
}

Pixel average_color(MLV_Image* img, int a, int b, int size){
	int i, j;
	Pixel p;
	Pixel somme;
	somme.r = 0;
	somme.g = 0;
	somme.b = 0;
	somme.a = 0;
	for(i = a; i < a + size; i += 1){
		for(j = b; j < b + size; j += 1){
			MLV_get_pixel_on_image(img, i, j, &p.r, &p.g, &p.b, &p.a);
			somme.r += p.r;
			somme.g += p.g;
			somme.b += p.b;
			somme.a += p.a;
		}
	}
	if(size != 0){
		somme.r /= (size * size);
		somme.g /= (size * size);
		somme.b /= (size * size);
		somme.a /= (size * size);
	}
	
	return somme;
}


double error(int a, int b, int size, MLV_Image* img){
	int i, j;
	Pixel average_zone;
	Pixel tmp;
	double somme;
	average_zone = average_color(img, a, b, size);
	somme = 0;
	for(i = a; i < a + size; i += 1){
		for(j = b; j < b + size; j += 1){
			MLV_get_pixel_on_image(img, i, j, &tmp.r, &tmp.g, &tmp.b, &tmp.a);
			somme += dist(tmp, average_zone);
		}
	}
	return somme;
}


Quadtree allocateNode(int x, int y, int siz, int hei, MLV_Image* img){
	Quadtree tmp;
	tmp = (Node*)malloc(sizeof(Node));
	if(tmp != NULL){
		tmp->height = hei;
		tmp->a = x;
		tmp->b = y;
		tmp->size = siz;
		tmp->error = error(x, y, siz, img);
		tmp->p = average_color(img, x, y, siz);
		tmp->no = NULL;
		tmp->ne = NULL;
		tmp->se = NULL;
		tmp->so = NULL;
	}
	return tmp;
}


void allocateSonNode(MLV_Image* img, Quadtree *q) {
	(*q)->no = allocateNode((*q)->a, (*q)->b, (*q)->size / 2, (*q)->height + 1, img);
	(*q)->ne = allocateNode((*q)->a + (*q)->size / 2, (*q)->b, (*q)->size / 2, (*q)->height + 1, img);
	(*q)->so = allocateNode((*q)->a, (*q)->b + (*q)->size / 2, (*q)->size / 2, (*q)->height + 1, img);
	(*q)->se = allocateNode((*q)->a + (*q)->size / 2, (*q)->b + (*q)->size / 2, (*q)->size / 2, (*q)->height + 1, img);
}

int isLeaf(Quadtree q){
	if(q->se == NULL && q->so == NULL && q->ne == NULL && q->no == NULL)
		return 1;
	return 0;
}

int numberLeaf(Quadtree q){
	if(q == NULL)
		return 0;
	if(isLeaf(q) == 1)
		return 1;
	return numberLeaf(q->no) + numberLeaf(q->ne) + numberLeaf(q->so) + numberLeaf(q->se);
}

Quadtree worstZone(Quadtree q){

	Quadtree max_error = q;

	if(q->ne != NULL){
		Quadtree ne = worstZone(q->ne);
		if(ne->error > max_error->error)
			max_error = ne;
	}

	if(q->no != NULL){
		Quadtree no = worstZone(q->no);
		if(no->error > max_error->error)
			max_error = no;
	}

	if(q->so != NULL){
		Quadtree so = worstZone(q->so);
		if(so->error > max_error->error)
			max_error = so;
	}

	if(q->se != NULL){
		Quadtree se = worstZone(q->se);
		if(se->error > max_error->error)
			max_error = se;
	}

	return max_error;
}

Quadtree worstError(Quadtree a, Quadtree b){
	if(a->error > b->error)
		return a;
	return b;
}


Quadtree worstLeaf(Quadtree q){

	Quadtree ne = worstZone(q->ne);
	if(isLeaf(ne) == 0)
		ne = worstLeaf(ne);

	Quadtree no = worstZone(q->no);
	if(isLeaf(no) == 0)
		no = worstLeaf(no);

	Quadtree so = worstZone(q->so);
	if(isLeaf(so) == 0)
		so = worstLeaf(so);

	Quadtree se = worstZone(q->se);
	if(isLeaf(se) == 0)
		se = worstLeaf(se);

	return worstError(worstError(no, ne), worstError(se, so));
}



void allocateQuadtree(Quadtree *q, MLV_Image* img, int subDivision){
	int i = 0;
	(*q) = allocateNode(0, 0, 512, 0, img);
	allocateSonNode(img, q);
	Quadtree worst = worstLeaf(*q);
	while(i != subDivision){
		allocateSonNode(img, &worst);
		worst = worstLeaf(*q);
		i++;
	}
}

int BlackOrWhite(Pixel p){
	return (p.r + p.g + p.r) / 3;
}

void QuadtreeBlackWhite(Quadtree *tmp){
	if(*tmp == NULL)
		return;
	(*tmp)->p.r = BlackOrWhite((*tmp)->p);
	(*tmp)->p.g = BlackOrWhite((*tmp)->p);
	(*tmp)->p.b = BlackOrWhite((*tmp)->p);
	if((*tmp)->no != NULL){
		QuadtreeBlackWhite(&(*tmp)->no);
	}
	if((*tmp)->ne != NULL){
		QuadtreeBlackWhite(&(*tmp)->ne);
	}
	if((*tmp)->so != NULL){
		QuadtreeBlackWhite(&(*tmp)->se);
	}
	if((*tmp)->se != NULL){
		QuadtreeBlackWhite(&(*tmp)->so);
	}
}

double distQuadTree(Quadtree T, Quadtree Q) {

	if ( isLeaf(T) && isLeaf(Q) )
		return dist(T->p, Q->p);

	if ( isLeaf(T) && !isLeaf(Q) )
		return distQuadTree(T, Q->ne) + distQuadTree(T, Q->no) + distQuadTree(T, Q->se) + distQuadTree(T, Q->so);

	if ( !isLeaf(T) && isLeaf(Q) )
		return distQuadTree(T->ne, Q) + distQuadTree(T->no, Q) + distQuadTree(T->se, Q) + distQuadTree(T->so, Q);

	if (!isLeaf(T) && !isLeaf(Q)) 
		return distQuadTree(T->ne, Q->ne) + distQuadTree(T->no, Q->no) + distQuadTree(T->se, Q->se) + distQuadTree(T->so, Q->so);

	/*if this is reached, its mean that an error occured*/
	return -1;
}


