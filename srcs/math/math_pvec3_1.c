/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_pvec3_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:08:10 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 20:15:08 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lalgebra.h"

t_vec3	pvec3_addcombr(t_vec3 *v1, t_flt c1, t_vec3 *v2, t_flt c2)
{
	t_vec3 out;

	out.x = c1 * v1->x + c2 * v2->x;
	out.y = c1 * v1->y + c2 * v2->y;
	out.z = c1 * v1->z + c2 * v2->z;
	return (out);
}

void	pvec3_add3(t_vec3 *v1, t_vec3 *v2, t_vec3 *v3, t_vec3 *out)
{
	out->x = v1->x + v2->x + v3->x;
	out->y = v1->y + v2->y + v3->y;
	out->z = v1->z + v2->z + v3->z;
}

void	pvec3_sub(t_vec3 *v1, t_vec3 *v2, t_vec3 *out)
{
	out->x = v1->x - v2->x;
	out->y = v1->y - v2->y;
	out->z = v1->z - v2->z;
}

void	pvec3_muln(t_vec3 *v, t_flt nbr)
{
	v->x *= nbr;
	v->y *= nbr;
	v->z *= nbr;
}

void	pvec3_mulnr(t_vec3 *v, t_flt nbr, t_vec3 *out)
{
	out->x = v->x * nbr;
	out->y = v->y * nbr;
	out->z = v->z * nbr;
}
