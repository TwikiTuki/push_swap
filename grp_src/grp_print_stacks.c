#include <graphics.h>

t_color_scaling ColorScaling(int color0, int color1, coord_val max_pxl)
{
	t_color_scaling	scaling;
	
	scaling.color0 = color0;		
	scaling.color1 = color1;		
	scaling.max_pxl = max_pxl;		
	return (scaling);
}

void grp_print_index_to_A(int y_pos, int order_index, t_mlx_img img, coord_val height ,int len, int y_adj)
{
	grp_draw_square(img,
		Point(G_X_BEGIN_A, G_Y_BEGIN_A - y_pos* height - min(y_pos, y_adj)),
		Point(G_AREAS_WIDTH * (order_index+1) / len, height + (y_pos< y_adj)),
		Point(-1, -1),
		ColorScaling(0xffaaffaa, 0xfffefefe, G_AREAS_WIDTH)
	);
}

void grp_print_index_to_B(int y_pos, int order_index, t_mlx_img img, coord_val height, int len, int y_adj)
{
	grp_draw_square(img,
		Point(G_X_BEGIN_B, G_Y_BEGIN_A - y_pos* height - min(y_pos, y_adj)),
		Point(G_AREAS_WIDTH * (order_index+1) / len, height + (y_pos< y_adj)),
		Point(1, -1),
		ColorScaling(0xffaa5566, 0xfffefef, G_AREAS_WIDTH)
	);
}

int grp_print_stacks(t_stk_node* stacks[2], t_stack_id stackid, t_mlx_img img, size_t _len)
{
	coord_val height;
	t_stk_node* node;
	int			i;
	int 		len;
	int			extra_pxls;
	
	len = (coord_val) _len;
	if (len < -1)
		return (0);
	node = stacks[stackid];
	height = G_AREAS_HEIGHT / len;
	extra_pxls = G_AREAS_HEIGHT % len;
	i = stk_len(stacks[stackid]) - 1;
	while (node)
	{
		if (stackid == STACK_A)
			grp_print_index_to_A(i, node->index, img, height, len, extra_pxls);
		else if (stackid == STACK_B)
			grp_print_index_to_B(i, node->index, img, height, len, extra_pxls);
		else 
			return (0);
		node = node->next;
		i--;
	}
	return 1;
}
