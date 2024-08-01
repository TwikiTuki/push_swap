
#include <stdio.h>
#include "psw_graphics.h"

void g_draw_area_A(t_mlx_img img)
{
	int		color;
	char	*pxlbyte;

	color = 0xff77aaaa;
	for (int i = 0; i < G_AREAS_HEIGHT; i++)
	{
		pxlbyte = img.data + G_X_BEGIN_A * img.bytesxpxl + (G_Y_BEGIN_A - i - 1) * img.bytesxline;
		for (int j = 0; j < G_AREAS_WIDTH; j++)
		{
			*((int*) pxlbyte) = color;
			pxlbyte -= img.bytesxpxl;
		}
	}
}

void g_draw_pixel(t_mlx_img img, int x, int y, int color)
{
	char *pxl = img.data + x * img.bytesxpxl + y * img.bytesxline;
//	printf("pixel: %d\n", (int) (pxl - img.data));
	*((int*) pxl) = color;
}

t_point g_pixel_coords(t_mlx_img img, char *pixel)
{
	t_point coords;
	int		index;
	
	index = pixel - img.data;
	coords.x = ((index % img.bytesxline) / 4); 
	coords.y = (index / img.bytesxline); 
	
	return (coords);
}

void mlx_main(int argc, char **argv)
{
	void*	mlx;
	void*	mlx_window;
//	void*	mlx_img; int 	pxl;
//	int		bitsxpxl;
//	int		bitsxline;
//	int		endian;
	int 	color;
	//int 	bytesxpxl;
	int		sdaf;
	int 	pxl;

	t_mlx_img	img;
	
	//char*	mlx_img_data;

	(void)	argc;
	(void)	argv;

	mlx = mlx_init();
	mlx_window = mlx_new_window(mlx, G_WINDOW_WIDTH, G_WINDOW_HEIGHT, "Push Swap");
	img.img = mlx_new_image(mlx, G_WINDOW_WIDTH, G_WINDOW_HEIGHT);
	img.data = mlx_get_data_addr(img.img, &sdaf, &img.bytesxline, &img.endian);
	img.bitsxpxl = sdaf;
	img.bytesxpxl = img.bitsxpxl / 8;
	for (int i = 0; i < G_WINDOW_HEIGHT; i++)
	{
		pxl = G_WINDOW_WIDTH * i;
		//printf("i: %d pxl %d\n", i, pxl);
		for (int j = 0; j < G_WINDOW_WIDTH; j++)
		{
			color = 0x88888888;
			for (int k = 0; k < img.bytesxpxl; k++)
				*(img.data+pxl+k) = 0x88;
			*((int*)img.data + pxl) = color;
			//printf("i: %d j: %d pxl %d\n", i, j, pxl);
			pxl++;
		}
	}
	for (int i = 0; i < 100; i++)
	{
		for (int j = 0; j < 100; j++)
		{
			g_draw_pixel(img, i + 250, j + 350, 0xffffff00);
		}
	}
	g_draw_area_A(img);
	printf("sdaf\n");
	mlx_put_image_to_window(mlx, mlx_window, img.img, 0, 0);
	printf("fasd\n");
	mlx_loop(mlx);
	printf("koko\n");
}
