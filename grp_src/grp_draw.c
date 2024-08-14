#include "graphics.h"

void grp_normalize_direction(t_point *direction)
{
	if (direction->x > 0)
		direction->x = 1;
	else 
		direction->x = -1;
	if (direction->y > 0)
		direction->y = 1;
	else 
		direction->y = -1;
}

void grp_draw_square(t_mlx_img img, t_point begin, t_point size, t_point direction, t_color_scaling scaling)
{
	char	*pxlByte;
	int		color;

	if (scaling.max_pxl == 0)
		scaling.max_pxl = size.x;
	grp_normalize_direction(&direction);
	/*	
		Outer loop iterates over columns while inner one iterates over lines.
		In other words it prints by comlumn.
	*/
	for (coord_val i = 0; i != size.x; i++)
	{
		pxlByte = img.data + begin.y * img.bytesxline;
		pxlByte += (begin.x + i * direction.x) * img.bytesxpxl;
		color = grp_average_color(
			scaling.color0,
			scaling.color1,
			Point(i, scaling.max_pxl)
		);
		for (coord_val j = 0; j < size.y; j++)
		{
			*((int*) pxlByte) = color;
			pxlByte += (img.bytesxline * direction.y);
		}
	} 
}

void grp_draw_background(t_mlx_img *img)
{
	grp_draw_square(
		*img,
		Point(0, 0),
		Point(G_WINDOW_WIDTH/2 +1, G_WINDOW_HEIGHT),
		Point(1, 1),
		ColorScaling(0xff88bbbb, 0xc8e9e9, G_WINDOW_WIDTH/2)
	);
	grp_draw_square(
		*img,
		Point(G_WINDOW_WIDTH, 0),
		Point(G_WINDOW_WIDTH/2 +1, G_WINDOW_HEIGHT),
		Point(-1, 1),
		ColorScaling(0xff88bbbb, 0xc8e9e9, G_WINDOW_WIDTH/2+5)
	);
}

void grp_draw_area_A(t_mlx_img img)
{
	grp_draw_square(img,
		Point(G_X_BEGIN_A, G_Y_BEGIN_A),
		Point(G_AREAS_WIDTH, G_AREAS_HEIGHT),
		Point(-1, -1),
		ColorScaling(0xff77aaaa, 0xff77aaaa, 0)
	); 
}

void grp_draw_area_B(t_mlx_img img)
{
	grp_draw_square(img,
		Point(G_X_BEGIN_B, G_Y_BEGIN_B),
		Point(G_AREAS_WIDTH, G_AREAS_HEIGHT),
		Point(1, -1),
		ColorScaling(0xff77aaaa, 0xff77aaaa, 0)
	); 
}
