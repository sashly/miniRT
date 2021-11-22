/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <sashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 21:16:56 by sashly            #+#    #+#             */
/*   Updated: 2020/11/06 13:07:42 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*join;
	size_t	len1;
	size_t	len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(join = (char *)malloc(sizeof(char) * (len1 + len2 + 1))))
		return (NULL);
	ft_strlcpy(join, s1, len1 + 1);
	join += len1;
	ft_strlcpy(join, s2, len2 + 1);
	return (join - len1);
}
