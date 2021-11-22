/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_objs_main.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 13:28:49 by sashly            #+#    #+#             */
/*   Updated: 2021/03/19 13:29:07 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser.h"

/*
** SET_OBJECTS functions:
** Indices for objects: sphere - 3; plane - 4; square - 5; triangle - 6;
** cylinder - 7; capped cylinder - 8; cone - 9; rectangle - 10; disk - 11;
** aabb - 12; cube - 13; pyramid - 14; ellipsoid - 15;
*/

int		set_objects(t_scene *sc, char **spl, int id)
{
	int ret;

	sc->objs[sc->pobj].obj_id = sc->pobj;
	if (id == 3 && (ret = set_sphere_raw(sc, spl)) != 1)
		return (ret);
	if (id == 4 && (ret = set_plane_raw(sc, spl)) != 1)
		return (ret);
	if (id == 5 && (ret = set_square_raw(sc, spl)) != 1)
		return (ret);
	if (id == 6 && (ret = set_triang_raw(sc, spl)) != 1)
		return (ret);
	if ((id >= 7 && id <= 9) && (ret = set_quadr_raw(sc, spl, id)) != 1)
		return (ret);
	if (id == 11 && (ret = set_disk_raw(sc, spl)) != 1)
		return (ret);
	if (id == 12 && (ret = set_aabb_raw(sc, spl)) != 1)
		return (ret);
	if (id == 13 && (ret = set_cube_raw(sc, spl)) != 1)
		return (ret);
	if (id == 14 && (ret = set_pyramid_raw(sc, spl)) != 1)
		return (ret);
	if (id == 15 && (ret = set_ellips_raw(sc, spl)) != 1)
		return (ret);
	return (set_plus_bonus(sc, spl, id));
}

void	set_material(t_obj *obj, t_vec3 *col, t_flt *kffs)
{
	obj->surf->col = *col;
	obj->surf->colmod_f = COLMOD_MONO;
	obj->surf->normmod_f = NORMMOD_DEF;
	obj->surf->txtr = NULL;
	obj->surf->bmap = NULL;
	obj->surf->bmap_cf = 1.;
	if (!kffs)
	{
		obj->surf->kamb = DEF_AMB;
		obj->surf->kdiff = DEF_DIFF;
		obj->surf->kspec = DEF_SPEC;
		obj->surf->kshin = DEF_SHIN;
		obj->surf->krefl = DEF_REFL;
		obj->surf->ktran = DEF_TRAN;
		obj->surf->ref_ind = DEF_REFI;
	}
}
