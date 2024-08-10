#include <stdio.h>
#include <unistd.h>
#include <push_swap.h>
#include <checker.h>
#include "graphics.h"


typedef struct s_grp_loop_data {
	t_stk_node*		stacks[2];
	void*			mlx;
	void*			mlx_window;
	t_mlx_img		img;
	int 			len;
	useconds_t		sleep;
	int				paused;
	int				next_action;
} t_grp_loop_data;

//int init_graphics(void** mlx, void** mlx_window, t_mlx_img* img)
int init_graphics(t_grp_loop_data *loop_data)
{
	t_mlx_img *img = &loop_data->img;
	loop_data->mlx = mlx_init();
	loop_data->mlx_window = mlx_new_window(loop_data->mlx, G_WINDOW_WIDTH, G_WINDOW_HEIGHT, "Push Swap");
	img->img = mlx_new_image(loop_data->mlx, G_WINDOW_WIDTH, G_WINDOW_HEIGHT);
	img->data = mlx_get_data_addr(img->img, &img->bitsxpxl, &img->bytesxline, &img->endian);
	img->bytesxpxl = img->bitsxpxl / 8;
	if (!loop_data->mlx || !loop_data->mlx_window || !img->data || !img->img)
		return (0);	
	//g_draw_square(*img, Point(0,0), Point(G_WINDOW_WIDTH,G_WINDOW_HEIGHT), Point(1,1), 0xff88bbbb, 0x88bbbb, 0);
	g_draw_square(*img, Point(0, 0), Point(G_WINDOW_WIDTH/2 +1, G_WINDOW_HEIGHT), Point(1, 1), 0xff88bbbb, 0xc8e9e9, G_WINDOW_WIDTH/2);
	g_draw_square(*img, Point(G_WINDOW_WIDTH, 0), Point(G_WINDOW_WIDTH/2 +1, G_WINDOW_HEIGHT), Point(-1, 1), 0xff88bbbb, 0xc8e9e9, G_WINDOW_WIDTH/2+5);
	g_draw_area_A(*img);
	g_draw_area_B(*img);

	//print_stacks(data.stacks, STACK_A, data.img, data.len);
	//print_stacks(data.stacks, STACK_B, data.img, data.len);
	mlx_put_image_to_window(loop_data->mlx, loop_data->mlx_window, loop_data->img.img, 0, 0);
	loop_data->sleep = G_SLEEP; 
	loop_data->paused = 0; 
	loop_data->next_action = 0; 
	return 1; // TODO no memfree on NULL
}

int min(int val0, int val1)
{
	if (val0 < val1)
		return (val0);
	return (val1);
}

void print_index_to_A(int y_position, int order_index, t_mlx_img img, coord_val height ,int len, int y_adjustment)
{
	g_draw_square(img,
		//Point(G_X_BEGIN_A, y_position * height + G_MARGIN),
		Point(G_X_BEGIN_A, G_Y_BEGIN_A - y_position * height - min(y_position, y_adjustment)),
		Point(G_AREAS_WIDTH * (order_index+1) / len, height + (y_position < y_adjustment)),
		//Point(-1, 1),
		Point(-1, -1),
		0xffaaffaa, 0xfffefefe,
		G_AREAS_WIDTH
	);
}

void print_index_to_B(int y_position, int order_index, t_mlx_img img, coord_val height ,int len, int y_adjustment)
{
	g_draw_square(img,
		//Point(G_X_BEGIN_B, y_position * height + G_MARGIN),
		Point(G_X_BEGIN_B, G_Y_BEGIN_A - y_position * height - min(y_position, y_adjustment)),
		Point(G_AREAS_WIDTH * (order_index+1) / len, height + (y_position < y_adjustment)),
		//Point(1, 1),
		Point(1, -1),
		0xffaa5566, 0xfffefef,
		G_AREAS_WIDTH
	);
}

int print_stacks(t_stk_node* stacks[2], t_stack_id stackid, t_mlx_img img, size_t _len)
{
	coord_val height;
	t_stk_node* node;
	int			i;
	int 		len;
	int			lonely_pixels;
	
	node = stacks[stackid];
	len = (coord_val) _len;
	if (len < -1)
		return (0);
	height = G_AREAS_HEIGHT / len;
	lonely_pixels = G_AREAS_HEIGHT % len;
	
	i = stk_len(stacks[stackid]) - 1;
	while (node)
	{
		if (stackid == STACK_A)
			print_index_to_A(i, node->index, img, height, len, lonely_pixels);
		else if (stackid == STACK_B)
			print_index_to_B(i, node->index, img, height, len, lonely_pixels);
		else 
			return (0);
		node = node->next;
		i--;
	}
	return 1;
}

