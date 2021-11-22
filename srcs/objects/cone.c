/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 22:49:13 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 22:50:48 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	cone_get_cfs(t_ray *r, t_flt *cfs)
{
	cfs[0] = r->dir.x * r->dir.x - r->dir.y * r->dir.y + r->dir.z * r->dir.z;
	cfs[1] = 2. * r->orig.x * r->dir.x - 2. * r->orig.y * r->dir.y +
		2. * r->orig.z * r->dir.z;
	cfs[2] = r->orig.x * r->orig.x - r->orig.y * r->orig.y +
		r->orig.z * r->orig.z;
	cfs[3] = cfs[1] * cfs[1] - 4. * cfs[0] * cfs[2];
}

int		cn_hit_return(t_hit_rec *hr, t_flt tmp)
{
	hr->t = tmp;
	return (1);
}

int		is_hit_cone(t_ray *ray, t_obj *cn, t_flt t_max, t_hit_rec *hr)
{
	t_ray	r;
	t_flt	cfs[4];
	t_flt	tmp;
	t_flt	cy;

	get_objray(cn, ray, &r);
	cone_get_cfs(&r, cfs);
	if (FLT_ISZERO(cfs[0]) && FLT_ISZERO(cfs[1]))
		return (0);
	if (cfs[3] < 0.)
		return (0);
	tmp = (-cfs[1] - sqrt(cfs[3])) / (2. * cfs[0]);
	cy = r.orig.y + tmp * r.dir.y;
	if ((tmp > 0.0001 && tmp < t_max) && (cy < 0. && cy > -cn->obj.cn.h))
		return (cn_hit_return(hr, tmp));
	tmp = (-cfs[1] + sqrt(cfs[3])) / (2. * cfs[0]);
	cy = r.orig.y + tmp * r.dir.y;
	if ((tmp > 0.0001 && tmp < t_max) && (cy < 0. && cy > -cn->obj.cn.h))
		return (cn_hit_return(hr, tmp));
	return (0);
}

void	cone_norm(t_obj *cn, t_hit_rec *hr, t_vec3 *norm)
{
	t_vec3 generatrix;
	t_vec3 tan;

	pvec3_sub(&cn->obj.cn.ph, &hr->p, &generatrix);
	pvec3_unit(&generatrix);
	pvec3_cross(&cn->obj.cn.n, &generatrix, &tan);
	pvec3_cross(&generatrix, &tan, norm);
	pvec3_unit(norm);
}

int		cn_tmat_build(t_obj *cn)
{
	t_nbasis	nb;
	t_mat4		tmp;
	t_mat4		mult;
	t_vec3		p;

	if (!cn->m->inv && !(mat44_malloc3(&cn->m->tmat, &cn->m->inv,
					&cn->m->tinv)))
		return (0);
	if (!(mat44_malloc2(&tmp, &mult)))
		return (0);
	pgvec3(0., 0., 0., &p);
	gnbasis_norm(&cn->obj.cn.n, gvec3(0., 1., 0.), gvec3(0., 0., 1.), &nb);
	m44tf_transition_inv(&nb, &p, cn->m->tmat);
	m44tf_translation(&cn->obj.cn.c, tmp);
	mat44_mult_tmat44(tmp, cn->m->tmat, mult);
	m44tf_scaling(gvec3(cn->obj.cn.r / cn->obj.cn.h, 1,
						cn->obj.cn.r / cn->obj.cn.h), tmp);
	mat44_mult_tmat44(mult, tmp, cn->m->tmat);
	if (!(mat44_inverse(cn->m->tmat, cn->m->inv)))
		return (0);
	mat44_transpose(cn->m->inv, cn->m->tinv);
	free(tmp);
	free(mult);
	return (1);
}
