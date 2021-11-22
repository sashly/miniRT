/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_pvec3_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:08:33 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 20:15:17 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lalgebra.h"

void	pvec3_divn(t_vec3 *v, t_flt nbr)
{
	t_flt n_inv;

	n_inv = 1. / nbr;
	v->x *= n_inv;
	v->y *= n_inv;
	v->z *= n_inv;
}

void	pvec3_mulc(t_vec3 *vec, t_vec3 c)
{
	vec->x *= c.x;
	vec->y *= c.y;
	vec->z *= c.z;
}

void	pvec3_mul(t_vec3 *vec, t_vec3 *c)
{
	vec->x *= c->x;
	vec->y *= c->y;
	vec->z *= c->z;
}

void	pvec3_unit(t_vec3 *vec)
{
	t_flt vlen_inv;

	vlen_inv = 1. / sqrt(vec->x * vec->x + vec->y * vec->y + vec->z * vec->z);
	vec->x *= vlen_inv;
	vec->y *= vlen_inv;
	vec->z *= vlen_inv;
}

void	pvec3_unitsub(t_vec3 *v1, t_vec3 *v2, t_vec3 *out)
{
	t_flt vlen_inv;

	out->x = v1->x - v2->x;
	out->y = v1->y - v2->y;
	out->z = v1->z - v2->z;
	vlen_inv = 1. / sqrt(out->x * out->x + out->y * out->y + out->z * out->z);
	out->x *= vlen_inv;
	out->y *= vlen_inv;
	out->z *= vlen_inv;
}
