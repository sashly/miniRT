/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_objs_pl_sq.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 13:29:22 by sashly            #+#    #+#             */
/*   Updated: 2021/03/19 13:29:41 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser.h"

int	set_plane(t_vec3 *cd, t_vec3 *n, t_vec3 *col, t_obj *pl)
{
	pl->type = PLANE;
	set_material(pl, col, NULL);
	pl->obj.pl.p = *cd;
	pl->obj.pl.n = *n;
	pl->hit_f = &is_hit_plane;
	pl->norm_f = &plane_norm;
	return (1);
}

int	set_plane_raw(t_scene *sc, char **split)
{
	t_vec3 v3[3];

	if (!(parse_vec3f(split[1], &v3[0])))
		return (ERR_INVSPEC);
	if (!(parse_vec3f(split[2], &v3[1])))
		return (ERR_INVSPEC);
	if (!check_norm(&v3[1]) || !handle_norm(&v3[1]))
		return (ERR_INVNORM);
	if (!(parse_vec3i(split[3], &v3[2])))
		return (ERR_INVRGB);
	return (set_plane(&v3[0], &v3[1], &v3[2], &sc->objs[sc->pobj--]));
}

int	set_square(t_vec3 *v3, float side, t_obj *sq)
{
	sq->type = SQUARE;
	set_material(sq, &v3[2], NULL);
	sq->obj.sq.p = v3[0];
	sq->obj.sq.n = v3[1];
	sq->obj.sq.side = side;
	sq->obj.sq.sd2 = side * 0.5;
	sq->hit_f = &is_hit_square;
	sq->norm_f = &square_norm;
	return (1);
}

int	set_square_raw(t_scene *sc, char **split)
{
	t_vec3	v3[3];
	float	side;
	int		flen;

	flen = 0;
	if (!(parse_vec3f(split[1], &v3[0])))
		return (ERR_INVSPEC);
	if (!(parse_vec3f(split[2], &v3[1])))
		return (ERR_INVSPEC);
	if (!check_norm(&v3[1]) || !handle_norm(&v3[1]))
		return (ERR_INVNORM);
	if (!(parse_vec3i(split[4], &v3[2])))
		return (ERR_INVRGB);
	side = ft_atof_m(split[3], &flen);
	if (*(split[3] + flen) || side < 0. - RT_EPSILON)
		return (ERR_INVSPEC);
	return (set_square(v3, side, &sc->objs[sc->pobj--]));
}
