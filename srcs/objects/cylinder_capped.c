/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_capped.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 22:52:10 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 22:53:54 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		is_hit_caps(t_ray *ray, t_obj *cp, t_flt t_max, t_hit_rec *hit_rec)
{
	t_flt	tmin;
	t_flt	tmax;
	int		hit_f;

	if (!cp->obj.cy.cap || fabs(ray->dir.y) < RT_EPSILON)
		return (0);
	hit_f = 0;
	tmin = (-ray->orig.y) / ray->dir.y;
	if (check_cap(ray, tmin) && tmin > RT_EPSILON && tmin < t_max)
		hit_f++;
	else
		tmin = RT_HUGEVAL;
	tmax = (cp->obj.cy.h / cp->obj.cy.r - ray->orig.y) / ray->dir.y;
	if (check_cap(ray, tmax) && tmax > RT_EPSILON && tmax < t_max)
		hit_f++;
	else
		tmax = RT_HUGEVAL;
	if (hit_f)
		hit_rec->t = (tmin < tmax) ? tmin : tmax;
	return (hit_f);
}

int		cp_handle_caps(t_ray *oray, t_obj *cp, t_flt *t_max, t_hit_rec *hr)
{
	t_flt a;

	a = oray->dir.x * oray->dir.x + oray->dir.z * oray->dir.z;
	if (FLT_ISZERO(a) && is_hit_caps(oray, cp, *t_max, hr))
	{
		ray_point(oray, hr->t, &hr->p);
		if (hr->p.y >= (cp->obj.cy.h / cp->obj.cy.r - RT_EPSILON))
			pgvec3(0., 1., 0., &hr->n);
		else if (hr->p.y < RT_EPSILON)
			pgvec3(0., -1., 0., &hr->n);
		norm_to_world(cp, &hr->n);
		return (2);
	}
	if (is_hit_caps(oray, cp, *t_max, hr))
	{
		ray_point(oray, hr->t, &hr->p);
		if (hr->p.y >= (cp->obj.cy.h / cp->obj.cy.r - RT_EPSILON))
			pgvec3(0., 1., 0., &hr->n);
		else if (hr->p.y < RT_EPSILON)
			pgvec3(0., -1., 0., &hr->n);
		norm_to_world(cp, &hr->n);
		*t_max = hr->t;
		return (1);
	}
	return (0);
}

void	cp_get_cfs(t_ray *or, t_flt *cfs)
{
	cfs[0] = or->dir.x * or->dir.x + or->dir.z * or->dir.z;
	cfs[1] = 2. * or->orig.x * or->dir.x + 2. * or->orig.z * or->dir.z;
	cfs[2] = or->orig.x * or->orig.x + or->orig.z * or->orig.z - 1.;
	cfs[3] = cfs[1] * cfs[1] - 4. * cfs[0] * cfs[2];
}

int		cp_handle_body(t_ray *oray, t_obj *cp, t_flt *t, t_hit_rec *hr)
{
	t_flt y;

	y = oray->orig.y + t[0] * oray->dir.y;
	if ((t[0] > RT_EPSILON && t[0] < t[2]) &&
		(y > 0. && y < cp->obj.cy.h / cp->obj.cy.r))
	{
		hr->t = t[0];
		ray_point(oray, t[0], &hr->p);
		pgvec3(hr->p.x, 0., hr->p.z, &hr->n);
		norm_to_world(cp, &hr->n);
		return (1);
	}
	y = oray->orig.y + t[1] * oray->dir.y;
	if ((t[1] > RT_EPSILON && t[1] < t[2]) &&
		(y > 0. && y < cp->obj.cy.h / cp->obj.cy.r))
	{
		hr->t = t[1];
		ray_point(oray, t[1], &hr->p);
		pgvec3(-hr->p.x, 0., -hr->p.z, &hr->n);
		norm_to_world(cp, &hr->n);
		return (1);
	}
	return (0);
}

int		is_hit_cylinder_cp_t(t_ray *ray, t_obj *cp, t_flt t_max, t_hit_rec *hr)
{
	t_ray	oray;
	t_flt	cfs[4];
	t_flt	tmp[3];
	int		hit_cap;

	get_objray(cp, ray, &oray);
	hit_cap = cp_handle_caps(&oray, cp, &t_max, hr);
	if (hit_cap == 2)
		return (1);
	cp_get_cfs(&oray, cfs);
	if (cfs[3] < 0.)
		return (hit_cap);
	tmp[0] = (-cfs[1] - sqrt(cfs[3])) / (2. * cfs[0]);
	tmp[1] = (-cfs[1] + sqrt(cfs[3])) / (2. * cfs[0]);
	tmp[2] = t_max;
	if (cp_handle_body(&oray, cp, tmp, hr))
		return (1);
	return (hit_cap);
}
