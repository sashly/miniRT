/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_pvec3_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:08:49 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 20:15:31 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lalgebra.h"

void	pvec3_unitneg(t_vec3 *vec)
{
	t_flt vlen_inv;

	vlen_inv = 1. / sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
	vec->x *= -vlen_inv;
	vec->y *= -vlen_inv;
	vec->z *= -vlen_inv;
}

void	pvec3_neg(t_vec3 *vec)
{
	vec->x *= -1.;
	vec->y *= -1.;
	vec->z *= -1.;
}

t_vec3	pvec3_negr(t_vec3 *vec)
{
	t_vec3	neg;

	neg.x = -vec->x;
	neg.y = -vec->y;
	neg.z = -vec->z;
	return (neg);
}

t_flt	pvec3_len(t_vec3 *v)
{
	return (sqrt(v->x * v->x + v->y * v->y + v->z * v->z));
}

void	pvec3_dot(t_vec3 *v1, t_vec3 *v2, t_flt *out)
{
	*out = v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}
