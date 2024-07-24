/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrenau-v <jrenau-v@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 16:34:22 by jrenau-v          #+#    #+#             */
/*   Updated: 2022/09/22 12:35:13 by jrenau-v         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	hay_i;
	size_t	need_i;

	hay_i = 0;
	while (haystack[hay_i] != '\0')
	{
		need_i = 0;
		while (haystack[hay_i + need_i] == needle[need_i]
			&& needle[need_i] != '\0'
			&& (need_i + hay_i) < len)
		{
			need_i++;
		}
		if (needle[need_i] == '\0')
			return ((char *)(haystack + hay_i));
		hay_i++;
	}
	if (needle[0] == '\0')
		return ((char *)haystack);
	return (0);
}
