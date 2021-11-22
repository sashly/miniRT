/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_objs_cb.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 13:27:36 by sashly            #+#    #+#             */
/*   Updated: 2021/03/19 13:28:39 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser.h"

int		set_cube(t_vec3 *v3, float side, t_obj *cb)
{
	cb->type = GROUP;
	set_material(cb, &v3[2], NULL);
	cube_construct(v3, side, cb);
	return (1);
}

int		set_cube_raw(t_scene *sc, char **split)
{
	t_vec3	v3[3];
	float	side;
	int		flen;

	flen = 0;
	if (!(parse_vec3f(split[1], &v3[0])))
		return (ERR_INVSPEC);
	if (!(parse_vec3f(split[2], &v3[1])))
		return (ERR_INVSPEC);
	if (!check_norm(&v3[1]))
		return (ERR_INVNORM);
	pvec3_unit(&v3[1]);
	if (!(parse_vec3i(split[4], &v3[2])))
		return (ERR_INVRGB);
	side = ft_atof_m(split[3], &flen);
	if (*(split[3] + flen) || side < 0. - RT_EPSILON)
		return (ERR_INVSPEC);
	return (set_cube(v3, side, &sc->objs[sc->pobj--]));
}

void	cube_raw_set_color(t_vec3 *col, t_vec3 *raw)
{
	raw[2] = *col;
	raw[5] = *col;
	raw[8] = *col;
	raw[11] = *col;
	raw[14] = *col;
	raw[17] = *col;
}

void	cube_raw_set_points(t_nbasis *nb, float sd2, t_vec3 *raw)
{
	pgvec3(0., 0., 0., &raw[0]);
	raw[1] = pvec3_negr(&nb->v);
	raw[3] = pvec3_addcombr(&nb->u, sd2, &nb->v, sd2);
	raw[4] = nb->u;
	raw[6] = pvec3_addcombr(&nb->w, -sd2, &nb->v, sd2);
	raw[7] = pvec3_negr(&nb->w);
	raw[9] = pvec3_addcombr(&nb->u, -sd2, &nb->v, sd2);
	raw[10] = pvec3_negr(&nb->u);
	raw[12] = pvec3_addcombr(&nb->w, sd2, &nb->v, sd2);
	raw[13] = nb->w;
	pvec3_mulnr(&nb->v, 2.f * sd2, &raw[15]);
	raw[16] = nb->v;
}

int		cube_construct(t_vec3 *v3, float side, t_obj *cb)
{
	t_nbasis	nb;
	t_vec3		raw[18];

	if (!gr_memalloc(cb, 6))
		return (ERR_MEMALLOC);
	cb->obj.gr.gsize = 6;
	pgvec3(1., 0., 0., &nb.u);
	pgvec3(0., 1., 0., &nb.v);
	pgvec3(0., 0., 1., &nb.w);
	cube_raw_set_color(&v3[2], raw);
	cube_raw_set_points(&nb, side / 2.f, raw);
	set_square(&raw[0], side, &cb->obj.gr.gr[0]);
	set_square(&raw[3], side, &cb->obj.gr.gr[1]);
	set_square(&raw[6], side, &cb->obj.gr.gr[2]);
	set_square(&raw[9], side, &cb->obj.gr.gr[3]);
	set_square(&raw[12], side, &cb->obj.gr.gr[4]);
	set_square(&raw[15], side, &cb->obj.gr.gr[5]);
	cb_tmat_build(cb, &v3[0], &v3[1]);
	cb->hit_f = &is_hit_group;
	cb->norm_f = &group_norm;
	return (1);
}
