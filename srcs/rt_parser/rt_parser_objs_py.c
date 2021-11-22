/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_objs_py.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 13:32:30 by sashly            #+#    #+#             */
/*   Updated: 2021/03/19 13:32:39 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser.h"

int	set_pyramid(t_vec3 *v3, float *f, t_obj *py)
{
	py->type = GROUP;
	set_material(py, &v3[2], NULL);
	pyramid_construct(v3, f, py);
	return (1);
}

int	set_pyramid_raw(t_scene *sc, char **split)
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
	f[0] = ft_atof_m(split[3], &flen);
	if (*(split[3] + flen))
		return (ERR_INVSPEC);
	f[1] = ft_atof_m(split[4], &flen);
	if (*(split[4] + flen))
		return (ERR_INVSPEC);
	if (f[0] < 0. - RT_EPSILON || f[1] < 0. - RT_EPSILON)
		return (ERR_INVSPEC);
	return (set_pyramid(v3, f, &sc->objs[sc->pobj--]));
}
