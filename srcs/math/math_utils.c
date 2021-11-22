/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:11:21 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 20:10:53 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lalgebra.h"

void	pgvec2(t_flt min, t_flt max, t_vec2 *vec)
{
	vec->min = min;
	vec->max = max;
}

t_ivec3	givec3(int x, int y, int z)
{
	t_ivec3 vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

void	pgivec3(int x, int y, int z, t_ivec3 *ivec)
{
	ivec->x = x;
	ivec->y = y;
	ivec->z = z;
}

void	gnbasis_norm(t_vec3 *vec, t_vec3 c1, t_vec3 c2, t_nbasis *nb)
{
	nb->dummy = c1;
	if (vec3_coll(vec, &nb->dummy))
		nb->dummy = c2;
	nb->v = vec3_unit(*vec);
	pvec3_cross(&nb->dummy, &nb->v, &nb->w);
	pvec3_unit(&nb->w);
	pvec3_cross(&nb->v, &nb->w, &nb->u);
}

void	gnbasis_view(t_vec3 *vec, t_nbasis *nb)
{
	t_vec3 up;

	pgvec3(0., 1., 0., &up);
	if (pvec3_equal(&up, vec))
		pgvec3(0., 0., 1., &up);
	else if (vec3_equal(&up, vec3_neg(*vec)))
		pgvec3(0., 0., -1., &up);
	nb->w = vec3_unit(vec3_neg(*vec));
	pvec3_cross(&up, &nb->w, &nb->u);
	pvec3_unit(&nb->u);
	pvec3_cross(&nb->w, &nb->u, &nb->v);
}
