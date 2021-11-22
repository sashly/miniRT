/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_square.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 23:05:53 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 23:06:55 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	get_square_uv(t_obj *sq, t_hit_rec *hr, t_flt *u, t_flt *v)
{
	t_nbasis	nb;
	t_vec3		lvec;
	t_flt		uv[2];

	pvec3_sub(&hr->p, &sq->obj.sq.p, &lvec);
	gnbasis_norm(&sq->obj.sq.n, gvec3(1., 0., 0.), gvec3(0., 1., 0.), &nb);
	uv[0] = pvec3_dotr(&lvec, &nb.u);
	uv[1] = pvec3_dotr(&lvec, &nb.w);
	*u = (sq->obj.sq.sd2 + uv[0]) / sq->obj.sq.side;
	*v = 1. - (sq->obj.sq.sd2 + uv[1]) / sq->obj.sq.side;
}

void	square_bump_mapping(t_obj *sq, t_hit_rec *hr, t_vec3 *norm)
{
	t_nbasis	tang;
	t_vec3		bump_col;
	t_flt		uv[2];
	int			i;
	int			j;

	gnbasis_norm(&sq->obj.sq.n, gvec3(1., 0., 0.), gvec3(0., 1., 0.), &tang);
	get_square_uv(sq, hr, &uv[0], &uv[1]);
	i = (int)(uv[0] * ((t_flt)sq->surf->bmap->w - 1.));
	j = (int)(uv[1] * ((t_flt)sq->surf->bmap->h - 1.));
	bgrt_to_vec3((sq->surf->bmap->arr + j * 4 * sq->surf->bmap->w + i * 4),
			&bump_col);
	pvec3_muln(&bump_col, 2.);
	bump_col.x -= 1.;
	bump_col.y -= 1.;
	bump_col.z -= 1.;
	pvec3_muln(&tang.u, sq->surf->bmap_cf * bump_col.x);
	pvec3_muln(&tang.w, sq->surf->bmap_cf * bump_col.y);
	pvec3_muln(&tang.v, bump_col.z);
	pvec3_add3(&tang.u, &tang.v, &tang.w, norm);
	pvec3_unit(norm);
}

void	uv_mapping_square(t_obj *obj, t_hit_rec *hr, t_vec3 *outcol)
{
	t_flt	uv[2];
	int		i;
	int		j;

	get_square_uv(obj, hr, &uv[0], &uv[1]);
	i = (int)(uv[0] * ((t_flt)obj->surf->txtr->w - 1.));
	j = (int)((1. - uv[1]) * ((t_flt)obj->surf->txtr->h - 1.));
	bgrt_to_vec3((obj->surf->txtr->arr + j * 4 * obj->surf->txtr->w + i * 4),
			outcol);
}
