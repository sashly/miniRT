/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <sashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 21:43:58 by sashly            #+#    #+#             */
/*   Updated: 2020/11/05 17:58:51 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digit(int n)
{
	int count;

	if (n == 0)
		return (1);
	count = 0;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static void	ft_strrev_itoa(char *str, int len)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	j = len - 1;
	while (i < len / 2)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		i++;
		j--;
	}
}

char		*ft_itoa(int n)
{
	char	*itoa;
	int		size;
	int		sign;

	sign = (n < 0) ? 1 : 0;
	size = count_digit(n) + ((n < 0) ? 2 : 1);
	if (!(itoa = (char *)malloc(sizeof(char) * size)))
		return (NULL);
	(n == 0) ? (*(itoa++) = '0') : (void)n;
	while (n != 0)
	{
		*(itoa++) = ((n < 0) ? (n % 10) * (-1) : n % 10) + '0';
		n /= 10;
	}
	(sign) ? (*(itoa++) = '-') : (void)sign;
	*itoa = '\0';
	ft_strrev_itoa((itoa - size + 1), size - 1);
	return (itoa - size + 1);
}
