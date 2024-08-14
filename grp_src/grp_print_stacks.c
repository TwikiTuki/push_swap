#include <graphics.h>

t_color_scaling ColorScaling(int color0, int color1, coord_val max_pxl)
{
	t_color_scaling	scaling;
	
	scaling.color0 = color0;		
	scaling.color1 = color1;		
	scaling.max_pxl = max_pxl;		
	return (scaling);
}

void grp_print_index_to_A(int y_pos, int order_index, t_mlx_img img, coord_val height, int len, int extra_y, int extra_height)
{
	grp_draw_square(img,
		Point(G_X_BEGIN_A, G_Y_BEGIN_A - y_pos* height - extra_y),
		Point(G_AREAS_WIDTH * (order_index+1) / len, height + extra_height),
		Point(-1, -1),
		ColorScaling(0xffaaffaa, 0xfffefefe, G_AREAS_WIDTH)
	);
}

void grp_print_index_to_B(int y_pos, int order_index, t_mlx_img img, coord_val height, int len, int extra_y, int extra_height)
{
	grp_draw_square(img,
		Point(G_X_BEGIN_B, G_Y_BEGIN_A - y_pos * height - extra_y),
		Point(G_AREAS_WIDTH * (order_index+1) / len, height + extra_height),
		Point(1, -1),
		ColorScaling(0xffaa5566, 0xfffefef, G_AREAS_WIDTH)
	);
}

// TODO refactor
int grp_print_stack(t_stk_node* stacks[2], t_stack_id stackid, t_mlx_img img, size_t len)
{
	int					i;
	coord_val			height;
	t_stk_node*			node;
	float				extra_triger;
	coord_val			extra_pxls;
	coord_val			extra_y;
	coord_val			extra_height;
	
	node = stk_last(stacks[stackid]);
	height = G_AREAS_HEIGHT / len;
	extra_pxls = G_AREAS_HEIGHT % len;
	extra_triger = extra_pxls == 0 ? 0 : (float) len / extra_pxls;
	extra_y = 0;
	extra_height = 0;
	i = 0;
	while (node)
	{
		if (i >= extra_triger * extra_y)
			extra_height = 1;
		if (stackid == STACK_A)
			grp_print_index_to_A(i, node->index, img, height, len, extra_y, extra_height);
		else if (stackid == STACK_B)
			grp_print_index_to_B(i, node->index, img, height, len, extra_y, extra_height);
		else 
			return (0);
		node = node->previous;
		if (extra_height == 1)
		{
			extra_height = 0;
			extra_y++;
		}
		i++;
	}
	return 1;
}
