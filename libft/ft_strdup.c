/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <sashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 21:15:11 by sashly            #+#    #+#             */
/*   Updated: 2020/11/06 13:07:39 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char *dup;
	char *d;

	if (!(dup = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1))))
		return (NULL);
	d = dup;
	while (*s)
		*(dup++) = *(s++);
	*dup = '\0';
	return (d);
}
