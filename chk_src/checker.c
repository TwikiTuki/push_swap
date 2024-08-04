/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenau-v <jrenau-v@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:12:37 by jrenau-v          #+#    #+#             */
/*   Updated: 2024/08/04 16:51:21 by jrenau-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "push_swap.h"
#include "checker.h"

/*
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
	if (argc == 2 && ft_strchr(argv[1], ' '))
		free_matrix((void **) args);
	return (len);
}
*/

int	main(int argc, char **argv)
{
	t_stk_node	*stacks[2];

	if (argc <= 1)
		return (0);
	if (argc == 2 && argv[1][0] == '\0')
		return (psw_prnt_error());
	init_stack_0(&stacks[0], argc, argv);
	stacks[1] = NULL;
	if (!stacks[0])
		return (psw_prnt_error());
	stacks[1] = NULL;
	if (!chk_run_actions(stacks))
		return (0);
	if (check_sorted(stacks[0]) && stacks[1] == NULL)
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	stk_clear(&stacks[0]);
}