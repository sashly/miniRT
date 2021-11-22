/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_pvec3_4.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:09:05 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 20:15:47 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lalgebra.h"

t_flt	pvec3_dotr(t_vec3 *v1, t_vec3 *v2)
{
	t_flt out;

	out = v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
	return (out);
}

t_flt	pvec3_dotsub(t_vec3 *v1, t_vec3 *v2, t_vec3 *v3)
{
	t_vec3 vec;

	vec.x = v1->x - v2->x;
	vec.y = v1->y - v2->y;
	vec.z = v1->z - v2->z;
	return (vec.x * v3->x + vec.y * v3->y + vec.z * v3->z);
}

void	pvec3_cross(t_vec3 *v1, t_vec3 *v2, t_vec3 *out)
{
	out->x = v1->y * v2->z - v1->z * v2->y;
	out->y = v1->z * v2->x - v1->x * v2->z;
	out->z = v1->x * v2->y - v1->y * v2->x;
}

int		pvec3_equal(t_vec3 *v1, t_vec3 *v2)
{
	if (fabs(v1->x - v2->x) < RT_EQNEPS && fabs(v1->y - v2->y) < RT_EQNEPS &&
		fabs(v1->z - v2->z) < RT_EQNEPS)
		return (1);
	return (0);
}

int		vec3_equal(t_vec3 *v1, t_vec3 v2)
{
	if (fabs(v1->x - v2.x) < RT_EQNEPS && fabs(v1->y - v2.y) < RT_EQNEPS &&
		fabs(v1->z - v2.z) < RT_EQNEPS)
		return (1);
	return (0);
}
