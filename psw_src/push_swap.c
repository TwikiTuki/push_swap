/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenau-v <jrenau-v@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 11:12:37 by jrenau-v          #+#    #+#             */
/*   Updated: 2024/08/04 16:48:28 by jrenau-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "graphics.h"
#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stk_node	*stacks[2];
	int			len;

	if (!init_stacks(argc, argv, stacks, &len))
		return (0);

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
