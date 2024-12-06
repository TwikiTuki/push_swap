
#include <stdlib.h>
#include "push_swap.h"
#include "checker.h"

int	main(int argc, char **argv)
{
	t_stk_node	*stacks[2];
	int			len;

	if (!init_stacks(argc, argv, stacks, &len))
		return (0);
	if (!chk_run_actions(stacks))
		return (0);
	if (check_sorted(stacks[0]) && stacks[1] == NULL)
		ft_printf("OK\n");
	else
		ft_printf("KO\n");
	stk_clear(&stacks[0]);
}
