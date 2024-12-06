
#include <stdlib.h>
#include "push_swap.h"


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
