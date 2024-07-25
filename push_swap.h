/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenau-v <jrenau-v@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/30 13:04:52 by jrenau-v          #+#    #+#             */
/*   Updated: 2023/02/04 16:07:08 by jrenau-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdio.h>
# include "./libft/ft_printf/ft_printf.h"
# include "./libft/libft/libft.h"

typedef	enum	ChunckBound 
{
	LOW_BOUND_MIN,
	LOW_BOUND_MAX,
	HIGH_BOUND_MIN,
	HIGH_BOUND_MAX
}t_ChunckBound;


typedef struct s_stk_node
{
	int					value;
	unsigned int		index;
	struct s_stk_node	*previous;
	struct s_stk_node	*next;
}	t_stk_node;

/*push_swap*/
int			main(int argc, char **argv);
int			psw_prnt_error(void);
void		psw_long_sort(t_stk_node *stacks[]);

/*psw_stk_basics.c*/
t_stk_node	*stk_last(t_stk_node *stack);
t_stk_node	*stk_clear(t_stk_node **stack);
t_stk_node	*stk_init(char **numbers, size_t len);
void		stk_print(t_stk_node *stk);
int			psw_getindexes(t_stk_node **start);

/*psw_stk_operions*/
void		psw_debug_log(char *str, int freee);
void		stk_caller(t_stk_node *stacks[2], char *action);	
void		stk_push(t_stk_node **stk1, t_stk_node **stk2);
void		stk_swap(t_stk_node *stk);
void		stk_rotate(t_stk_node **stk, int reverse);

/*psw_inpsanitize*/
int			psw_check(char **numbers);
int			psw_check_range(char *inp_num);
int			psw_check_general(char *inp_num);

/*psw_algorithm*/
void		psw_boundaries(size_t boundaries[], int chunck, size_t ln);
void		psw_semisort(t_stk_node *stacks[]);
size_t		stk_len(t_stk_node *stack);
void		psw_long_sort(t_stk_node *stacks[]);

/*psw_algorithm2*/
void		psw_sorta(t_stk_node *stacks[2]);
void		psw_pushback(t_stk_node *stacks[2]);
size_t		stk_maxIndex(t_stk_node *stack);

/*psw_shorts*/
void		stk_strcaller(t_stk_node *stakcs[], char *str);
void		stk_size3(t_stk_node *stakcs[2]);
void		stk_size5(t_stk_node *stakcs[2]);

/*psw_utils.c*/
int			psw_prnt_error(void);
int			check_sorted(t_stk_node *stack);
#endif
