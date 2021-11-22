/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 13:20:29 by sashly            #+#    #+#             */
/*   Updated: 2021/03/19 13:21:15 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser.h"

void	set_cfilter(t_scene *sc, int cf)
{
	sc->conf.cfilt = (char)cf;
	if (cf == 1)
		sc->conf.f_colfilt = &colfilt_grayscale;
	else if (cf == 2)
		sc->conf.f_colfilt = &colfilt_sepia;
	else if (cf == 3)
		sc->conf.f_colfilt = &colfilt_red;
	else if (cf == 4)
		sc->conf.f_colfilt = &colfilt_green;
	else if (cf == 5)
		sc->conf.f_colfilt = &colfilt_blue;
}

int		set_colorfilter(t_scene *sc, char **split)
{
	if (split[2])
		return (ERR_INVSPEC);
	if (!ft_strcmp(split[1], "gray"))
		set_cfilter(sc, 1);
	else if (!ft_strcmp(split[1], "sepia"))
		set_cfilter(sc, 2);
	else if (!ft_strcmp(split[1], "r"))
		set_cfilter(sc, 3);
	else if (!ft_strcmp(split[1], "g"))
		set_cfilter(sc, 4);
	else if (!ft_strcmp(split[1], "b"))
		set_cfilter(sc, 5);
	else
		return (ERR_INVSPEC);
	return (1);
}

int		set_aaliasing(t_scene *sc, char **split)
{
	int aa;

	if (split[2])
		return (ERR_INVSPEC);
	aa = ft_atoi_safe(split[1]);
	if (aa <= 0 || aa > 36)
		return (ERR_INVSPEC);
	sc->conf.aalias = (char)sqrt((double)aa);
	sc->f_sampler = &rt_sampler_aa_reg;
	return (1);
}

int		set_back_skybox(t_scene *sc, char **split)
{
	int		ret;
	t_flt	tmp;
	t_vec3	v3[2];

	ret = check_xpm_file(split[1]);
	if (ret != 1)
		return (ret);
	tmp = ft_atof_m(split[2], &ret);
	if (*(split[2] + ret))
		return (ERR_INVSPEC);
	if (tmp <= 0. - RT_EQNEPS || tmp >= 1. + RT_EQNEPS)
		return (ERR_OUTRNG);
	sc->back->skybox = (t_skybox *)malloc(sizeof(t_skybox));
	if (!sc->back->skybox)
		return (ERR_MEMALLOC);
	sc->back->mod = BG_SKYBOX;
	sc->back->skybox->lookup.name = ft_strdup(split[1]);
	sc->back->skybox->ints = tmp;
	pgvec3(0., 0., 0., &v3[0]);
	pgvec3(1., 1., 1., &v3[1]);
	if (!(sc->back->skybox->sp.surf = (t_surf *)malloc(sizeof(t_surf))))
		return (ERR_MEMALLOC);
	set_sphere(v3, SKYBOX_SIZE, &sc->back->skybox->sp);
	sc->conf.pics_to_load++;
	return (1);
}

int		set_background(t_scene *sc, char **split)
{
	t_vec3 col[2];

	if (split[1] && !split[2])
	{
		if (!(parse_vec3i(split[1], &col[0])))
			return (ERR_INVRGB);
		sc->back->mod = BG_MONO;
		sc->back->col1 = col[0];
	}
	else if (split[1] && split[2] && !split[3])
	{
		if (!(parse_vec3i(split[1], &col[0])))
			return (set_back_skybox(sc, split));
		if (!(parse_vec3i(split[2], &col[1])))
			return (ERR_INVRGB);
		sc->back->mod = BG_LERP;
		sc->back->col1 = col[0];
		sc->back->col2 = col[1];
	}
	else
		return (ERR_INVSPEC);
	return (1);
}
