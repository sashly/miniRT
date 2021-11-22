/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_shade_phong.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 14:54:14 by sashly            #+#    #+#             */
/*   Updated: 2021/03/19 14:55:47 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		rt_is_shadowed(t_scene *sc, t_light *light, t_hit_rec *hr, t_vec3 *l)
{
	t_hit_rec	hrec;
	t_ray		ray_to_light;
	t_vec3		vec;
	t_vec3		orig;
	t_flt		dist;

	if (light->type == LIGHT_SPOT)
	{
		pvec3_sub(&light->pos, &hr->p, &vec);
		dist = pvec3_len(&vec);
	}
	else
		dist = HUGE_VAL;
	pvec3_addcomb(&hr->p, RT_EPSILON, &hr->n, &orig);
	pgray(&orig, l, &ray_to_light);
	if (rt_intersect(sc, &ray_to_light, dist, &hrec))
		return (1);
	return (0);
}

t_vec3	diffuse_col(t_light *light, t_hit_rec *hrec, t_vec3 *lvec)
{
	t_vec3	diff;
	t_flt	r;

	pvec3_dot(&hrec->n, lvec, &r);
	pvec3_mulnr(&light->col, r, &diff);
	if (diff.x < 0. || diff.y < 0. || diff.z < 0.)
		pgvec3(0., 0., 0., &diff);
	return (diff);
}

t_vec3	specular_col(t_light *lgt, t_ray *ray, t_hit_rec *hr, t_surf *surf)
{
	t_vec3	spec;
	t_vec3	evec;
	t_vec3	lvec;
	t_vec3	rvec;
	t_flt	r;

	pgvec3(0., 0., 0., &spec);
	lgt->f_gl(lgt, &hr->p, &lvec);
	pvec3_neg(&lvec);
	evec = vec3_neg(ray->dir);
	pvec3_dot(&lvec, &hr->n, &r);
	pvec3_addcomb(&lvec, -2. * r, &hr->n, &rvec);
	pvec3_dot(&rvec, &evec, &r);
	if (r < 0.)
		return (spec);
	r = pow(r, surf->kshin);
	pvec3_mulnr(&lgt->col, r, &spec);
	pvec3_muln(&spec, surf->kspec);
	return (spec);
}

void	rt_shade_phong(t_scene *sc, t_ray *ray, t_hit_rec *hr, t_vec3 *out_col)
{
	t_vec3	diff;
	t_vec3	spec;
	t_vec3	lvec;
	t_vec3	objcol;
	int		i;

	i = 0;
	pgvec3(0., 0., 0., &diff);
	pgvec3(0., 0., 0., &spec);
	while (i < sc->lgt_size)
	{
		sc->lgts[i].f_gl(&sc->lgts[i], &hr->p, &lvec);
		if (!rt_is_shadowed(sc, &sc->lgts[i], hr, &lvec))
		{
			pvec3_addc(&diff, diffuse_col(&sc->lgts[i], hr, &lvec));
			pvec3_addc(&spec, specular_col(&sc->lgts[i], ray, hr,
						sc->objs[hr->obj_id].surf));
		}
		i++;
	}
	pvec3_add3(&sc->ambl->col, &diff, &spec, out_col);
	objcol = sc->objs[hr->obj_id].surf->col;
	if (sc->objs[hr->obj_id].surf->colmod_f != COLMOD_MONO)
		sc->objs[hr->obj_id].surf->f_txtr(&sc->objs[hr->obj_id], hr, &objcol);
	pvec3_mul(out_col, &objcol);
}
