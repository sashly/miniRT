/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_pvec3_6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:09:36 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 20:18:29 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lalgebra.h"

void	pvec3_cap(t_vec3 *vec, t_flt cap)
{
	if (vec->x > cap)
		vec->x = cap;
	if (vec->y > cap)
		vec->y = cap;
	if (vec->z > cap)
		vec->z = cap;
}

void	pvec3_pow(t_vec3 *col, t_flt pw)
{
	col->x = pow(col->x, pw);
	col->y = pow(col->y, pw);
	col->z = pow(col->z, pw);
}

t_vec4	gvec4(t_flt x, t_flt y, t_flt z, t_flt w)
{
	t_vec4 vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	vec.w = w;
	return (vec);
}
