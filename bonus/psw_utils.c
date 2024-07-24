/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenau-v <jrenau-v@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:12:37 by jrenau-v          #+#    #+#             */
/*   Updated: 2023/02/08 22:06:03 by jrenau-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "push_swap.h"

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
