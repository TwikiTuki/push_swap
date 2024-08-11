/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   psw_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenau-v <jrenau-v@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:12:37 by jrenau-v          #+#    #+#             */
/*   Updated: 2024/08/04 16:49:50 by jrenau-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "push_swap.h"

int init_stacks(int argc, char **argv, t_stk_node *stacks[2], int* len)
{
	if (argc <= 1)
		return (0);
	if (argc == 2 && argv[1][0] == '\0')
		return (psw_prnt_error());
	*len = init_stack_0(&stacks[0], argc, argv + 1);
	stacks[1] = NULL;
	if (!stacks[0])
		return (psw_prnt_error());		
	return (1);
}

size_t	init_stack_0(t_stk_node **stack, int argc, char **argv)
{
	char	**args;
	size_t	len;

	*stack = NULL;
	if (argc == 2 && ft_strchr(argv[0], ' '))
	{
		args = ft_split(argv[0], ' ');
		if (!args)
			return (0);
		len = 0;
		while (args[len])
			len++;
	}
	else
	{
		args = argv;
		len = argc - 1;
	}
	if (psw_check(args))
		*stack = stk_init(args, len);
	if (argc == 2)
		free_matrix((void **) args);
	return (len);
}


int	psw_str_prnt_error(char *str)
{
	write(2, "Error: ", 7);
	write(2, str, ft_strlen(str));
	return (0);
}

int	psw_prnt_error(void)
{
	write(2, "Error\n", 6);
	return (0);
}

int	check_sorted(t_stk_node *stack)
{
	unsigned int	i;

	i = 0;
	while (stack)
	{
		if (stack->index != i)
			return (0);
		i++;
		stack = stack->next;
	}
	return (1);
}

void	free_matrix(void **list)
{
	size_t	i;

	i = 0;
	while (list[i])
		free(list[i++]);
	free(list);
	return ;
}
