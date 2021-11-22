/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_objs_sp_el.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 13:35:25 by sashly            #+#    #+#             */
/*   Updated: 2021/03/19 13:36:17 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser.h"

int	set_sphere(t_vec3 *v3, t_flt rad, t_obj *sp)
{
	sp->type = SPHERE;
	set_material(sp, &v3[1], NULL);
	sp->surf->colmod_f = COLMOD_MONO;
	sp->obj.sp.r = rad;
	sp->obj.sp.rp2 = rad * rad;
	sp->obj.sp.cent = v3[0];
	sp->hit_f = &is_hit_sphere_alg;
	sp->norm_f = &sphere_norm;
	return (1);
}

int	set_sphere_raw(t_scene *sc, char **split)
{
	t_vec3	v3[2];
	float	rad;
	int		flen;

	flen = 0;
	if (!(parse_vec3f(split[1], &v3[0])))
		return (ERR_INVSPEC);
	if (!(parse_vec3i(split[3], &v3[1])))
		return (ERR_INVRGB);
	rad = ft_atof_m(split[2], &flen) * 0.5f;
	if (*(split[2] + flen))
		return (ERR_INVSPEC);
	if (rad <= 0. - RT_EPSILON)
		return (ERR_OUTRNG);
	return (set_sphere(v3, rad, &sc->objs[sc->pobj--]));
}

int	set_ellipsoid(t_vec3 *v3, float *f, float *angls, t_obj *el)
{
	el->type = ELLIPSD;
	el->obj.el.cent = v3[0];
	set_material(el, &v3[1], NULL);
	el->obj.el.r1 = f[0];
	el->obj.el.r2 = f[1];
	el->obj.el.r3 = f[2];
	el_tmat_build(el, angls[0], angls[1], angls[2]);
	el->hit_f = &is_hit_ellipsoid;
	el->norm_f = &ellipsoid_norm;
	return (1);
}

int	set_ellips_raw(t_scene *sc, char **split)
{
	t_vec3	v3[2];
	float	f[3];
	float	angls[3];
	int		flen;

	flen = 0;
	if (!(parse_vec3f(split[1], &v3[0])))
		return (ERR_INVSPEC);
	if (!(parse_vec3i(split[5], &v3[1])))
		return (ERR_INVRGB);
	f[0] = ft_atof_m(split[2], &flen) * 0.5f;
	if (*(split[2] + flen))
		return (ERR_INVSPEC);
	f[1] = ft_atof_m(split[3], &flen) * 0.5f;
	if (*(split[3] + flen))
		return (ERR_INVSPEC);
	f[2] = ft_atof_m(split[4], &flen) * 0.5f;
	if (*(split[4] + flen))
		return (ERR_INVSPEC);
	if (f[0] < 0. || f[1] < 0. || f[2] < 0.)
		return (ERR_OUTRNG);
	angls[0] = ft_atof_m(split[6], &flen);
	angls[1] = ft_atof_m(split[7], &flen);
	angls[2] = ft_atof_m(split[8], &flen);
	return (set_ellipsoid(v3, f, angls, &sc->objs[sc->pobj--]));
}
