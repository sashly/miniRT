/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <sashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 21:30:03 by sashly            #+#    #+#             */
/*   Updated: 2020/11/05 18:36:45 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	len;

	len = (int)ft_strlen(s) + 1;
	s = s + len - 1;
	while (len--)
		if ((len == 0) ? (*s == c) : (*(s--) == c))
			break ;
	if (len == 0)
		return ((char *)s);
	if (len > 0)
		return ((char *)(++s));
	return (0);
}
