/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_pvec3_5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:09:20 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 20:18:08 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lalgebra.h"

int		vec3_orth(t_vec3 *v1, t_vec3 *v2)
{
	if (fabs(v1->x * v2->x + v1->y * v2->y + v1->z * v2->z) < RT_EPSILON)
		return (1);
	return (0);
}

int		vec3_coll(t_vec3 *v1, t_vec3 *v2)
{
	t_vec3 cross;

	pvec3_cross(v1, v2, &cross);
	if ((cross.x * cross.x + cross.y * cross.y +
				cross.z * cross.z) < RT_EPSILON)
		return (1);
	return (0);
}

t_flt	vec3_absmax(t_vec3 *vec)
{
	t_flt max;

	max = (fabs(vec->x) >= fabs(vec->y) + RT_EQNEPS) ? vec->x : vec->y;
	max = (fabs(max) >= fabs(vec->z) + RT_EQNEPS) ? max : vec->z;
	return (max);
}

t_flt	pvec3_max(t_vec3 *vec)
{
	t_flt max;

	max = (vec->x > vec->y) ? vec->x : vec->y;
	max = (vec->z > max) ? vec->z : max;
	return (max);
}

int		pvec3_iszero(t_vec3 *vec)
{
	return (FLT_ISZERO(vec->x) && FLT_ISZERO(vec->y) && FLT_ISZERO(vec->z));
}
