#include <graphics.h>

int grp_init_graphics(t_grp_loop_data *loop_data)
{
	t_mlx_img *img = &loop_data->img;
	loop_data->mlx = mlx_init();
	loop_data->mlx_window = mlx_new_window(
		loop_data->mlx, G_WINDOW_WIDTH, G_WINDOW_HEIGHT, "Push Swap");
	img->img = mlx_new_image(loop_data->mlx, G_WINDOW_WIDTH, G_WINDOW_HEIGHT);
	img->data = mlx_get_data_addr(
		img->img, &img->bitsxpxl, &img->bytesxline, &img->endian);
	img->bytesxpxl = img->bitsxpxl / 8;
	if (!loop_data->mlx || !loop_data->mlx_window || !img->data || !img->img)
		return (0);	
	grp_draw_background(img);
	grp_draw_area_A(*img);
	grp_draw_area_B(*img);
	mlx_put_image_to_window(loop_data->mlx, loop_data->mlx_window,
		loop_data->img.img, 0, 0);
	loop_data->sleep = G_SLEEP; 
	loop_data->paused = 0; 
	loop_data->next_action = 0; 
	mlx_put_image_to_window(loop_data->mlx, loop_data->mlx_window,
		loop_data->img.img, 0, 0);
	return 1; // TODO no memfree on NULL
}

int grp_key_press(int key, t_grp_loop_data *data)
{
	if (key == G_SPACE)
		data->paused = !data->paused;
	else if (key == G_RIGHT)
		data->next_action = 1;
	else if (key == G_INTRO)
		data->next_action = 1;
	else if (key == G_CARRIAGE_RET)
		data->next_action = 1;
	else if (key == G_PLUS)
		data->sleep = data->sleep >> 1;
	else if (key == G_MINUS && data->sleep <= G_MAX_SLEEP)
		data->sleep = 0 ? 1 : data->sleep << 1;
	else if (key == G_ESC)
	{
		mlx_destroy_window(data->mlx, data->mlx_window);
		mlx_destroy_image(data->mlx, data->img.img);
		stk_clear(&data->stacks[0]);
		stk_clear(&data->stacks[1]);
		exit(1);
	}
	printf("sleep: %u\n", data->sleep);
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
	
	if (data->paused && !data->next_action)
		return (0);
	data->next_action = 0;
	ret = chk_run_action(data->stacks);
	if (ret <= 0)
		return (0);
	grp_draw_area_A(data->img);
	grp_draw_area_B(data->img);
	grp_print_stacks(data->stacks, STACK_A, data->img, data->len);
	grp_print_stacks(data->stacks, STACK_B, data->img, data->len);
	mlx_put_image_to_window(data->mlx, data->mlx_window, data->img.img, 0, 0);
	usleep(data->sleep);
	return 1;
}
