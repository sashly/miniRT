/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <sashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 21:18:31 by sashly            #+#    #+#             */
/*   Updated: 2020/11/06 13:07:46 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		len;
	int			size;

	if (dstsize >= ft_strlen(dst))
		len = ft_strlen(src) + ft_strlen(dst);
	else
		len = dstsize + ft_strlen(src);
	size = (int)dstsize - (int)ft_strlen(dst) - 1;
	if (size > 0)
	{
		while (*dst)
			dst++;
		while (*src && size--)
			*(dst++) = *(src++);
		*dst = '\0';
	}
	return (len);
}
