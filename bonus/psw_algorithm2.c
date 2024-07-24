/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   psw_algorithm2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenau-v <jrenau-v@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:56:49 by jrenau-v          #+#    #+#             */
/*   Updated: 2023/02/04 17:50:51 by jrenau-v         ###   ########.fr       */
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
		if (current >= target - 1)
			stk_caller(stacks, "pa");
		else if (current >= target - 3)
		{
			stk_caller(stacks, "pa");
			stk_caller(stacks, "ra");
		}
		else if (!reverse)
			stk_caller(stacks, "rb");
		else
			stk_caller(stacks, "rrb");
		if (current == target)
			return ;
	}
}

void	psw_sorta(t_stk_node *stacks[2])
{
	long int	nxt_target;
	long int	last;
	long int	penult;

	if (stk_len(stacks[0]) < 2)
		return ;
	if (stk_len(stacks[0]) == 2
		&& stacks[0]->index - stacks[0]->next->index == 3)
		return ;
	last = stk_last(stacks[0])->index;
	penult = stk_last(stacks[0])->previous->index;
	if (stacks[0]->index == stacks[0]->next->index + 1)
		stk_caller(stacks, "sa");
	nxt_target = ((long int) stacks[0]->index) - 1;
	if (penult == nxt_target || penult == nxt_target - 1)
		stk_caller(stacks, "rra");
	if (penult == nxt_target || penult == nxt_target - 1)
		stk_caller(stacks, "rra");
	else if (last == nxt_target || last == nxt_target - 1)
		stk_caller(stacks, "rra");
	if (stacks[0]->index > stacks[0]->next->index)
		stk_caller(stacks, "sa");
	if (stacks[0]->index + 1 < nxt_target)
		stk_caller(stacks, "ra");
}
