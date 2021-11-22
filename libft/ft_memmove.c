/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <sashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 20:58:09 by sashly            #+#    #+#             */
/*   Updated: 2020/11/05 18:33:04 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const char	*s;
	char		*d;

	if (src < dest)
	{
		s = (const char *)src;
		d = (char *)dest;
		s += n - 1;
		d += n - 1;
		while (n--)
			*(d--) = *(s--);
	}
	else if (n && dest != src)
		ft_memcpy(dest, src, n);
	return (dest);
}
