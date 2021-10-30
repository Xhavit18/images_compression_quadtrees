#include "../include/encodage.h"

void binaryConvert(uint8_t c, FILE *f){
	int i = 7;
	char b;
	while(i >= 0){
		b = (c | (1u << i)) == c;
		fwrite(&b, sizeof(char), 1, f);
		i--;
	}
}

void fromPixeltoBin(Pixel c, FILE* f){
	binaryConvert(c.r, f);
	binaryConvert(c.g, f);
	binaryConvert(c.b, f);
	binaryConvert(c.a, f);
}


void encodingQuadtree(Quadtree q, FILE *f){
	fromPixeltoBin(q->p, f);
	if(q->no != NULL){
		encodingQuadtree(q->no, f);
	}
	if(q->ne != NULL){
		encodingQuadtree(q->ne, f);
	}
	if(q->se != NULL){
		encodingQuadtree(q->se, f);
	}
	if(q->so != NULL){
		encodingQuadtree(q->so, f);
	}
}