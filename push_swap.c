/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenau-v <jrenau-v@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:12:37 by jrenau-v          #+#    #+#             */
/*   Updated: 2024/07/30 17:31:01 by jrenau-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "push_swap.h"

static void	free_matrix(void **list)
{
	size_t	i;

	i = 0;
	while (list[i])
		free(list[i++]);
	free(list);
	return ;
}

static size_t	init_stack_0(t_stk_node **stack, int argc, char **argv)
{
	char	**args;
	size_t	len;

	*stack = NULL;
	if (argc == 2 && ft_strchr(argv[1], ' '))
	{
		args = ft_split(argv[1], ' ');
		if (!args)
			return (0);
		len = 0;
		while (args[len])
			len++;
	}
	else
	{
		args = argv + 1;
		len = argc - 1;
	}
	if (psw_check(args))
		*stack = stk_init(args, len);
	if (argc == 2)
	{
		printf("Wild free\n");
		free_matrix((void **) args);
	}
	return (len);
}

void mlx_main(int argc, char **argv)
{
	void*	mlx;
	void*	mlx_window;
	void*	mlx_img;
//	int 	pxl;
	int		bitsxpxl;
	int		bitsxline;
	int		endian;
	
	char*	mlx_img_data;

	(void)	argc;
	(void)	argv;

	mlx = mlx_init();
printf("koko\n");
	mlx_window = mlx_new_window(mlx, 600, 600, "Push Swap");
printf("sdaf\n");
	mlx_img = mlx_new_image(mlx, 600, 600);
printf("fasdyy\n");
	mlx_img_data = mlx_get_data_addr(mlx_img, &bitsxpxl, &bitsxline, &endian);
	printf("bits per pixel: %d, bits per line: %d, endian %d\n", bitsxpxl, bitsxline, endian);
	for (int i = 0; i < bitsxline * 50; i++)
	{
		int color = 0;
		color += 254;
		color = color << 8;
		color += 254;
		color = color << 8;
		color += 0;
		color = color << 8;
		color += 0;
		*((int*)mlx_img_data + i) = color;
	}
	mlx_put_image_to_window(mlx, mlx_window, mlx_img, 0, 0);
	mlx_loop(mlx);
}

int	main(int argc, char **argv)
{
	t_stk_node	*stacks[2];
	int			len;

	mlx_main(argc, argv);
	return(0);

	if (argc <= 1)
		return (0);
	if (argc == 2 && argv[1][0] == '\0')
		return (psw_prnt_error());
	len = init_stack_0(&stacks[0], argc, argv);
	stacks[1] = NULL;
	if (!stacks[0])
		return (psw_prnt_error());
	if (len < 2 || check_sorted(stacks[0]))
	{
		stk_clear(&stacks[0]);
		return (1);
	}
	if (stk_len(stacks[0]) <= 3)
		stk_size3(stacks);
	else if (stk_len(stacks[0]) <= 5)
		stk_size5(stacks);
	else
		psw_long_sort(stacks);
	stk_clear(&stacks[0]);
}
