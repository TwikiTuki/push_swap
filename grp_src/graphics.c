#include <graphics.h>

int main(int argc, char **argv)
{
	t_grp_loop_data data;

	printf("init stacks %d\n", argc);
	if (!init_stacks(argc, argv, data.stacks, &data.len))
		return (0);
	printf("stacks initialized\n");
	if (data.stacks[0] == 0)
		return(0);
	if (data.len > G_AREAS_HEIGHT)
		return (psw_str_prnt_error(
			"Unable to print so much numbers. Increase height resolution\n"));
	if (!grp_init_graphics(&data))
	{
		printf("Error on init window\n");
		return (1);
	}
	mlx_hook(data.mlx_window, 17, 0, grp_key_press, &data);
	mlx_hook(data.mlx_window, 2, 1L << 0, grp_key_press, &data);
	mlx_hook(data.mlx_window, 3, 1L << 1, grp_key_relese, &data);
	mlx_loop_hook(data.mlx, grp_mlx_loop,&data);
	mlx_loop(data.mlx);
	return (0);
}
