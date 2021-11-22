/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_sphere.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 23:04:16 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 23:05:43 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	get_sphere_uv(t_hit_rec *hr, t_flt *u, t_flt *v)
{
	t_flt	theta;
	t_flt	phi;

	theta = asin(hr->n.y);
	phi = atan2(hr->n.x, hr->n.z);
	*u = (phi + RT_PI) * RT_INVPI_2;
	*v = 1. - (theta + RT_PI_2) * RT_INVPI;
}

void	uv_mapping_sphere(t_obj *obj, t_hit_rec *hr, t_vec3 *outcol)
{
	t_flt	uv[2];
	int		i;
	int		j;

	get_sphere_uv(hr, &uv[0], &uv[1]);
	i = (int)(uv[0] * ((t_flt)obj->surf->txtr->w - 1.));
	j = (int)(uv[1] * ((t_flt)obj->surf->txtr->h - 1.));
	bgrt_to_vec3((obj->surf->txtr->arr + j * 4 * obj->surf->txtr->w + i * 4),
			outcol);
}

void	sphere_bump_mapping(t_obj *sp, t_hit_rec *hr, t_vec3 *norm)
{
	t_flt	uv[2];
	t_flt	phi;
	t_vec3	tang[2];
	int		ij[2];
	t_vec3	bump_col;

	pvec3_unitsub(&hr->p, &sp->obj.sp.cent, &hr->n);
	get_sphere_uv(hr, &uv[0], &uv[1]);
	phi = atan2(hr->n.z, hr->n.x);
	pgvec3(-sin(phi), 0., cos(phi), &tang[0]);
	pvec3_cross(&hr->n, &tang[0], &tang[1]);
	ij[0] = (int)(uv[0] * ((t_flt)sp->surf->bmap->w - 1.));
	ij[1] = (int)(uv[1] * ((t_flt)sp->surf->bmap->h - 1.));
	bgrt_to_vec3((sp->surf->bmap->arr + ij[1] * 4 *
				sp->surf->bmap->w + ij[0] * 4), &bump_col);
	pvec3_muln(&bump_col, 2.);
	bump_col.x -= 1.;
	bump_col.y -= 1.;
	bump_col.z -= 1.;
	pvec3_muln(&tang[0], sp->surf->bmap_cf * bump_col.y);
	pvec3_muln(&tang[1], sp->surf->bmap_cf * bump_col.x);
	pvec3_muln(&hr->n, bump_col.z);
	pvec3_add3(&hr->n, &tang[0], &tang[1], norm);
	pvec3_unit(norm);
}
