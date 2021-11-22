/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <sashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 21:39:02 by sashly            #+#    #+#             */
/*   Updated: 2020/11/06 13:09:32 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	size;

	if (!s)
		return (NULL);
	if (start >= ft_strlen(s))
		len = 0;
	len += 1;
	size = ft_strlen(s + start) + 1;
	if (!(sub = (char *)malloc(sizeof(char) * \
					((len < size) ? len : size))))
		return (NULL);
	ft_strlcpy(sub, s + start, ((len < size) ? len : size));
	return (sub);
}
