/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_vec3_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:11:01 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 20:14:19 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lalgebra.h"

t_flt	vec3_dot(t_vec3 v1, t_vec3 v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vec3	vec3_cross(t_vec3 v1, t_vec3 v2)
{
	t_vec3 cross;

	cross.x = v1.y * v2.z - v1.z * v2.y;
	cross.y = v1.z * v2.x - v1.x * v2.z;
	cross.z = v1.x * v2.y - v1.y * v2.x;
	return (cross);
}

t_vec3	vec3_unit(t_vec3 vec)
{
	t_vec3	unit;
	t_flt	vlen_inv;

	vlen_inv = 1. / sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	unit.x = vec.x * vlen_inv;
	unit.y = vec.y * vlen_inv;
	unit.z = vec.z * vlen_inv;
	return (unit);
}

t_vec3	vec3_neg(t_vec3 vec)
{
	return (gvec3(-vec.x, -vec.y, -vec.z));
}
