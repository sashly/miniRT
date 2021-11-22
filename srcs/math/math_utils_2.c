/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 20:31:20 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 20:32:14 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lalgebra.h"

int	solve_quadric_sp(t_flt *c, t_flt *roots)
{
	t_flt	disc;
	t_flt	q;
	t_flt	inv_a;

	inv_a = 1 / c[0];
	disc = c[1] * c[1] - 4 * c[0] * c[2];
	if (FLT_ISZERO(disc))
	{
		roots[0] = -0.5 * c[1] * inv_a;
		return (1);
	}
	else if (disc > 0.)
	{
		q = (c[1] > 0.) ? (-0.5 * (c[1] + sqrt(disc))) : (-0.5 *
				(c[1] - sqrt(disc)));
		roots[0] = q * inv_a;
		roots[1] = c[2] / q;
		if (roots[0] > roots[1])
			SWAP_FLT(roots[0], roots[1]);
		return (2);
	}
	return (0);
}
