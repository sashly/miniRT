/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <sashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 14:23:34 by sashly            #+#    #+#             */
/*   Updated: 2020/11/05 17:57:56 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void *ptr;

	ptr = NULL;
	size *= nmemb;
	if ((ptr = (void *)malloc(size)))
		ft_memset(ptr, 0, size);
	return (ptr);
}
