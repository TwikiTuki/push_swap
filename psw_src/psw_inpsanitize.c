/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   psw_inpsanitize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenau-v <jrenau-v@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 16:30:01 by jrenau-v          #+#    #+#             */
/*   Updated: 2023/02/08 21:04:47 by jrenau-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

#define MAX_INT_STR "2147483647"
#define MIN_INT_STR "-2147483648"

int	psw_check(char **numbers)
{
	size_t	i;

	i = 0;
	while (numbers[i])
	{
		if (!psw_check_general(numbers[i]))
			return (0);
		if (!psw_check_range(numbers[i]))
			return (0);
		i++;
	}
	return (1);
}

static int	psw_find_start(char *inp_num)
{
	int	start;

	start = 0;
	if (inp_num[start] == '-')
		start++;
	while (inp_num[start] && inp_num[start] == '0')
		start++;
	if (start && inp_num[start - 1] != '-' && !inp_num[start])
		start--;
	return (start);
}

int	psw_check_range(char *inp)
{
	int		i;
	int		len;
	int		start;
	char	c;
	int		neg;

	neg = inp[0] == '-';
	start = psw_find_start(inp);
	len = ft_strlen(inp) - start;
	if (!len)
		return (0);
	if (len != 10)
		return (len < 10);
	i = 0;
	while (inp[i + start])
	{
		c = ((char *[]){"2147483647", "-2147483648"})[neg][i + neg];
		if (inp[i + start] > c)
			return (0);
		if (inp[i + start] < c)
			return (1);
		i++;
	}
	return (1);
}

int	psw_check_general(char *inp_num)
{
	int	i;

	i = 0;
	if (inp_num[i] == '-' || inp_num[i] == '+')
		i++;
	if (!inp_num[i] || inp_num[i] == '-' || inp_num[i] == '+')
		return (0);
	while (inp_num[i])
	{
		if (inp_num[i] < '0' || inp_num[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
