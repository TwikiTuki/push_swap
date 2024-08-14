/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   psw_algorithm2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenau-v <jrenau-v@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:56:49 by jrenau-v          #+#    #+#             */
/*   Updated: 2023/02/04 14:53:14 by jrenau-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

size_t	stk_max_index(t_stk_node *stack)
{
	size_t	max;

	max = 0;
	while (stack)
	{
		if (stack->index > max)
			max = stack->index;
		stack = stack->next;
	}
	return (max);
}

int	psw_should_reverse(t_stk_node *stack, size_t target)
{
	size_t	len;
	size_t	position;

	len = stk_len(stack);
	position = 0;
	while (stack->index != target)
	{
		stack = stack->next;
		position++;
	}
	return ((len - position) < position);
}

void	psw_pushback(t_stk_node *stacks[2])
{
	long int	target; 	
	long int	current;
	int			reverse;

	target = stk_max_index(stacks[1]);
	reverse = psw_should_reverse(stacks[1], target);
	while (1)
	{
		current = stacks[1]->index;
		if (current >= target - 3)
		{
			stk_caller_verbose(stacks, "pa");
			if (current <= target - 2)
				stk_caller_verbose(stacks, "ra");
		}
		else if (!reverse)
			stk_caller_verbose(stacks, "rb");
		else
			stk_caller_verbose(stacks, "rrb");
		if (current == target)
			return ;
	}
}

void	psw_sorta(t_stk_node *stacks[2])
{
	t_stk_node  *lastNode;
	long int	nxt_target;
	long int	last;
	long int	penult;

	if (stk_len(stacks[0]) < 2)
		return ;
	if (stk_len(stacks[0]) == 2
		&& stacks[0]->index - stacks[0]->next->index == 3)
		return ;
	lastNode = stk_last(stacks[0]);
	last = lastNode->index;
	penult = lastNode->previous->index;
	if (stacks[0]->index == stacks[0]->next->index + 1)
		stk_caller_verbose(stacks, "sa");
	nxt_target = ((long int) stacks[0]->index) - 1;
	if (penult == nxt_target || penult == nxt_target - 1)
	{
		stk_caller_verbose(stacks, "rra");
		stk_caller_verbose(stacks, "rra");
	}
	else if (last == nxt_target || last == nxt_target - 1)
		stk_caller_verbose(stacks, "rra");
	if (stacks[0]->index > stacks[0]->next->index)
		stk_caller_verbose(stacks, "sa");
	if (stacks[0]->index + 1 < nxt_target)
		stk_caller_verbose(stacks, "ra");
}
