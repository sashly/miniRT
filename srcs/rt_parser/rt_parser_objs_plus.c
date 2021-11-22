/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_objs_plus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 13:29:57 by sashly            #+#    #+#             */
/*   Updated: 2021/03/19 13:31:12 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser.h"

/*
**	Bonus additional specifications:
**	"+" - means there is an additional spec for an object;
**	"+ checker3D |RGB| |F|" - 3d checker with size;
**	"+ checker2D |RGB| |F|" - 2d checker with size;
**	"+ checker2DO |RGB| |RGB| |F| |F|" - 2d checker with outline (2 colors, 2
**		coefficients);
**	"+ norm_sine" - sphere normal perturbation according sine law;
**	"+ texture ./image.xpm" - texture for uv mapping from an image;
**	"+ bmap ./image.xpm |F|" - bump map texture from an image;
**	"+ texture_bmap ./image1.xpm ./image2.xpm |F|" - texture and bump map;
*/

int		set_plus_bonus(t_scene *sc, char **spl, int id)
{
	int i;

	i = ident_size(id) + 1;
	if (spl[i] && !ft_strcmp(spl[i], "+"))
	{
		if (spl[i + 1] && !ft_strcmp(spl[i + 1], "checker3D"))
			return (set_plus_checker3d(sc, spl, i));
		else if (spl[i + 1] && id == 3 && !ft_strcmp(spl[i + 1], "checker2D"))
			return (set_plus_checker2d_sp(sc, spl, i, 0));
		else if (spl[i + 1] && id == 3 && !ft_strcmp(spl[i + 1], "checker2DO"))
			return (set_plus_checker2d_sp(sc, spl, i, 1));
		else if (spl[i + 1] && id == 3 && !ft_strcmp(spl[i + 1], "norm_sine"))
			return (set_plus_normsine_sp(sc, spl, i));
		else if (spl[i + 1] && !ft_strcmp(spl[i + 1], "texture"))
			return (set_plus_texture(sc, spl, id, i));
		else if (spl[i + 1] && !ft_strcmp(spl[i + 1], "bmap"))
			return (set_plus_bmap(sc, spl, id, i));
		else if (spl[i + 1] && !ft_strcmp(spl[i + 1], "texture_bmap"))
			return (set_plus_textrbmap(sc, spl, id, i));
		else
			return (ERR_INVSPEC);
	}
	return (1);
}

int		set_plus_checker3d(t_scene *sc, char **spl, int i)
{
	t_vec3	col;
	t_flt	tmp;
	int		flen;
	int		pobj;

	if (!spl[i + 2] || !spl[i + 3] || spl[i + 4])
		return (ERR_INVSPEC);
	if (!(parse_vec3i(spl[i + 2], &col)))
		return (ERR_INVRGB);
	tmp = ft_atof_m(spl[i + 3], &flen);
	if (*(spl[i + 3] + flen) || tmp <= 0.)
		return (ERR_INVSPEC);
	pobj = sc->pobj + 1;
	sc->objs[pobj].surf->col1 = col;
	sc->objs[pobj].surf->cf1 = tmp;
	sc->objs[pobj].surf->colmod_f = COLMOD_FTXTR;
	sc->objs[pobj].surf->f_txtr = &checker3d_txtr_floor;
	return (1);
}

int		set_plus_checker2do_sp(t_scene *sc, char **spl, int i)
{
	t_vec3	col[2];
	t_flt	f[2];
	int		flen;
	int		pobj;

	if (!spl[i + 2] || !spl[i + 3] || !spl[i + 4] || !spl[i + 5] || spl[i + 6])
		return (ERR_INVSPEC);
	if (!(parse_vec3i(spl[i + 2], &col[0])))
		return (ERR_INVRGB);
	if (!(parse_vec3i(spl[i + 3], &col[1])))
		return (ERR_INVRGB);
	f[0] = ft_atof_m(spl[i + 4], &flen);
	if (*(spl[i + 4] + flen) || f[0] <= 0.)
		return (ERR_INVSPEC);
	f[1] = ft_atof_m(spl[i + 5], &flen);
	if (*(spl[i + 5] + flen) || f[1] <= 0.)
		return (ERR_INVSPEC);
	pobj = sc->pobj + 1;
	sc->objs[pobj].surf->colmod_f = COLMOD_FTXTR;
	sc->objs[pobj].surf->col1 = col[0];
	sc->objs[pobj].surf->col2 = col[1];
	sc->objs[pobj].surf->cf1 = f[0];
	sc->objs[pobj].surf->cf2 = f[1];
	sc->objs[pobj].surf->f_txtr = &checker2d_outline_sphere;
	return (1);
}

int		set_plus_checker2d_sp(t_scene *sc, char **spl, int i, int is_outl)
{
	t_vec3	col;
	t_flt	tmp;
	int		flen;
	int		pobj;

	if (is_outl)
		return (set_plus_checker2do_sp(sc, spl, i));
	if (!spl[i + 2] || !spl[i + 3] || spl[i + 4])
		return (ERR_INVSPEC);
	if (!(parse_vec3i(spl[i + 2], &col)))
		return (ERR_INVRGB);
	tmp = ft_atof_m(spl[i + 3], &flen);
	if (*(spl[i + 3] + flen) || tmp <= 0.)
		return (ERR_INVSPEC);
	pobj = sc->pobj + 1;
	sc->objs[pobj].surf->colmod_f = COLMOD_FTXTR;
	sc->objs[pobj].surf->col1 = col;
	sc->objs[pobj].surf->cf1 = tmp;
	sc->objs[pobj].surf->f_txtr = &checker2d_sphere;
	return (1);
}
