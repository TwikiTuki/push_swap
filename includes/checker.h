/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenau-v <jrenau-v@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 16:10:58 by jrenau-v          #+#    #+#             */
/*   Updated: 2023/02/04 17:47:31 by jrenau-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H
# include "push_swap.h"
# include "../libft/get_next_line/get_next_line.h"
/* chk_utils.c */
int	chk_check_action(char *action);
int	chk_run_actions(t_stk_node *stacks[2]);
int	chk_run_action(t_stk_node *stacks[2]);
#endif
