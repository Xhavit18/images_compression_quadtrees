#include "../include/Graphic.h"
#include "../include/compression.h"
#include "../include/encodage.h"

int main(){
	Quadtree q = NULL;
	int x,y;
	MLV_Image* img;
	MLV_create_window("Quadtree", "Quadtree", 800, 512);
	drawChoice();
	MLV_actualise_window();
	MLV_wait_mouse(&x, &y);
	if(x < 400 && y < 256)
		img = MLV_load_image("Images/terre.png");
	if(x < 400 && y > 256)
		img = MLV_load_image("Images/panthere_rose.jpeg");
	if(x > 400 && y < 256)
		img = MLV_load_image("Images/pikachu.png");
	if(x > 400 && y > 256)
		img = MLV_load_image("Images/panda.png");
	MLV_clear_window(MLV_COLOR_BLACK);
	MLV_draw_image(img, 0, 0);
	drawOptions();
	MLV_actualise_window();
	while(1){
		MLV_wait_mouse(&x, &y);
		if(x > 512 && y > 0 && y < 73){
			if(q != NULL){
				printf("You've already launch an approximation for this image !\n");
			}
			else{
				char answer;
				do{
					printf("Do you want to draw it in the same time ? (y or n)\n");
					scanf("%c", &answer);
				}
				while(answer != 'y' && answer != 'n');
				if(answer == 'y')
					drawQuadtreeInTime(&q, img, 4096);
				else
					allocateQuadtree(&q, img, 4069);
				printf("Quadtree created !\n");
			}
		}
		if(x > 512 && y > 73 && y < 146){
			if(q == NULL)
				printf("You have to launch an approximation before trying it !\n");
			else{
				Quadtree copy = q;
				QuadtreeBlackWhite(&copy);
				FILE *bwf = fopen("test.qtn", "w");
				encodingQuadtree(copy, bwf);
				fclose(bwf);
				printf("Encoding black and white file created !\n");
			}
		}
		if(x > 512 && y > 146 && y < 219){
			if(q == NULL)
				printf("You have to launch an approximation before trying it !\n");
			else{
				FILE *cf = fopen("test.qtc", "w");
				encodingQuadtree(q, cf);
				fclose(cf);
				printf("Encoding RGBA file created !\n");
			}
		}
		if(x > 512 && y > 219 && y < 292){
			if(q == NULL)
				printf("You have to launch an approximation before trying it !\n");
			else{
				printf("Number of leaf before : %d\n", numberLeaf(q));
				compressQuadtreeWithoutLosses(&q);
				printf("Number of leaf after : %d\n", numberLeaf(q));
			}
		}
		if(x > 512 && y > 292 && y < 365){
			if(q == NULL)
				printf("You have to launch an approximation before trying it !\n");
			else
				printf("Feature not available, sorry ...\n");
		}
		if(x > 512 && y > 365 && y < 438){
			if(q == NULL)
				printf("You have to launch an approximation before trying it !\n");
			else
				printf("Feature not available, sorry ...\n");
		}
		if(x > 512 && y > 438 && y < 512){
			break;
		}
	}
	MLV_free_window();
	return 1;
}