/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenau-v <jrenau-v@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:12:37 by jrenau-v          #+#    #+#             */
/*   Updated: 2024/07/31 18:32:08 by jrenau-v         ###   ########.fr       */
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


void g_draw_area_A(t_mlx_img img)
{
	int		color;
	char	*pxlbyte;

	char	*begin;
	char	*end;

	
	begin = img.data +  G_X_BEGIN_A * img.bytesxpxl + (G_Y_BEGIN_B + 0) * img.bytesxline;
	end = begin + (G_WINDOW_WIDTH * G_WINDOW_HEIGHT * 4);
	printf("begin: %p, end: %p, diff %d \n",begin, end, (int) (begin - end));
	printf("G_X_BEGIN_A: %d, G_Y_BEGIN_B: %d\n", G_X_BEGIN_A, G_Y_BEGIN_B);
	printf("bytesxpxl: %d, bytesxline: %d\n", img.bytesxpxl, img.bytesxline);

/*
	pxlbyte = begin;
	int count = 0;
	while (1)
	{
		printf("%d:: *begin: %p, *curr: %p, *end: %p, *diff: %d\n", count, begin, pxlbyte, end, (int) (end - pxlbyte)); 
		*pxlbyte = 0xff;
		pxlbyte--;
		count++;
	}
*/

	for (int i = G_AREAS_HEIGHT-1; i >= 0; i--)
	{
		pxlbyte = img.data + G_X_BEGIN_A * img.bytesxpxl + (G_Y_BEGIN_A - i) * img.bytesxline;
		for (int j = G_AREAS_WIDTH-1; j >= 0; j--)
		{
//			pxlbyte -= 4;
			printf("i: %d j: %d pxl %d\n", i, j, (int) (pxlbyte - begin));
			color = 0xff77aaaa;
//printf("sdaf\n");
/*
			for (int sdaf = 0; sdaf < 4; sdaf++)
			{
				printf("current: %p\n", pxlbyte + sdaf);
				*(pxlbyte - sdaf) = 0xff;
//				printf("fasd\n");
			}
*/
			*((int*) pxlbyte) = color;
			pxlbyte -= img.bytesxpxl;
printf("kook\n");
		}
	}
}


void mlx_main(int argc, char **argv)
{
	void*	mlx;
	void*	mlx_window;
//	void*	mlx_img; int 	pxl;
//	int		bitsxpxl;
//	int		bitsxline;
//	int		endian;
	int 	color;
	//int 	bytesxpxl;
	int		sdaf;
	int 	pxl;

	t_mlx_img	img;
	
	//char*	mlx_img_data;

	(void)	argc;
	(void)	argv;

	mlx = mlx_init();
	mlx_window = mlx_new_window(mlx, G_WINDOW_WIDTH, G_WINDOW_HEIGHT, "Push Swap");
	img.img = mlx_new_image(mlx, G_WINDOW_WIDTH, G_WINDOW_HEIGHT);
	img.data = mlx_get_data_addr(img.img, &sdaf, &img.bytesxline, &img.endian);
	img.bitsxpxl = sdaf;
	img.bytesxpxl = img.bitsxpxl / 8;
	for (int i = 0; i < G_WINDOW_HEIGHT; i++)
	{
		pxl = G_WINDOW_WIDTH * i;
		//printf("i: %d pxl %d\n", i, pxl);
		for (int j = 0; j < G_WINDOW_WIDTH; j++)
		{
			color = 0x88888888;
			for (int k = 0; k < img.bytesxpxl; k++)
				*(img.data+pxl+k) = 0x88;
			*((int*)img.data + pxl) = color;
			//printf("i: %d j: %d pxl %d\n", i, j, pxl);
			pxl++;
		}
	}
	g_draw_area_A(img);
	mlx_put_image_to_window(mlx, mlx_window, img.img, 0, 0);
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
