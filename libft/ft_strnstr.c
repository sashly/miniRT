/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <sashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 21:26:53 by sashly            #+#    #+#             */
/*   Updated: 2020/11/05 18:36:36 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int			i;
	int			si;
	const char	*n;

	if (!(*needle))
		return ((char *)haystack);
	n = needle;
	i = 0;
	while (haystack[i] && len)
	{
		si = i;
		if (haystack[i] == *needle)
		{
			while (haystack[i] == *(needle++) && haystack[i] && len--)
				i++;
			if (!*(--needle))
				return (char *)(haystack + si);
			needle = n;
			len += i - si;
			(haystack[i]) ? (i = si) : i--;
		}
		i++;
		len--;
	}
	return (0);
}
