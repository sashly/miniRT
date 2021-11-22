/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_shade_backg_nmap.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 14:52:52 by sashly            #+#    #+#             */
/*   Updated: 2021/03/19 14:54:01 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	rt_shade_backg(t_scene *sc, t_ray *ray, t_vec3 *out_col)
{
	t_flt	t;
	t_vec3	up;
	t_vec3	down;

	if (sc->back->mod == BG_MONO)
		*out_col = sc->back->col1;
	else if (sc->back->mod == BG_LERP)
	{
		t = 0.5 * (ray->dir.y + 1.);
		pvec3_mulnr(&sc->back->col2, t, &up);
		pvec3_mulnr(&sc->back->col1, (1. - t), &down);
		pvec3_add(&up, &down, out_col);
	}
	else if (sc->back->mod == BG_SKYBOX)
		rt_shade_skybox(sc, ray, out_col);
}

void	rt_shade_skybox(t_scene *sc, t_ray *ray, t_vec3 *out_col)
{
	t_hit_rec	hr;
	t_flt		uv[2];
	int			i;
	int			j;

	is_hit_sphere_alg(ray, &sc->back->skybox->sp, RT_HUGEVAL, &hr);
	ray_point(ray, hr.t, &hr.p);
	sphere_norm(&sc->back->skybox->sp, &hr, &hr.n);
	get_sphere_uv(&hr, &uv[0], &uv[1]);
	i = (int)(uv[0] * ((t_flt)sc->back->skybox->lookup.w - 1.));
	j = (int)(uv[1] * ((t_flt)sc->back->skybox->lookup.h - 1.));
	bgrt_to_vec3((sc->back->skybox->lookup.arr + j * 4 *
				sc->back->skybox->lookup.w + i * 4), out_col);
	pvec3_muln(out_col, sc->back->skybox->ints);
}

void	rt_shade_nmap(t_scene *sc, t_ray *ray, t_hit_rec *hr, t_vec3 *out_col)
{
	(void)sc;
	(void)ray;
	pvec3_add_const(&hr->n, 1., out_col);
	pvec3_muln(out_col, 0.5);
}
