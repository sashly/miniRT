/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_memalloc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 13:26:00 by sashly            #+#    #+#             */
/*   Updated: 2021/03/19 13:26:29 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser.h"

int		objs_memalloc(t_scene *sc, int obj_size)
{
	int index;

	index = 0;
	while (index < obj_size)
	{
		sc->objs[index].aabb = NULL;
		sc->objs[index].parent = NULL;
		sc->objs[index].surf = NULL;
		sc->objs[index].m = (t_trmat *)malloc(sizeof(t_trmat));
		if (!sc->objs[index].m)
			return (objs_free(sc, index + 1, 0));
		sc->objs[index].m->tmat = NULL;
		sc->objs[index].m->inv = NULL;
		sc->objs[index].m->tinv = NULL;
		sc->objs[index].surf = (t_surf *)malloc(sizeof(t_surf));
		if (!sc->objs[index].surf)
			return (objs_free(sc, index + 1, 0));
		sc->objs[index].surf->txtr = NULL;
		sc->objs[index].surf->bmap = NULL;
		index++;
	}
	return (1);
}

void	cams_set_null(t_scene *sc, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		sc->cams[i].nb = NULL;
		sc->cams[i].tmat = NULL;
		sc->cams[i].tmat_i = NULL;
		i++;
	}
}

int		rt_scene_memalloc(t_scene **sc, int *c)
{
	if (!(*sc = (t_scene *)malloc(sizeof(t_scene))))
		return (ERR_MEMALLOC);
	(*sc)->cams = NULL;
	(*sc)->ambl = NULL;
	(*sc)->lgts = NULL;
	(*sc)->objs = NULL;
	(*sc)->back = NULL;
	if (!((*sc)->ambl = (t_light *)malloc(sizeof(t_light))))
		return (free_rt_scene(*sc, ERR_MEMALLOC));
	if (c[0] && !((*sc)->cams = (t_camera *)malloc(sizeof(t_camera) * c[0])))
		return (free_rt_scene(*sc, ERR_MEMALLOC));
	if (c[0])
		cams_set_null(*sc, c[0]);
	if (c[1] && !((*sc)->lgts = (t_light *)malloc(sizeof(t_light) * c[1])))
		return (free_rt_scene(*sc, ERR_MEMALLOC));
	if (c[2] && !((*sc)->objs = (t_obj *)malloc(sizeof(t_obj) * c[2])))
		return (free_rt_scene(*sc, ERR_MEMALLOC));
	if (c[2] && !objs_memalloc(*sc, c[2]))
		return (free_rt_scene(*sc, ERR_MEMALLOC));
	if (!((*sc)->back = (t_backg *)malloc(sizeof(t_backg))))
		return (free_rt_scene(*sc, ERR_MEMALLOC));
	(*sc)->back->skybox = NULL;
	return (1);
}

int		gr_memalloc(t_obj *gr, int obj_size)
{
	int index;

	index = 0;
	gr->obj.gr.gr = (t_obj *)malloc(sizeof(t_obj) * obj_size);
	if (!gr->obj.gr.gr)
		return (0);
	while (index < obj_size)
	{
		gr->obj.gr.gr[index].aabb = NULL;
		gr->obj.gr.gr[index].parent = NULL;
		gr->obj.gr.gr[index].m = (t_trmat *)malloc(sizeof(t_trmat));
		gr->obj.gr.gr[index].surf = (t_surf *)malloc(sizeof(t_surf));
		if (!gr->obj.gr.gr[index].m || !gr->obj.gr.gr[index].surf)
			return (gr_free(gr, index + 1, 0));
		index++;
	}
	return (1);
}
