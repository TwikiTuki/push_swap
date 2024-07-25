/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   psw_shorts.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenau-v <jrenau-v@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:15:38 by jrenau-v          #+#    #+#             */
/*   Updated: 2023/02/03 21:56:25 by jrenau-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

#define COMBINATIONS ((char*[]) {"012\0", "021\0", "120\0", "102\0", "201\0", "210\0"})
#define SOLUTIONS ((char*[]) {"", "sa\nra\n\0", "rra\n\0",  "sa\n\0", "ra\n\0", "sa\nrra\n\0"})

#define LEN 6

void	stk_strcaller(t_stk_node *stacks[], char *str)
{
	char	action[4];
	int		i;

	i = 0;
	while (*str)
	{
		if (*str == '\n')
		{
			action[i] = '\0';
			stk_caller(stacks, action);
			i = 0;
		}
		else
		{
			action[i] = *str;
			i++;
		}
		str++;
	}
}

void	stk_size5(t_stk_node *stacks[2])
{
	unsigned int	max_index;

	max_index = stk_len(stacks[0]) - 1;
	while (stk_len(stacks[0]) > 3)
		stk_caller(stacks, "pb");
	stk_size3(stacks);
	if (stacks[1]->next && stacks[1]->index < stacks[1]->next->index)
		stk_caller(stacks, "sb");
	if (stacks[1]->index == max_index)
		stk_caller(stacks, "pa");
	while (stk_len(stacks[1]))
	{
		if (stk_last(stacks[0])->index < stacks[1]->index
			&& stacks[0]->index > stacks[1]->index)
			stk_caller(stacks, "pa");
		else if (stacks[1]->next && stacks[0]->index == 2
			&& stacks[1]->index == 1 && stacks[1]->next->index == 0)
			stk_caller(stacks, "pa");
		else if (stacks[1]->index == 0 && stacks[0]->index == 1)
			stk_caller(stacks, "pa");
		else
			stk_caller(stacks, "rra");
	}
	while (stacks[0]->index != 0)
		stk_caller(stacks, "rra");
}

static char	get_index(t_stk_node *stack, int value)
{
	t_stk_node	*node;
	int			index;

	node = stack;
	index = 0;
	while (node)
	{
		index += value > node->value;
		node = node -> next;
	}
	return (index + '0');
}

void	stk_size3(t_stk_node *stacks[2])
{
	t_stk_node	*stka;
	char		str[4];
	int			i;

	if (stk_len(stacks[0]) == 2)
	{
		if (stacks[0]->index > stacks[0]->next->index)
			stk_caller(stacks, "sa");
		return ;
	}
	stka = stacks[0];
	i = 0;
	while (stka)
	{
		str[i++] = get_index(stacks[0], stka->value);
		stka = stka->next;
	}
	str[3] = '\0';
	i = 0;
	while (ft_strncmp(str, COMBINATIONS[i], 4) && i < LEN)	
		i++;
	stk_strcaller(stacks, (SOLUTIONS[i]));
}
