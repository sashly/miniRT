/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/04 16:20:55 by sashly            #+#    #+#             */
/*   Updated: 2020/11/06 13:08:29 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, int len)
{
	char *dup;
	char *d;

	if (!(dup = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	d = dup;
	while (*s && len--)
		*(dup++) = *(s++);
	*dup = '\0';
	return (d);
}
