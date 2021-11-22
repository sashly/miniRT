/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_capped_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 22:54:11 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 22:55:05 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		cy_tmat_build(t_obj *cy)
{
	t_nbasis	nb;
	t_mat4		tmp;
	t_mat4		mult;
	t_vec3		point;

	if (!cy->m->inv && !(mat44_malloc3(&cy->m->tmat, &cy->m->inv,
					&cy->m->tinv)))
		return (0);
	if (!(mat44_malloc2(&tmp, &mult)))
		return (0);
	pgvec3(0., 0., 0., &point);
	gnbasis_norm(&cy->obj.cy.na, gvec3(1., 0., 0.), gvec3(0., 1., 0.), &nb);
	m44tf_scaling(gvec3(cy->obj.cy.r, cy->obj.cy.r, cy->obj.cy.r), cy->m->tmat);
	m44tf_transition_inv(&nb, &point, tmp);
	mat44_mult_tmat44(tmp, cy->m->tmat, mult);
	m44tf_translation(&cy->obj.cy.a, tmp);
	mat44_mult_tmat44(tmp, mult, cy->m->tmat);
	if (!(mat44_inverse(cy->m->tmat, cy->m->inv)))
		return (0);
	mat44_transpose(cy->m->inv, cy->m->tinv);
	free(tmp);
	free(mult);
	return (1);
}

void	cylinder_norm_cp_t(t_obj *cp, t_hit_rec *hr, t_vec3 *norm)
{
	(void)cp;
	(void)hr;
	(void)norm;
}

int		check_cap(t_ray *ray, t_flt t)
{
	t_flt	x;
	t_flt	z;

	x = ray->orig.x + (t * ray->dir.x);
	z = ray->orig.z + (t * ray->dir.z);
	return ((x * x + z * z) <= 1.);
}
