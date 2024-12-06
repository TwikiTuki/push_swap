
#include "push_swap.h"

static int	n_chuncks(size_t len)
{
	if (len <= 100)
		return (3);
	if (len <= 500)
		return (7);
	else
		return (15);
}

void	psw_boundaries(size_t bounds[], int chunck, size_t ln)
{
	unsigned int	size;
	unsigned int	size_up;
	unsigned int	size_down;

	size = ln / n_chuncks(ln) + ((size_t) chunck < (ln % n_chuncks(ln))); 
	size_up = size / 2;
	size_down = size / 2 + size % 2;
	bounds[LOW_BOUND_MIN] = bounds[HIGH_BOUND_MAX] + 1;	
	bounds[LOW_BOUND_MAX] = bounds[LOW_BOUND_MIN] + size_down - 1;
	bounds[HIGH_BOUND_MIN] = bounds[LOW_BOUND_MAX] + 1;
	bounds[HIGH_BOUND_MAX] = bounds[HIGH_BOUND_MIN] + size_up - 1;
}	

size_t	stk_len(t_stk_node *stack)
{
	size_t	len;

	len = 0;
	while (stack)
	{
		len++;
		stack = stack -> next;
	}
	return (len);
}

void	psw_semisort(t_stk_node *stacks[])
{
	size_t			bounds[4];
	size_t			len;
	size_t			orig_len;
	int				chunck;	

	chunck = 0;
	bounds[HIGH_BOUND_MAX] = 0 - 1;
	orig_len = stk_len(stacks[0]);
	while (chunck++ < n_chuncks(orig_len))
	{
		len = stk_len(stacks[0]);
		psw_boundaries(bounds, chunck - 1, orig_len);
		while (len--)
		{
			if ((stacks[0]->index >= bounds[LOW_BOUND_MIN])
				&& (stacks[0]->index <= bounds[HIGH_BOUND_MAX]))
			{
				stk_caller_verbose(stacks, "pb");
				if (stacks[1]->index > bounds[LOW_BOUND_MAX])
					stk_caller_verbose(stacks, "rb");
			}
			else
				stk_caller_verbose(stacks, "ra");
		}
	}
}

void	psw_long_sort(t_stk_node *stacks[])
{
	psw_semisort(stacks);
	while (stacks[1])
	{
		psw_pushback(stacks);
		psw_sorta(stacks);
	}
}