int grp_key_press(int key, t_grp_loop_data *data)
{
	printf("Pressed key: %d, %d\n", key, G_SPACE);

	if (key == G_SPACE)
	{
		data->paused = !data->paused;
		printf("paused: %d\n", data->paused);
	}
	else if (key == G_RIGHT)
		data->next_action = 1;
	else if (key == G_INTRO)
		data->next_action = 1;
	else if (key == G_CARRIAGE_RET)
		data->next_action = 1;
	else if (key == G_PLUS)
		data->sleep /= 1.1;
	else if (key == G_MINUS && data->sleep < 1000000000)
	{
		if (data->sleep == 0)
			data->sleep = 1;
		else
			data->sleep *= 1.1;
	}
	else if (key == G_ESC)
	{
		mlx_destroy_window(data->mlx, data->mlx_window);
		mlx_destroy_image(data->mlx, data->img.img);
		stk_clear(&data->stacks[0]);
		stk_clear(&data->stacks[1]);
		exit(1);
	}
	return (1);
}

int grp_key_relese(int key, t_grp_loop_data *data)
{
	(void) data;
	printf("release\n");
	printf("Key: %d\n", key);
	return (1);
}

int grp_mlx_loop(void *_data)
{
	t_grp_loop_data* data = _data;
	int ret;
	
//	printf("paused: %d, action: %d\n", data->paused, data->next_action);
	if (data->paused && !data->next_action)
		return (0);
	data->next_action = 0;


	ret = chk_run_action(data->stacks);
	if (ret <= 0)
	{
		//while(1);
	}
	
	g_draw_area_A(data->img);
	g_draw_area_B(data->img);
	print_stacks(data->stacks, STACK_A, data->img, data->len);
	print_stacks(data->stacks, STACK_B, data->img, data->len);
	mlx_put_image_to_window(data->mlx, data->mlx_window, data->img.img, 0, 0);
	usleep(data->sleep);
	return 1;
}

int presss(int key, t_grp_loop_data data)
{
	(void) data;
	(void) key;
	
	printf("Pressed a key\n");
	return (1);
}
int _main(void)
{
	t_grp_loop_data data;

	data.mlx= mlx_init();

	data.mlx_window = mlx_new_window(data.mlx, 500, 500, "fkkkkk this shit");
	mlx_hook(data.mlx_window, 2, 1L << 0, presss, &data);
	mlx_loop(data.mlx);
	return (0);
}

int main(int argc, char **argv)
{
	t_grp_loop_data data;
	printf("HAREAS_WIDTH: %d, HAREAS_HEIGHT: %d\n", G_AREAS_WIDTH, G_AREAS_HEIGHT);
	int len;
	t_stk_node *stacks[2];

	if (!init_stacks(argc, argv, stacks, &len))
		return (0);

	if (argc <= 1)
		return (0);
	if (argc == 2 && argv[1][0] == '\0')
		return (psw_prnt_error());
	data.len = init_stack_0(&data.stacks[0], argc, argv + 1);
	if (!data.stacks[0])
		return (psw_prnt_error());
	data.stacks[1] = NULL;

	if (data.len > G_AREAS_HEIGHT)
		return (psw_str_prnt_error("Unable to print so much numbers. Increase height resolution\n"));

	printf("Starting mlx\n");
	if (!init_graphics(&data))
	{
		printf("Error on init window\n");
		return (1);
	}

	//g_draw_square(data.img, Point(250,250), Point(50,50), Point(1,1), 0x0066ff66, 0, 0);
	//g_draw_square(data.img, Point(250,250), Point(50,50), Point(1,-1), 0x006666ff, 0);
	//g_draw_square(data.img, Point(250,250), Point(50,50), Point(-1,1), 0x00ff66ff, 0);
	//g_draw_square(data.img, Point(250,250), Point(50,50), Point(-1,-1), 0x00ffffff, 0);
	
	mlx_hook(data.mlx_window, 17, 0, grp_key_press, &data);
	mlx_hook(data.mlx_window, 2, 1L << 0, grp_key_press, &data);
	mlx_hook(data.mlx_window, 3, 1L << 1, grp_key_relese, &data);
	mlx_put_image_to_window(data.mlx, data.mlx_window, data.img.img, 0, 0);
	mlx_loop_hook(data.mlx, grp_mlx_loop,&data);
	mlx_loop(data.mlx);

	return (0);
}
