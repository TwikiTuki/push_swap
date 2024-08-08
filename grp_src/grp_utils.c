#include <stdio.h>
#include <stdlib.h>
#include "graphics.h"

t_point Point(coord_val x, coord_val y)
{
	t_point point;

	point.x = x;
	point.y = y;
	
	return (point);
}

static char grp_average_char(unsigned char color0, unsigned char color1, t_point division)
{
	int		dif;

	dif = ((int)color1 - (int)color0) * (int) division.x / (int) division.y; 
//	printf("::: color0: %d, dif: %d\n", color0, dif);

	return ((char) ((int)color0 + dif));
}

int grp_average_color(unsigned int color0, unsigned int color1, t_point division)
{
	char	shift;
	unsigned char	byteColor;
	int		colorRes;

	
	colorRes= 0;
	//printf(" colorRes %x\n", colorRes);
	//printf("color0 %x, color1 %x\n", color0, color1);
	//printf("divx %x, divy %x\n", division.x, division.y);
	for (int i = 0; i < 4; i++)
	{
		shift = 8 * i;
		byteColor = grp_average_char(color0 >> shift, color1 >> shift, division);
		colorRes += ((int)0+ byteColor) << shift;
		//printf(":: sdaf: %d\n", byteColor == 0xaa);
		//printf(":: byteColor %x, colorRes %x\n",byteColor, colorRes);
	}
	return colorRes;
}

void g_draw_square(t_mlx_img img, t_point begin, t_point size, t_point direction, int colorBegin, int colorEnd, coord_val max_width_color_scaling)
{

	char	*pxlByte;
	int		color;

	if (max_width_color_scaling == 0)
		max_width_color_scaling = size.x;
	//max_width_color_scaling = G_AREAS_WIDTH;
	if (direction.x > 0)
		direction.x = 1;
	else 
	{
		direction.x = -1;
//		size.x *= direction.x; //TODO really needed?
	}
	if (direction.y > 0)
		direction.y = 1;
	else 
		direction.y = -1;

	//Outer loop iterates over columns while inner one iterates over lines. In other words it prints by comlumn.
	//for (coord_val i = 0; i != size.x; i += direction.x)
	for (coord_val i = 0; i != size.x; i++)
	{
		//pxlByte = img.data + (begin.x + i) * img.bytesxpxl + begin.y * img.bytesxline;
		pxlByte = img.data + (begin.x + i * direction.x) * img.bytesxpxl + begin.y * img.bytesxline;
		pxlByte += (img.bytesxline); //TODO why ??? 
		color = grp_average_color(colorBegin, colorEnd, Point(i, max_width_color_scaling));
		for (coord_val j = 0; j < size.y; j++)
		{
			*((int*) pxlByte) = color;
			pxlByte += (img.bytesxline * direction.y);
		}
	} 
}

void g_draw_area_B(t_mlx_img img)
{

	g_draw_square(img,
		Point(G_X_BEGIN_B, G_Y_BEGIN_B),
		Point(G_AREAS_WIDTH, G_AREAS_HEIGHT),
		Point(1, -1),
		0xff77aaaa,
		0xff77aaaa,
		0
	); 
}

void g_draw_area_A(t_mlx_img img)
{
	int		color;
	char	*pxlbyte;

	color = 0xff77aaaa;
	for (coord_val i = 0; i < G_AREAS_HEIGHT; i++)
	{
		pxlbyte = img.data + G_X_BEGIN_A * img.bytesxpxl + (G_Y_BEGIN_A - i - 0) * img.bytesxline;
		for (coord_val j = 0; j < G_AREAS_WIDTH; j++)
		{
			*((int*) pxlbyte) = color;
			pxlbyte -= img.bytesxpxl;
		}
	}
}

void g_draw_pixel(t_mlx_img img, coord_val x, coord_val y, int color)
{
	char *pxl = img.data + x * img.bytesxpxl + y * img.bytesxline;
	//printf("pixel: %d\n", (int) (pxl - img.data));
	*((int*) pxl) = color;
}

t_point g_pixel_coords(t_mlx_img img, char *pixel)
{
	t_point coords;
	coord_val		index;
	
	index = pixel - img.data;
	coords.x = ((index % img.bytesxline) / 4); 
	coords.y = (index / img.bytesxline); 
	
	return (coords);
}
