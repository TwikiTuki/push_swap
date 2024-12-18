
#include "push_swap.h"

t_stk_node	*stk_last(t_stk_node *stack)
{
	if (!stack)
		return (NULL);
	while (stack->next)
		stack = stack->next;
	return (stack);
}

t_stk_node	*stk_clear( t_stk_node **stack)
{
	t_stk_node	*node;
	t_stk_node	*next;

	node = *stack;
	*stack = NULL;
	while (node)
	{
		next = node->next;
		free(node);
		node = next;
	}
	return (NULL);
}

void	stk_print(t_stk_node	*stk)
{
	size_t	bnds[4];
	size_t	i;
	size_t	ln;
	int		chunck;

	if (stk == NULL)
		ft_printf("(empty)");
	if (stk == NULL)
		return ;
	ln = stk_len(stk);
	i = 0;
	chunck = 0;
	psw_boundaries(bnds, chunck, ln);
	while (stk)
	{
		if (i == bnds[0] || i == bnds[1] || i == bnds[2] || i == bnds[3])
			ft_printf("*");
		if (i == bnds[3])
			ft_printf("*");
		if (i == bnds[3])
			psw_boundaries(bnds, ++chunck, ln);
		ft_printf("%d:%d ", stk->index, stk->value);
		i++;
		stk = stk->next;
	}
}

int	psw_getindexes(t_stk_node **start)
{
	t_stk_node	*to_sort;
	t_stk_node	*to_cmpr;		

	to_sort = *start;
	while (to_sort)
	{
		to_sort->index = 0;
		to_cmpr = *start;
		while (to_cmpr)
		{
			if (to_sort->value > to_cmpr->value)
				to_sort->index += 1;
			if (to_sort->value == to_cmpr->value && to_sort != to_cmpr)
			{
				stk_clear(start);
				return (0);
			}
			to_cmpr = to_cmpr->next;
		}
		to_sort = to_sort->next;
	}
	return (1);
}
