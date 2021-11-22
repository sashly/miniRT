/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ellipsoid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 22:56:01 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 22:56:51 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		el_tmat_build(t_obj *el, t_flt a, t_flt b, t_flt g)
{
	t_mat4	tmp;
	t_mat4	mult;
	t_vec3	c;

	if (!el->m->inv && !(mat44_malloc3(&el->m->tmat, &el->m->inv,
					&el->m->tinv)))
		return (0);
	if (!(mat44_malloc2(&tmp, &mult)))
		return (0);
	m44tf_rotate_xyz(a, b, g, el->m->tmat);
	pgvec3(el->obj.el.cent.x, el->obj.el.cent.y, el->obj.el.cent.z, &c);
	m44tf_translation(&c, tmp);
	mat44_mult_tmat44(tmp, el->m->tmat, mult);
	m44tf_scaling(gvec3(el->obj.el.r1, el->obj.el.r2, el->obj.el.r3), tmp);
	mat44_mult_tmat44(mult, tmp, el->m->tmat);
	if (!(mat44_inverse(el->m->tmat, el->m->inv)))
		return (0);
	mat44_transpose(el->m->inv, el->m->tinv);
	free(tmp);
	free(mult);
	return (1);
}

int		is_hit_ellipsoid(t_ray *ray, t_obj *el, t_flt t_max, t_hit_rec *hr)
{
	t_ray	oray;
	t_vec3	oc;
	t_flt	cfs[4];
	t_flt	tmp;

	get_objray(el, ray, &oray);
	oc = oray.orig;
	cfs[0] = pvec3_dotr(&oray.dir, &oray.dir);
	cfs[1] = pvec3_dotr(&oc, &oray.dir);
	cfs[2] = pvec3_dotr(&oc, &oc) - 1.;
	cfs[3] = cfs[1] * cfs[1] - cfs[0] * cfs[2];
	if (cfs[3] < 0.)
		return (0);
	cfs[3] = sqrt(cfs[3]);
	tmp = (-cfs[1] - cfs[3]) / cfs[0];
	if (tmp < 0.)
		tmp = (-cfs[1] + cfs[3]) / cfs[0];
	if (!(tmp > RT_EPSILON && tmp < t_max))
		return (0);
	hr->t = tmp;
	return (1);
}

void	ellipsoid_norm(t_obj *el, t_hit_rec *hr, t_vec3 *norm)
{
	t_vec3	local_p;
	t_vec3	local_n;
	t_vec3	el_local_c;

	local_p = hr->p;
	mat44_mult_mat31_inplace(el->m->inv, &local_p, 1);
	pgvec3(0., 0., 0., &el_local_c);
	pvec3_unitsub(&local_p, &el_local_c, &local_n);
	mat44_mult_mat31_inplace(el->m->tinv, &local_n, 0);
	pvec3_unit(&local_n);
	*norm = local_n;
}
