#include <graphics.h>

typedef enum s_grp_loop_data_lvl
{
	LVL_STACKS,
	LVL_MLX,
	LVL_MLX_WINDOW,
	LVL_MLX_IMG,
	LVL_ALL
} t_grp_loop_data_lvl;

int clear_loop_data(t_grp_loop_data *loop_dta, t_grp_loop_data_lvl lvl, char *err_str)
{
	write(1, err_str, ft_strlen(err_str));
		stk_clear(&loop_dta->stacks[0]);
		stk_clear(&loop_dta->stacks[1]);
		exit(1);
	if (LVL_MLX_IMG <= lvl)
		mlx_destroy_image(loop_dta->mlx, loop_dta->img.img);
	if (LVL_MLX_WINDOW <= lvl)
		mlx_destroy_window(loop_dta->mlx, loop_dta->mlx_window);
	if (LVL_MLX <= lvl)
		free(loop_dta->mlx);
	if (LVL_STACKS <= lvl)
	{
		stk_clear(&loop_dta->stacks[0]);
		stk_clear(&loop_dta->stacks[1]);
	}
}

	//TODO leaks
int grp_init_graphics(t_grp_loop_data *loop_dta)
{
	t_mlx_img *img = &loop_dta->img;
	loop_dta->mlx = mlx_init();
	if (!loop_dta->mlx)
		return (clear_loop_data(loop_dta, LVL_MLX, "ERR: init mlx\n"));
	loop_dta->mlx_window = mlx_new_window(
		loop_dta->mlx, G_WINDOW_WIDTH, G_WINDOW_HEIGHT, "Push Swap");
	if (!loop_dta->mlx_window)
		return (clear_loop_data(loop_dta, LVL_MLX_WINDOW, "ERR: init window\n"));
	img->img = mlx_new_image(loop_dta->mlx, G_WINDOW_WIDTH, G_WINDOW_HEIGHT);
	if (!loop_dta->img.img)
		return (clear_loop_data(loop_dta, LVL_MLX_IMG, "ERR: init img\n"));
	img->data = mlx_get_data_addr(
		img->img, &img->bitsxpxl, &img->bytesxline, &img->endian);
	img->bytesxpxl = img->bitsxpxl / 8;
	loop_dta->sleep = _G_SLEEP; 
	loop_dta->paused = 1; 
	loop_dta->next_action = 0; 
	grp_draw_background(img);
	grp_draw_area_A(*img);
	grp_draw_area_B(*img);
	grp_print_stack(loop_dta->stacks, STACK_A, loop_dta->img, loop_dta->len);
	grp_print_stack(loop_dta->stacks, STACK_B, loop_dta->img, loop_dta->len);
	mlx_put_image_to_window(loop_dta->mlx, loop_dta->mlx_window,
		loop_dta->img.img, 0, 0);
	return 1;
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
	return (1);
}

int grp_key_relese(int key, t_grp_loop_data *data)
{
	(void) key;
	(void) data;
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
	grp_print_stack(data->stacks, STACK_A, data->img, data->len);
	grp_print_stack(data->stacks, STACK_B, data->img, data->len);
	mlx_put_image_to_window(data->mlx, data->mlx_window, data->img.img, 0, 0);
	usleep(data->sleep);
	return 1;
}
