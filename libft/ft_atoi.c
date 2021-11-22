/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <sashly@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 14:19:53 by sashly            #+#    #+#             */
/*   Updated: 2020/11/06 13:02:13 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace_atoi(int c)
{
	return (c == ' ' || c == '\n' || c == '\t' || \
			c == '\v' || c == '\r' || c == '\f');
}

int			ft_atoi(const char *nptr)
{
	int	res;
	int	sign;

	res = 0;
	sign = 1;
	while (ft_isspace_atoi(*nptr))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
		if (*(nptr++) == '-')
			sign = -1;
	while (*nptr >= '0' && *nptr <= '9')
		res = res * 10 + (*(nptr++) - '0');
	return (sign * res);
}

static int	atoi_check_overflow(const char *nptr, int res)
{
	if (res == 214748364 && (*nptr >= '0' && *nptr <= '7'))
		res = (IS_DIGIT(*(++nptr))) ? -5 : (res * 10 + (*(--nptr) - '0'));
	else
		res = (IS_DIGIT(*(nptr))) ? -5 : res;
	return ((*nptr) ? -1 : res);
}

int			ft_atoi_safe(const char *nptr)
{
	int res;

	res = 0;
	while (*nptr >= '0' && *nptr <= '9')
		if ((res = res * 10 + (*(nptr++) - '0')) > 214748363)
			return (atoi_check_overflow(nptr, res));
	return ((*nptr) ? -1 : res);
}
