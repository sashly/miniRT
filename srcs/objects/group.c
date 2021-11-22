/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   group.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 22:57:08 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 22:58:04 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		is_hit_group(t_ray *ray, t_obj *gr, t_flt t_max, t_hit_rec *hr)
{
	t_ray	oray;
	int		hit_flag;
	int		i;

	i = 0;
	hit_flag = 0;
	get_objray(gr, ray, &oray);
	while (i < gr->obj.gr.gsize)
	{
		if (gr->obj.gr.gr[i].hit_f(&oray, &gr->obj.gr.gr[i], t_max, hr))
		{
			hit_flag = 1;
			gr->obj.gr.gr[i].norm_f(&gr->obj.gr.gr[i], hr, &hr->n);
			t_max = hr->t;
		}
		i++;
	}
	return (hit_flag);
}

void	group_norm(t_obj *gr, t_hit_rec *hr, t_vec3 *norm)
{
	*norm = hr->n;
	norm_to_world(gr, norm);
}

int		group_tmat_build(t_obj *gr)
{
	if (!gr->m->inv && !(mat44_malloc3(&gr->m->tmat, &gr->m->inv,
					&gr->m->tinv)))
		return (0);
	mat44_ident_fill(gr->m->tmat);
	mat44_ident_fill(gr->m->inv);
	mat44_ident_fill(gr->m->tinv);
	return (1);
}

int		cb_tmat_build(t_obj *cb, t_vec3 *p0, t_vec3 *norm)
{
	t_nbasis	nb;
	t_mat4		tmp;
	t_mat4		mult;
	t_vec3		p;

	if (!cb->m->inv && !(mat44_malloc3(&cb->m->tmat, &cb->m->inv,
					&cb->m->tinv)))
		return (0);
	if (!(mat44_malloc2(&tmp, &mult)))
		return (0);
	pgvec3(0., 0., 0., &p);
	gnbasis_norm(norm, gvec3(0., 1., 0.), gvec3(0., 0., 1.), &nb);
	m44tf_transition_inv(&nb, &p, mult);
	m44tf_translation(p0, tmp);
	mat44_mult_tmat44(tmp, mult, cb->m->tmat);
	if (!(mat44_inverse(cb->m->tmat, cb->m->inv)))
		return (0);
	mat44_transpose(cb->m->inv, cb->m->tinv);
	free(tmp);
	free(mult);
	return (1);
}
