#include <stdio.h>
#include <unistd.h>
#include <push_swap.h>
#include <checker.h>
#include "graphics.h"

int init_mlx_stuff(void** mlx, void** mlx_window, t_mlx_img* img)
{
	*mlx = mlx_init();
	*mlx_window = mlx_new_window(*mlx, G_WINDOW_WIDTH, G_WINDOW_HEIGHT, "Push Swap");
	img->img = mlx_new_image(*mlx, G_WINDOW_WIDTH, G_WINDOW_HEIGHT);
	img->data = mlx_get_data_addr(img->img, &img->bitsxpxl, &img->bytesxline, &img->endian);
	img->bytesxpxl = img->bitsxpxl / 8;
	if (!*mlx || !*mlx_window || !img->data || !img->img)
		return (0);	
//	g_draw_square(*img, Point(0,0), Point(G_WINDOW_WIDTH,G_WINDOW_HEIGHT), Point(1,1), 0xff88bbbb, 0x88bbbb, G_WINDOW_WIDTH); // TODO color changed
	g_draw_square(*img, Point(0,0), Point(G_WINDOW_WIDTH,G_WINDOW_HEIGHT), Point(1,1), 0x00000000, 0x00000000, G_WINDOW_WIDTH);
	g_draw_area_A(*img);
	g_draw_area_B(*img);
	return 1; // TODO no memfree on NULL
}


void print_index_to_A(int y_position, int order_index, t_mlx_img img, coord_val height ,int len, coord_val y_adj)
{
	printf("::::: y_position: %d, y_adjustment: %d\n", y_position, y_adj);
	int hieight_adj = y_adj == (y_position + 1);
	g_draw_square(img, Point(G_X_BEGIN_A, y_position * height + G_MARGIN + y_adj), Point(G_AREAS_WIDTH * (order_index+1) / len, height + hieight_adj), Point(-1, 1), 0xffaaffaa, 0xfffefefe, G_WINDOW_WIDTH);
	//g_draw_square(img, Point(G_X_BEGIN_A, y_position * height + G_MARGIN), Point(G_AREAS_WIDTH * (order_index+1) / len, height), Point(-1, 1), 0xffaaffaa, 0xfffefefe, G_WINDOW_WIDTH);
}

void print_index_to_B(int y_position, int order_index, t_mlx_img img, coord_val height ,int len, coord_val y_adj)
{
	printf("STACK_B: y_position: %d, order_index: %d, len: %d\n", y_position, order_index, len);
	int width_adj = y_adj == (y_position + 1);
	//g_draw_square(img, Point(G_X_BEGIN_B, y_position * height + G_MARGIN + y_adj), Point(G_AREAS_WIDTH * (order_index+1) / len, height), Point(1, -1),  0xffaa5566, 0xfffefefe, G_WINDOW_WIDTH);
	g_draw_square(img, Point(G_X_BEGIN_B, y_position * height + G_MARGIN + y_adj), Point(G_AREAS_WIDTH * (order_index+1) / len, height + width_adj), Point(1, 1), 0xffaa5566, 0xfffefefe, G_WINDOW_WIDTH);
}

coord_val y_adjustment(int index, coord_val height, int len)
{
	coord_val mod;
//	coord_val remaining;

return (0);
	mod = height  % len;
//	remaining = len-index;
if (index < mod)
	return index + 1;
return mod -0;
//TODO delete
//	if (remaining < mod)
//		return (remaining);
//	return (mod);
}

