/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 22:47:54 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 22:48:58 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	aabb_norm(t_obj *ab, t_hit_rec *hr, t_vec3 *norm)
{
	(void)ab;
	(void)hr;
	(void)norm;
}

int		ab_tmat_build(t_obj *ab, t_flt a, t_flt b, t_flt g)
{
	t_mat4	tmp;
	t_mat4	mult;
	t_vec3	c;

	if (!ab->m->inv && !(mat44_malloc3(&ab->m->tmat, &ab->m->inv,
					&ab->m->tinv)))
		return (0);
	if (!(mat44_malloc2(&tmp, &mult)))
		return (0);
	m44tf_rotate_xyz(a, b, g, ab->m->tmat);
	pgvec3(ab->obj.ab.p.x + (ab->obj.ab.lx / 2), ab->obj.ab.p.y +
			(ab->obj.ab.ly / 2), ab->obj.ab.p.z + (ab->obj.ab.lz / 2), &c);
	m44tf_translation(&c, tmp);
	mat44_mult_tmat44(tmp, ab->m->tmat, mult);
	m44tf_scaling(gvec3(ab->obj.ab.lx / 2, ab->obj.ab.ly / 2,
						ab->obj.ab.lz / 2), tmp);
	mat44_mult_tmat44(mult, tmp, ab->m->tmat);
	if (!(mat44_inverse(ab->m->tmat, ab->m->inv)))
		return (0);
	mat44_transpose(ab->m->inv, ab->m->tinv);
	free(tmp);
	free(mult);
	return (1);
}
