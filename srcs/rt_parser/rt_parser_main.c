/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 13:24:33 by sashly            #+#    #+#             */
/*   Updated: 2021/03/19 13:25:48 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser.h"

int		parser_main(char *name, t_scene **sc)
{
	int		count[IND_COUNT_SIZE];
	t_list	*fcache;
	char	*errstr;
	int		fd;

	fcache = NULL;
	if (!(check_rt_name(name)))
		return (rt_error(name, ERR_INVEXT, &fcache));
	if ((fd = open(name, O_RDONLY)) == -1)
		return (rt_error(name, ERR_OPEN, &fcache));
	if (!(cache_file(fd, &fcache)))
		return (rt_error(name, ERR_READ, &fcache));
	if ((fd = check_and_count_cache(fcache, count, &errstr)) != 1)
		return (rt_error(errstr, fd, &fcache));
	if ((fd = build_rt_scene_main(sc, fcache, count, &errstr)) != 1)
		return (rt_error(errstr, fd, &fcache));
	if (!(*sc)->cams[0].constr(&(*sc)->cams[0], (*sc)->wres, (*sc)->hres))
		return (rt_error(errstr, ERR_MEMALLOC, &fcache));
	ft_lstclear(&fcache, &del_split);
	return (1);
}

int		build_rt_scene_main(t_scene **sc, t_list *fcache,
			int *count, char **errstr)
{
	int ret;

	if (rt_scene_memalloc(sc, count) != 1)
		return (ERR_MEMALLOC);
	rt_scene_init(*sc, count);
	if ((ret = rt_scene_content(*sc, fcache, errstr)) != 1)
		return (free_rt_scene(*sc, ret));
	(*sc)->pobj = 0;
	(*sc)->pcam = 0;
	return (1);
}

void	rt_scene_init(t_scene *sc, int *count)
{
	sc->f_sampler = &rt_sampler_naa;
	sc->f_shader = &rt_shade_phong;
	sc->ambl->ints = 0.;
	sc->ambl->col = gvec3(0., 0., 0.);
	sc->back->mod = BG_MONO;
	sc->back->col1 = gvec3(0., 0., 0.);
	sc->back->skybox = NULL;
	sc->conf.f_tonemap = &rt_tonemap_cap;
	sc->conf.aalias = AA_NONE;
	sc->conf.cfilt = CF_NONE;
	sc->conf.mthred = MT_DEFL;
	sc->conf.nmap = NM_NONE;
	sc->conf.gamma = RT_GAMMA;
	sc->cam_size = count[0];
	sc->lgt_size = count[1];
	sc->obj_size = count[2];
	sc->pcam = sc->cam_size - 1;
	sc->plgt = sc->lgt_size - 1;
	sc->pobj = sc->obj_size - 1;
	sc->conf.pics_to_load = 0;
}

int		rt_scene_content(t_scene *scene, t_list *fcache, char **errstr)
{
	char	**split;
	int		ret;
	int		id;

	while (fcache)
	{
		split = (char **)fcache->content;
		*errstr = split[0];
		id = find_ident(split[0]);
		if (id == 16 && (set_resolution(scene, split)) != 1)
			return (ERR_WRRES);
		if (id == 17 && (ret = set_amblight(scene, split)) != 1)
			return (ret);
		if ((id == 1 || id == 2) && (ret = set_light(scene, split, id)) != 1)
			return (ret);
		if (id == 0 && (ret = set_cameras(scene, split)) != 1)
			return (ret);
		if ((id >= 3 && id <= 15) && (ret = set_objects(scene, split, id)) != 1)
			return (ret);
		if (id > 17 && (ret = set_bonus(scene, split, id)) != 1)
			return (ret);
		fcache = fcache->next;
	}
	return (1);
}

int		set_bonus(t_scene *scene, char **split, int id)
{
	if (id == 18)
		return (set_colorfilter(scene, split));
	else if (id == 19)
		return (set_aaliasing(scene, split));
	else if (id == 20)
		return (set_background(scene, split));
	return (ERR_INVTY);
}
