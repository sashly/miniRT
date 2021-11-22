/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_objs_quad_tr.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 13:33:55 by sashly            #+#    #+#             */
/*   Updated: 2021/03/19 13:34:27 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser.h"

int	set_triangle(t_vec3 *v3, t_obj *tr)
{
	tr->type = TRIANGLE;
	set_material(tr, &v3[3], NULL);
	tr->obj.tr.p1 = v3[0];
	tr->obj.tr.p2 = v3[1];
	tr->obj.tr.p3 = v3[2];
	pvec3_sub(&v3[1], &v3[0], &tr->obj.tr.e1);
	pvec3_sub(&v3[2], &v3[0], &tr->obj.tr.e2);
	pvec3_cross(&tr->obj.tr.e1, &tr->obj.tr.e2, &tr->obj.tr.n);
	pvec3_unit(&tr->obj.tr.n);
	tr->hit_f = &is_hit_triangle;
	tr->norm_f = &triangle_norm;
	return (1);
}

int	set_triang_raw(t_scene *sc, char **split)
{
	t_vec3 v3[4];

	if (!(parse_vec3f(split[1], &v3[0])))
		return (ERR_INVSPEC);
	if (!(parse_vec3f(split[2], &v3[1])))
		return (ERR_INVSPEC);
	if (!(parse_vec3f(split[3], &v3[2])))
		return (ERR_INVSPEC);
	if (!(parse_vec3i(split[4], &v3[3])))
		return (ERR_INVRGB);
	return (set_triangle(v3, &sc->objs[sc->pobj--]));
}

int	set_cylinder(t_vec3 *v3, float *f, int cap, t_obj *cy)
{
	cy->type = CYLINDER;
	set_material(cy, &v3[2], NULL);
	cy->obj.cy.a = v3[0];
	cy->obj.cy.na = v3[1];
	pvec3_addcomb(&cy->obj.cy.a, f[1], &cy->obj.cy.na, &cy->obj.cy.b);
	cy->obj.cy.r = f[0];
	cy->obj.cy.rp2 = f[0] * f[0];
	cy->obj.cy.h = f[1];
	cy->obj.cy.cap = cap;
	if (cap)
	{
		if (!cy_tmat_build(cy))
			return (ERR_MEMALLOC);
		cy->hit_f = &is_hit_cylinder_cp_t;
		cy->norm_f = &cylinder_norm_cp_t;
	}
	else
	{
		cy->hit_f = &is_hit_cylinder_la;
		cy->norm_f = &cylinder_norm_la;
	}
	return (1);
}

int	set_cone(t_vec3 *v3, float *f, t_obj *cn)
{
	cn->type = CONE;
	set_material(cn, &v3[2], NULL);
	cn->obj.cn.c = v3[0];
	cn->obj.cn.n = v3[1];
	cn->obj.cn.r = f[0];
	cn->obj.cn.h = f[1];
	cn->obj.cn.cap = 0;
	pvec3_addcomb(&v3[0], f[1], &v3[1], &cn->obj.cn.ph);
	cn->obj.cn.sin_th = sin(atan(f[0] / f[1]));
	cn_tmat_build(cn);
	cn->hit_f = &is_hit_cone;
	cn->norm_f = &cone_norm;
	return (1);
}

int	set_quadr_raw(t_scene *sc, char **split, int m)
{
	t_vec3	v3[3];
	float	f[2];
	int		flen;

	flen = 0;
	if (!(parse_vec3f(split[1], &v3[0])))
		return (ERR_INVSPEC);
	if (!(parse_vec3f(split[2], &v3[1])))
		return (ERR_INVSPEC);
	if (!check_norm(&v3[1]))
		return (ERR_INVNORM);
	pvec3_unit(&v3[1]);
	if (!(parse_vec3i(split[5], &v3[2])))
		return (ERR_INVRGB);
	f[0] = ft_atof_m(split[3], &flen) * 0.5f;
	if (*(split[3] + flen))
		return (ERR_INVSPEC);
	f[1] = ft_atof_m(split[4], &flen);
	if (*(split[4] + flen))
		return (ERR_INVSPEC);
	if (f[0] < 0. - RT_EPSILON || f[1] < 0. - RT_EPSILON)
		return (ERR_INVSPEC);
	if (m == 9)
		return (set_cone(v3, f, &sc->objs[sc->pobj--]));
	return (set_cylinder(v3, f, (m == 8 ? 1 : 0), &sc->objs[sc->pobj--]));
}
