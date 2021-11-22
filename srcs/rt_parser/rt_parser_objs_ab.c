/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_objs_ab.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 13:26:49 by sashly            #+#    #+#             */
/*   Updated: 2021/03/19 13:27:27 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser.h"

int	set_aabb(t_vec3 *v3, float *f, float *angls, t_obj *ab)
{
	ab->type = AABB;
	set_material(ab, &v3[1], NULL);
	ab->obj.ab.p = v3[0];
	ab->obj.ab.lx = f[0];
	ab->obj.ab.ly = f[1];
	ab->obj.ab.lz = f[2];
	ab_tmat_build(ab, angls[0], angls[1], angls[2]);
	ab->hit_f = &is_hit_aabb;
	ab->norm_f = &aabb_norm;
	return (1);
}

int	set_aabb_raw(t_scene *sc, char **split)
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
	f[0] = ft_atof_m(split[2], &flen);
	if (*(split[2] + flen))
		return (ERR_INVSPEC);
	f[1] = ft_atof_m(split[3], &flen);
	if (*(split[3] + flen))
		return (ERR_INVSPEC);
	f[2] = ft_atof_m(split[4], &flen);
	if (*(split[4] + flen))
		return (ERR_INVSPEC);
	if (f[0] < 0. || f[1] < 0. || f[2] < 0.)
		return (ERR_INVSPEC);
	angls[0] = ft_atof_m(split[6], &flen);
	angls[1] = ft_atof_m(split[7], &flen);
	angls[2] = ft_atof_m(split[8], &flen);
	return (set_aabb(v3, f, angls, &sc->objs[sc->pobj--]));
}
