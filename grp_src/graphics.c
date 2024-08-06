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
	g_draw_square(*img, Point(0,0), Point(G_WINDOW_WIDTH,G_WINDOW_HEIGHT), Point(1,1), 0xff88bbbb, 0x88bbbb);
	g_draw_area_A(*img);
	g_draw_area_B(*img);
	return 1; // TODO no memfree on NULL
}


void print_index_to_A(int y_position, int order_index, t_mlx_img img, coord_val height ,int len)
{
	g_draw_square(img, Point(G_X_BEGIN_A, y_position * height + G_MARGIN), Point(G_AREAS_WIDTH * (order_index+1) / len, height), Point(-1, 1), 0xffaaffaa, 0xfffefefe);
	//g_draw_square(img, Point(G_X_BEGIN_A, G_Y_BEGIN_A), Point(20,20), Point(1, 1), 0xff000000, 0x00000000);
}

void print_index_to_B(int y_position, int order_index, t_mlx_img img, coord_val height ,int len)
{
	printf("STACK_B: y_position: %d, order_index: %d, len: %d\n", y_position, order_index, len);
	g_draw_square(img, Point(G_X_BEGIN_B, y_position * height + G_MARGIN), Point(G_AREAS_WIDTH * (order_index+1) / len, height), Point(1, 1),  0xffaa5566, 0xfffefefe);
}

int print_stacks(t_stk_node* stacks[2], t_stack_id stackid, t_mlx_img img, size_t _len)
{
	coord_val height;
	t_stk_node* node;
	int			i;
	int 		len;
	
	node = stacks[stackid];
	len = (coord_val) _len;
	printf("::: ::: len: %d\n", len);
	if (len < 0)
		return (0);
	height = G_AREAS_HEIGHT / len;
	
	i = len-stk_len(stacks[stackid]);
	while (node)
	{
		if (stackid == STACK_A)
			print_index_to_A(i, node->index, img, height, len);
		else if (stackid == STACK_B)
			print_index_to_B(i, node->index, img, height, len);
		else 
			return (0);
		node = node->next;
		i++;
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
	//if (!print_stacks(fk_stacks, STACK_B, img, len))
	//	printf("fKKK stk B\n");
	/*
	*/

	//g_draw_square(img, Point(250,250), Point(50,50), Point(1,1), 0x0066ff66, 0);
	//g_draw_square(img, Point(250,250), Point(50,50), Point(1,-1), 0x006666ff, 0);
	//g_draw_square(img, Point(250,250), Point(50,50), Point(-1,1), 0x00ff66ff, 0);
	//g_draw_square(img, Point(250,250), Point(50,50), Point(-1,-1), 0x00ffffff, 0);
	
	mlx_put_image_to_window(mlx, mlx_window, img.img, 0, 0);
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
