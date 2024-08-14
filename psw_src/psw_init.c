#include "push_swap.h"

int init_stacks(int argc, char **argv, t_stk_node *stacks[2], int* len)
{
	if (argc <= 2)
		return(psw_str_prnt_error("Invalid number of arguments\n"));
	if (argc == 2 && argv[1][0] == '\0')
		return (psw_prnt_error());
	*len = init_stack_0(&stacks[0], argc - 1, argv + 1);
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
	if (argc == 1 && ft_strchr(argv[0], ' '))
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
		len = argc;
	}
	if (psw_check(args))
		*stack = stk_init(args, len);
	if (argc == 1)
		free_matrix((void **) args);
	return (len);
}

t_stk_node	*stk_init(char **numbers, size_t len)
{
	t_stk_node	*nw_node;
	t_stk_node	*lst_node;

	nw_node = NULL;
	lst_node = NULL;
	while (len--)
	{
		nw_node = malloc(sizeof (t_stk_node));
		if (!nw_node)
			return (stk_clear(&lst_node));
		nw_node->value = ft_atoi(numbers[len]);
		nw_node->previous = NULL;
		if (!lst_node)
			nw_node->next = NULL;
		else
		{
			nw_node->next = lst_node;
			lst_node->previous = nw_node;
		}
		lst_node = nw_node;
	}
	if (!psw_getindexes(&nw_node))
		return (stk_clear(&nw_node));
	return (nw_node);
}