int print_stacks(t_stk_node* stacks[2], t_stack_id stackid, t_mlx_img img, size_t _len)
{
	coord_val height;
	t_stk_node* node;
	int			i;
	int 		len;
	
	if(stackid == STACK_A)
		printf("Printing STACKA\n");
	else
		printf("Printing STACKB\n");
	node = stacks[stackid];
	len = (coord_val) _len;
	printf("sdaafff %d len %d\n", G_Y_BEGIN_B == G_Y_BEGIN_A, len);
	if (len < 0)
		return (0);
	height = G_AREAS_HEIGHT / len;
	printf("::: ::: G_AREAS_HEIGHT: %d, len: %d, mod:%d\n", G_AREAS_HEIGHT, len, height%len);
	
	i = len-stk_len(stacks[stackid]) +1;
	i = 0;
	while (node)
	{
		if (stackid == STACK_A)
			print_index_to_A(i, node->index, img, height,  len, y_adjustment(i, G_AREAS_HEIGHT, len));
		else if (stackid == STACK_B)
		{
			print_index_to_B(i, node->index, img, height, len, y_adjustment(i, height, len));
		}
		else 
			return (0);
		node = node->next;
		i++;
		//break;
	}
	return 1;
}

typedef struct s_grp_loop_data {
	t_stk_node*		stacks[2];
	void*			mlx;
	void*			mlx_window;
	t_mlx_img		img;
	int 			len;
} t_grp_loop_data;

int grp_mlx_loop(void *_data)
{
	t_grp_loop_data* data = _data;
	int ret;

	printf("looping \n");

	ret = chk_run_action(data->stacks);
	if (ret <= 0)
	{
		while(1);
	}
	
	printf("\n:::len %d: \n", data->len);
	g_draw_area_A(data->img);
	g_draw_area_B(data->img);
	print_stacks(data->stacks, STACK_A, data->img, data->len);
	print_stacks(data->stacks, STACK_B, data->img, data->len);
	mlx_put_image_to_window(data->mlx, data->mlx_window, data->img.img, 0, 0);
	usleep(G_SLEEP);
	return 1;
}

int main(int argc, char **argv)
{
	void*	mlx;
	void*	mlx_window;
	t_stk_node* 	stacks[2];
	t_stk_node* 	fk_stacks[2]; //TODO delte
	size_t 	len;

	t_mlx_img	img;

	if (argc <= 1)
		return (0);
	if (argc == 2 && argv[1][0] == '\0')
		return (psw_prnt_error());

	len = init_stack_0(&stacks[0], argc, argv + 1);
	if (!stacks[0])
		return (psw_prnt_error());
	stacks[1] = NULL;
	fk_stacks[0] = stacks[0];
	fk_stacks[1] = stacks[0];
	stk_print(fk_stacks[1]);
	printf("\n");

	printf("Strting mlx\n");
	if (!init_mlx_stuff(&mlx, &mlx_window, &img))
		return (1);

	print_stacks(stacks, STACK_A, img, len);
	int i = 0.75 * G_WINDOW_WIDTH;
	int color = 0xffff00ff;
	while (i > 0.25 * G_WINDOW_WIDTH)
	{
//void g_draw_pixel(t_mlx_img img, coord_val x, coord_val y, int color)
		g_draw_pixel(img, i-1, G_MARGIN -0, color);
		g_draw_pixel(img, i-1, G_MARGIN + 1, color);
		g_draw_pixel(img, i-1, G_WINDOW_HEIGHT - G_MARGIN - 0, color);
		g_draw_pixel(img, i-1, G_WINDOW_HEIGHT - G_MARGIN + 1, color);
		i--;
		
	}
	g_draw_area_A(img);
	g_draw_area_B(img);
	
	g_draw_square(img, Point(50,50), Point(50,50), Point(1, 1), 0xff0000aa, 0xff0000aa, G_WINDOW_WIDTH);
	g_draw_square(img, Point(50,200), Point(50,50), Point(1, 1), 0xff00aa00, 0xff00aa00, G_WINDOW_WIDTH);
	mlx_put_image_to_window(mlx, mlx_window, img.img, 0, 0);
//	while(1);
	printf("sdaffff\n");
	//TODO clean the mess lower
	t_grp_loop_data data;
	data.stacks[0] = stacks[0];
	data.stacks[1] = stacks[1];
	data.mlx = mlx;
	data.mlx_window = mlx_window;
	data.img = img;
	data.len = len;
	mlx_loop_hook(mlx, grp_mlx_loop, &data);
	mlx_loop(mlx);
}
