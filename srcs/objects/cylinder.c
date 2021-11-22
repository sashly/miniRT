/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 22:51:05 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 22:51:58 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		is_hit_cylinder_la(t_ray *ray, t_obj *cy, t_flt t_max, t_hit_rec *hr)
{
	t_vec3	vcs[2];
	t_flt	ds[3];
	t_flt	cfs[5];
	t_flt	tmp;

	pvec3_sub(&cy->obj.cy.b, &cy->obj.cy.a, &vcs[0]);
	pvec3_sub(&ray->orig, &cy->obj.cy.a, &vcs[1]);
	ds[0] = pvec3_dotr(&vcs[0], &vcs[0]);
	ds[1] = pvec3_dotr(&vcs[0], &ray->dir);
	ds[2] = pvec3_dotr(&vcs[0], &vcs[1]);
	cfs[0] = ds[0] - ds[1] * ds[1];
	cfs[1] = ds[0] * pvec3_dotr(&vcs[1], &ray->dir) - ds[1] * ds[2];
	cfs[2] = ds[0] * pvec3_dotr(&vcs[1], &vcs[1]) - ds[2] * ds[2] -
		ds[0] * cy->obj.cy.rp2;
	cfs[3] = cfs[1] * cfs[1] - cfs[0] * cfs[2];
	if (cfs[3] < 0.)
		return (0);
	tmp = (-cfs[1] - sqrt(cfs[3])) / cfs[0];
	cfs[4] = ds[2] + tmp * ds[1];
	if (tmp <= 0. || !(cfs[4] > 0. && cfs[4] < ds[0]))
		tmp = (-cfs[1] + sqrt(cfs[3])) / cfs[0];
	cfs[4] = ds[2] + tmp * ds[1];
	if (!(cfs[4] > 0. && cfs[4] < ds[0]))
		return (0);
	return (hit_return_helper(hr, RT_EPSILON, t_max, tmp));
}

void	cylinder_norm_la(t_obj *cy, t_hit_rec *hr, t_vec3 *norm)
{
	t_vec3	pvec;
	t_vec3	pt;
	t_flt	pvec_apr;

	pvec3_sub(&hr->p, &cy->obj.cy.a, &pvec);
	pvec_apr = pvec3_dotr(&pvec, &cy->obj.cy.na);
	pvec3_addcomb(&cy->obj.cy.a, pvec_apr, &cy->obj.cy.na, &pt);
	pvec3_unitsub(&hr->p, &pt, norm);
}
