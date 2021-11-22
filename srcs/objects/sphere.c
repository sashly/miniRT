/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 23:00:34 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 23:01:03 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		is_hit_sphere(t_ray *ray, t_obj *sp, t_flt t_max, t_hit_rec *hr)
{
	t_vec3	oc;
	t_flt	c[3];
	t_flt	roots[2];
	t_flt	tmp;
	int		sq;

	pvec3_sub(&ray->orig, &sp->obj.sp.cent, &oc);
	pvec3_dot(&ray->dir, &ray->dir, &c[0]);
	c[1] = 2.0 * pvec3_dotr(&oc, &ray->dir);
	c[2] = pvec3_dotr(&oc, &oc) - sp->obj.sp.r * sp->obj.sp.r;
	sq = solve_quadric(c, roots);
	if (sq)
	{
		tmp = roots[0];
		if (roots[0] < 0. && sq == 2)
			tmp = roots[1];
		if (!(tmp >= RT_EPSILON && tmp <= t_max - RT_EPSILON))
			return (0);
		hr->t = tmp;
		return (1);
	}
	return (0);
}

int		is_hit_sphere_alg(t_ray *ray, t_obj *sp, t_flt t_max, t_hit_rec *hr)
{
	t_vec3	oc;
	t_flt	b;
	t_flt	c;
	t_flt	h;
	t_flt	tmp;

	pvec3_sub(&ray->orig, &sp->obj.sp.cent, &oc);
	b = pvec3_dotr(&oc, &ray->dir);
	c = pvec3_dotr(&oc, &oc) - sp->obj.sp.rp2;
	h = b * b - c;
	if (h < 0.)
		return (0);
	h = sqrt(h);
	tmp = -b - h;
	if (tmp < 0.)
		tmp = -b + h;
	if (!(tmp > RT_EPS_SP && tmp < t_max))
		return (0);
	hr->t = tmp;
	return (1);
}

int		is_hit_sphere_gs(t_ray *ray, t_obj *sp, t_flt t_max, t_hit_rec *hr)
{
	t_vec3	l;
	t_flt	tca;
	t_flt	thc;
	t_flt	d2;
	t_flt	tmp;

	pvec3_sub(&sp->obj.sp.cent, &ray->orig, &l);
	tca = pvec3_dotr(&l, &ray->dir);
	if (tca < 0.)
		return (0);
	d2 = pvec3_dotr(&l, &l) - tca * tca;
	if (d2 >= sp->obj.sp.rp2 + RT_EPSILON)
		return (0);
	thc = sqrt(sp->obj.sp.rp2 - d2);
	tmp = tca - thc;
	if (tmp < 0.)
		tmp = tca + thc;
	if (!(tmp > RT_EPSILON && tmp < t_max))
		return (0);
	hr->t = tmp;
	return (1);
}

void	sphere_norm(t_obj *sp, t_hit_rec *hr, t_vec3 *norm)
{
	pvec3_unitsub(&hr->p, &sp->obj.sp.cent, norm);
}

void	sphere_norm_perturb_sin_new(t_obj *sp, t_hit_rec *hr, t_vec3 *norm)
{
	t_vec3	bitang;
	t_flt	cf;
	t_flt	phi;
	t_flt	theta;

	cf = sp->surf->cf1;
	pvec3_unitsub(&hr->p, &sp->obj.sp.cent, &hr->n);
	theta = asin(hr->n.y);
	phi = atan2(hr->n.x, hr->n.z);
	pgvec3(-sin(theta) * cos(phi), cos(theta), -sin(theta) * sin(phi), &bitang);
	pvec3_muln(&bitang, (sin(norm->y * 10 * RT_PI) /
		(cf + cf * norm->y * norm->y)));
	pvec3_addc(norm, bitang);
	pvec3_unit(norm);
}
