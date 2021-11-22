/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <sashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 21:34:07 by sashly            #+#    #+#             */
/*   Updated: 2020/11/06 13:09:10 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_is_instr(char const *set, char const s1)
{
	while (*set)
		if (*(set++) == s1)
			return (1);
	return (0);
}

static char const	*ft_strlen_mod(char const *s1, char const *set, \
		int *len)
{
	char const *start;
	char const *end;

	start = s1;
	end = s1 + ft_strlen(s1) - 1;
	while (*start && ft_is_instr(set, *start))
		start++;
	while (end > start && ft_is_instr(set, *end))
		end--;
	*len = end - start + 1;
	return (start);
}

char				*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	int		size;

	if (!s1 || !set)
		return (NULL);
	size = 0;
	s1 = ft_strlen_mod(s1, set, &size);
	if (!(trim = (char *)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ft_strlcpy(trim, s1, size + 1);
	return (trim);
}
