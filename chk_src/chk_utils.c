
#include "checker.h"

int	chk_check_action(char *action)
{
	if (ft_strchr("rps", action[0]))
	{
		if (ft_strchr("ab", action[1]) != NULL && ft_strlen(action) == 2)
			return (1);
		if (action[0] == action[1] && ft_strlen(action) == 2)
			return (1);
		if (ft_strlen(action) == 3 && action [0] == 'r' && action[1] == 'r')
			return (ft_strchr("abr", action[2]) != NULL);
	}
	else
		return (0);
	return (0);
}

int	chk_run_action(t_stk_node *stacks[2])
{
	char	*action;
	int		i;

	action = get_next_line(0);
	if (!action)
		return (-1);
	i = 0;
	while (action[i] && action[i] != '\n')
		i++;
	action[i] = '\0';
	if (!chk_check_action(action))
	{
		free(action);
		stk_clear(&stacks[0]);
		stk_clear(&stacks[1]);
		return (psw_prnt_error());
	}
	stk_caller(stacks, action);
	free(action);
	return (1);
}

int	chk_run_actions(t_stk_node *stacks[2])
{
	int ret;

	while (1)
	{
		ret = chk_run_action(stacks);
		if (ret <= 0)
			return (ret);
	}
	return (1);
}
