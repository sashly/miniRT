/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <sashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 21:20:07 by sashly            #+#    #+#             */
/*   Updated: 2020/11/06 13:07:49 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	const char *s;

	if (!dst || !src)
		return (0);
	s = src;
	if (size != 0)
	{
		while (*src && --size)
			*(dst++) = *(src++);
		*dst = '\0';
	}
	return (ft_strlen(s));
}
