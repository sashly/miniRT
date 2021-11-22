/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_vec3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:10:10 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 20:13:13 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lalgebra.h"

t_vec3	gvec3(t_flt x, t_flt y, t_flt z)
{
	t_vec3 vector;

	vector.x = x;
	vector.y = y;
	vector.z = z;
	return (vector);
}

t_vec3	vec3_add(t_vec3 v1, t_vec3 v2)
{
	t_vec3 ret;

	ret.x = v1.x + v2.x;
	ret.y = v1.y + v2.y;
	ret.z = v1.z + v2.z;
	return (ret);
}

t_vec3	vec3_sub(t_vec3 v1, t_vec3 v2)
{
	t_vec3 ret;

	ret.x = v1.x - v2.x;
	ret.y = v1.y - v2.y;
	ret.z = v1.z - v2.z;
	return (ret);
}

t_vec3	vec3_mul(t_vec3 v1, t_vec3 v2)
{
	t_vec3 ret;

	ret.x = v1.x * v2.x;
	ret.y = v1.y * v2.y;
	ret.z = v1.z * v2.z;
	return (ret);
}

t_vec3	vec3_div(t_vec3 v1, t_vec3 v2)
{
	t_vec3 ret;

	ret.x = v1.x / v2.x;
	ret.y = v1.y / v2.y;
	ret.z = v1.z / v2.z;
	return (ret);
}
