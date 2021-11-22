/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_objs_rc_ds.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 13:34:47 by sashly            #+#    #+#             */
/*   Updated: 2021/03/19 13:35:11 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser.h"

int	set_rectangle(t_vec3 *v3, t_obj *rc)
{
	rc->type = RECTANGLE;
	set_material(rc, &v3[3], NULL);
	rc->obj.rc.p = v3[0];
	rc->obj.rc.a = v3[1];
	rc->obj.rc.b = v3[2];
	return (1);
}

int	set_rect_raw(t_scene *sc, char **split)
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
	return (set_rectangle(v3, &sc->objs[sc->pobj--]));
}

int	set_disk(t_vec3 *v3, float rad, t_obj *ds)
{
	ds->type = DISK;
	set_material(ds, &v3[2], NULL);
	ds->obj.ds.p = v3[0];
	ds->obj.ds.n = v3[1];
	ds->obj.ds.r = rad;
	ds->obj.ds.rp2 = rad * rad;
	return (1);
}

int	set_disk_raw(t_scene *sc, char **split)
{
	t_vec3	v3[3];
	float	rad;
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
	rad = ft_atof_m(split[3], &flen) / 2.f;
	if (*(split[3] + flen))
		return (ERR_INVSPEC);
	return (set_disk(v3, rad, &sc->objs[sc->pobj--]));
}
