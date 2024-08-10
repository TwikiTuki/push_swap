#include "graphics.h"

t_point Point(coord_val x, coord_val y)
{
	t_point point;

	point.x = x;
	point.y = y;
	
	return (point);
}

int min(int val0, int val1)
{
	if (val0 < val1)
		return (val0);
	return (val1);
}

char grp_average_char(unsigned char color0, unsigned char color1, t_point division)
{
	int		dif;

	dif = ((int)color1 - (int)color0) * (int) division.x / (int) division.y; 
	return ((char) ((int)color0 + dif));
}

int grp_average_color(unsigned int color0, unsigned int color1, t_point division)
{
	char			shift;
	unsigned char	byteColor;
	int				colorRes;
	
	colorRes= 0;
	for (int i = 0; i < 4; i++)
	{
		shift = 8 * i;
		byteColor = grp_average_char(color0 >> shift,
			color1 >> shift, division);
		colorRes += ((int)0+ byteColor) << shift;
	}
	return colorRes;
}
