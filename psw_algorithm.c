/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   psw_algrothm.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenau-v <jrenau-v@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 15:12:51 by jrenau-v          #+#    #+#             */
/*   Updated: 2023/02/03 21:18:12 by jrenau-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	n_chuncks(size_t len)
{
	if (len <= 100)
		return (3);
	if (len <= 500)
		return (7);
	else
		return (15);
}

void	psw_boundaries(size_t bounds[], int chunck, size_t ln)
{
	unsigned int	size;
	unsigned int	size_up;
	unsigned int	size_down;

	size = ln / n_chuncks(ln) + ((size_t) chunck < (ln % n_chuncks(ln))); 
	size_up = size / 2;
	size_down = size / 2 + size % 2;
	bounds[0] = bounds[3] + 1;				//TODO define smth
	bounds[2] = bounds[0] + size_down - 1;
	bounds[1] = bounds[2] + 1;
	bounds[3] = bounds[1] + size_up - 1;
}	

size_t	stk_len(t_stk_node *stack)
{
	size_t	len;

	len = 0;
	while (stack)
	{
		len++;
		stack = stack -> next;
	}
	return (len);
}

void	psw_semisort(t_stk_node *stacks[])
{
	size_t			bounds[4];
	size_t			len;
	size_t			orig_len;
	int				chunck;	

	chunck = 0;
	bounds[3] = 0 - 1;
	orig_len = stk_len(stacks[0]);
	while (chunck++ < n_chuncks(orig_len))
	{
		len = stk_len(stacks[0]);
		psw_boundaries(bounds, chunck - 1, orig_len);
		while (len--)
		{
			if ((stacks[0]->index >= bounds[0])
				&& (stacks[0]->index <= bounds[3]))
			{
				stk_caller(stacks, "pb");
				if (stacks[1]->index > bounds[2])
					stk_caller(stacks, "rb");
			}
			else
				stk_caller(stacks, "ra");
		}
	}
}

void	psw_long_sort(t_stk_node *stacks[])
{
	psw_semisort(stacks);
	psw_debug_log("semisorted \n", 0);
	while (stacks[1])
	{
		psw_pushback(stacks);
		psw_debug_log("pushed back \n", 0);
		psw_sorta(stacks);
		psw_debug_log("sorted a\n", 0);
	}
}
