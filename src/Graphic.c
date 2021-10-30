#include "../include/Graphic.h"

void drawQuadtree(Quadtree q){
	if(q->ne != NULL){
		MLV_draw_filled_rectangle(q->ne->a, q->ne->b, q->ne->size, q->ne->size, MLV_convert_rgba_to_color(q->ne->p.r, q->ne->p.g, q->ne->p.b, q->ne->p.a));
		drawQuadtree(q->ne);
	}
	if(q->no != NULL){
		MLV_draw_filled_rectangle(q->no->a, q->no->b, q->no->size, q->no->size, MLV_convert_rgba_to_color(q->no->p.r, q->no->p.g, q->no->p.b, q->no->p.a));
		drawQuadtree(q->no);
	}
	if(q->so != NULL){
		MLV_draw_filled_rectangle(q->so->a, q->so->b, q->so->size, q->so->size, MLV_convert_rgba_to_color(q->so->p.r, q->so->p.g, q->so->p.b, q->so->p.a));
		drawQuadtree(q->so);
	}
	if(q->se != NULL){
		MLV_draw_filled_rectangle(q->se->a, q->se->b, q->se->size, q->se->size, MLV_convert_rgba_to_color(q->se->p.r, q->se->p.g, q->se->p.b, q->se->p.a));
		drawQuadtree(q->se);
	}
}


void drawOptions(){
	MLV_draw_text_box(512, 0, 288, 73, "Quadtree Approximation", 1, MLV_COLOR_WHITE, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
	MLV_draw_text_box(512, 73, 288, 73, "Black and white binary backup", 1, MLV_COLOR_WHITE, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
	MLV_draw_text_box(512, 146, 288, 73, "RGBA binary backup", 1, MLV_COLOR_WHITE, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
	MLV_draw_text_box(512, 219, 288, 73, "Minimization", 1, MLV_COLOR_WHITE, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
	MLV_draw_text_box(512, 292, 288, 73, "Black and white minimized graph backup", 1, MLV_COLOR_WHITE, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
	MLV_draw_text_box(512, 365, 288, 73, "RGBA minimized graph backup", 1, MLV_COLOR_WHITE, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
	MLV_draw_text_box(512, 438, 288, 73, "Close", 1, MLV_COLOR_WHITE, MLV_COLOR_WHITE, MLV_COLOR_BLACK, MLV_TEXT_CENTER, MLV_HORIZONTAL_CENTER, MLV_VERTICAL_CENTER);
}


void drawQuadtreeInTime(Quadtree *q, MLV_Image* img, int subDivision){
	int i = 0;
	(*q) = allocateNode(0, 0, 512, 0, img);
	allocateSonNode(img, q);
	drawQuadtree(*q);
	MLV_actualise_window();
	Quadtree worst = worstLeaf(*q);
	while(i != subDivision){
		allocateSonNode(img, &worst);
		worst = worstLeaf(*q);
		i++;
		MLV_clear_window(MLV_COLOR_BLACK);
		drawQuadtree(*q);
		drawOptions();
		MLV_actualise_window();
	}
}

void drawChoice(){
	MLV_Image* img;
	MLV_Image* img1;
	MLV_Image* img2;
	MLV_Image* img3;
	img = MLV_load_image("Images/terre.png");
	img1 = MLV_load_image("Images/panda.png");
	img2 = MLV_load_image("Images/panthere_rose.jpeg");
	img3 = MLV_load_image("Images/pikachu.png");
	MLV_resize_image(img, 800/2, 512/2);
	MLV_resize_image(img1, 800/2, 512/2);
	MLV_resize_image(img2, 800/2, 512/2);
	MLV_resize_image(img3, 800/2, 512/2);
	MLV_draw_image(img, 0, 0);
	MLV_draw_image(img1, 400, 256);
	MLV_draw_image(img2, 0, 256);
	MLV_draw_image(img3, 400, 0);
	MLV_actualise_window();
}