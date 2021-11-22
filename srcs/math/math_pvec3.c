/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_pvec3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:07:33 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 20:14:54 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lalgebra.h"

void	pgvec3(t_flt x, t_flt y, t_flt z, t_vec3 *out)
{
	out->x = x;
	out->y = y;
	out->z = z;
}

void	pvec3_add(t_vec3 *v1, t_vec3 *v2, t_vec3 *out)
{
	out->x = v1->x + v2->x;
	out->y = v1->y + v2->y;
	out->z = v1->z + v2->z;
}

void	pvec3_addc(t_vec3 *vec, t_vec3 c)
{
	vec->x += c.x;
	vec->y += c.y;
	vec->z += c.z;
}

void	pvec3_add_const(t_vec3 *vec, t_flt c, t_vec3 *out)
{
	out->x = vec->x + c;
	out->y = vec->y + c;
	out->z = vec->z + c;
}

void	pvec3_addcomb(t_vec3 *v1, t_flt c, t_vec3 *v2, t_vec3 *out)
{
	out->x = v1->x + c * v2->x;
	out->y = v1->y + c * v2->y;
	out->z = v1->z + c * v2->z;
}
