/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 13:36:40 by sashly            #+#    #+#             */
/*   Updated: 2021/03/19 13:37:36 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser.h"

int	set_resolution(t_scene *scene, char **split)
{
	int	width;
	int	height;

	if ((width = ft_atoi_safe(split[1])) <= 0)
		return (0);
	if ((height = ft_atoi_safe(split[2])) <= 0)
		return (0);
	scene->wres = width;
	scene->hres = height;
	return (1);
}

int	set_amblight(t_scene *scene, char **split)
{
	float	tmp;
	int		flen;

	flen = 0;
	scene->ambl->type = LIGHT_AMB;
	tmp = ft_atof_m(split[1], &flen);
	if (*(split[1] + flen))
		return (ERR_INVSPEC);
	else if (tmp < 0.f)
		return (ERR_NEGV);
	else if (tmp > 1.f)
		return (ERR_OUTRNG);
	scene->ambl->ints = tmp;
	if (!(parse_vec3i(split[2], &scene->ambl->col)))
		return (ERR_INVRGB);
	pvec3_muln(&scene->ambl->col, scene->ambl->ints);
	return (1);
}

int	set_cameras(t_scene *sc, char **split)
{
	float	fov;
	int		curr;
	int		flen;
	t_vec3	or;

	curr = sc->pcam;
	if (!(parse_vec3f(split[1], &sc->cams[curr].pos)))
		return (ERR_INVSPEC);
	if (!(parse_vec3f(split[2], &or)))
		return (ERR_INVSPEC);
	if (!check_norm(&or))
		return (ERR_INVNORM);
	sc->cams[curr].orient = or;
	fov = ft_atof_m(split[3], &flen);
	if (*(split[3] + flen) || fov <= 0.f - RT_EQNEPS || fov >= 180 + RT_EQNEPS)
		return (ERR_INVFOV);
	sc->cams[curr].fov = fov * RT_PID180;
	sc->cams[curr].nb = NULL;
	sc->cams[curr].tmat = NULL;
	sc->cams[curr].tmat_i = NULL;
	sc->cams[curr].constr = &pinhole_construct;
	if (sc->pcam)
		sc->pcam -= 1;
	return (1);
}

int	set_direct_light(t_scene *sc, int mod)
{
	if (mod == 2)
	{
		sc->lgts[sc->plgt].type = LIGHT_DIR;
		sc->lgts[sc->plgt].f_gl = &get_l_directional;
		if (!check_norm(&sc->lgts[sc->plgt].pos))
			return (ERR_INVNORM);
		pvec3_unitneg(&sc->lgts[sc->plgt].pos);
	}
	if (sc->plgt)
		sc->plgt -= 1;
	return (1);
}

int	set_light(t_scene *sc, char **split, int mod)
{
	t_vec3	tmpv;
	float	tmp;
	int		flen;

	flen = 0;
	sc->lgts[sc->plgt].type = LIGHT_SPOT;
	sc->lgts[sc->plgt].f_gl = &get_l_pointlight;
	if (!(parse_vec3f(split[1], &tmpv)))
		return (ERR_INVSPEC);
	sc->lgts[sc->plgt].pos = tmpv;
	tmp = ft_atof_m(split[2], &flen);
	if (*(split[2] + flen))
		return (ERR_INVSPEC);
	if (tmp <= 0. - RT_EQNEPS || tmp >= 1. + RT_EQNEPS)
		return (ERR_OUTRNG);
	sc->lgts[sc->plgt].ints = tmp;
	if (!(parse_vec3i(split[3], &sc->lgts[sc->plgt].col)))
		return (ERR_INVRGB);
	pvec3_muln(&sc->lgts[sc->plgt].col, sc->lgts[sc->plgt].ints);
	return (set_direct_light(sc, mod));
}
