#include <stdio.h>
#include "graphics.h"

t_point Point(coord_val x, coord_val y)
{
	t_point point;

	point.x = x;
	point.y = y;
	
	return (point);
}

void g_draw_square(t_mlx_img img, t_point begin, t_point size, t_point direction, int colorBegin, int colorEnd)
{

	(void)	colorEnd;
	char	*pxlByte;

	if (direction.x > 0)
		direction.x = 1;
	else 
	{
		direction.x = -1;
		size.x *= direction.x;
	}
	if (direction.y > 0)
		direction.y = 1;
	else 
		direction.y = -1;

	//Outer loop iterates over columns while inner one iterates over lines. In other words it prints by comlumn.
	for (coord_val i = 0; i != size.x; i += direction.x)
	{
		pxlByte = img.data + (begin.x + i) * img.bytesxpxl + begin.y * img.bytesxline;
		for (coord_val j = 0; j < size.y; j++)
		{
			*((int*) pxlByte) =colorBegin;
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
		0xff77aaaa
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
