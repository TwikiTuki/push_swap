
#ifndef CHECKER_H
# define CHECKER_H
# include "push_swap.h"
# include "../libft/get_next_line/get_next_line.h"
/* chk_utils.c */
int	chk_check_action(char *action);
int	chk_run_actions(t_stk_node *stacks[2]);
int	chk_run_action(t_stk_node *stacks[2]);
#endif
