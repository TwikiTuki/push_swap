#include "graphics.h"

t_point grp_pixel_coords(t_mlx_img img, char *pixel)
{
	t_point coords;
	coord_val		index;
	
	index = pixel - img.data;
	coords.x = ((index % img.bytesxline) / 4); 
	coords.y = (index / img.bytesxline); 
	return (coords);
}

void grp_draw_pixel(t_mlx_img img, coord_val x, coord_val y, int color)
{
	char *pxl = img.data + x * img.bytesxpxl + y * img.bytesxline;
	//printf("pixel: %d\n", (int) (pxl - img.data));
	*((int*) pxl) = color;
}
