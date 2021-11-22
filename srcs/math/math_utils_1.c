/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 20:30:07 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 20:31:00 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lalgebra.h"

t_flt	ft_fabs(t_flt a)
{
	return ((a < 0) ? -a : a);
}

void	ft_swapf(t_flt *a, t_flt *b)
{
	t_flt tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int		flt_equal(t_flt a, t_flt b)
{
	if (fabs(a - b) < RT_EQNEPS)
		return (1);
	return (0);
}

int		flt_iszero(t_flt myflt)
{
	return (myflt > -RT_EQNEPS && myflt < RT_EQNEPS);
}

int		solve_quadric(t_flt *c, t_flt *roots)
{
	t_flt	a_inv;
	t_flt	p;
	t_flt	q;
	t_flt	disc;
	t_flt	sqdisc;

	a_inv = 1 / c[0];
	p = c[1] * a_inv * 0.5;
	q = c[2] * a_inv;
	disc = p * p - q;
	if (FLT_ISZERO(disc))
	{
		roots[0] = -p;
		return (1);
	}
	else if (disc > 0.)
	{
		sqdisc = sqrt(disc);
		roots[0] = sqdisc - p;
		roots[1] = -sqdisc - p;
		if (roots[0] > roots[1])
			SWAP_FLT(roots[0], roots[1]);
		return (2);
	}
	return (0);
}
