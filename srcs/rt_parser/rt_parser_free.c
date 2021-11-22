/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 13:22:53 by sashly            #+#    #+#             */
/*   Updated: 2021/03/19 13:24:20 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser.h"

void	del_split(void *content)
{
	char **split;

	split = (char **)content;
	while (*split)
	{
		free(*split);
		split++;
	}
	free(content);
}

int		free_rt_scene(t_scene *scene, int ret)
{
	if (scene->ambl)
		free(scene->ambl);
	if (scene->cam_size)
		cams_free(scene);
	if (scene->cams)
		free(scene->cams);
	if (scene->lgts)
		free(scene->lgts);
	if (scene->obj_size)
		objs_free(scene, scene->obj_size, 1);
	if (scene->objs)
		free(scene->objs);
	if (scene->back)
	{
		if (scene->back->skybox)
			free_ptrs(scene->back->skybox->lookup.name,
					scene->back->skybox->sp.surf, scene->back->skybox, NULL);
		free(scene->back);
	}
	free(scene);
	return (ret);
}

void	cams_free(t_scene *sc)
{
	int i;

	i = 0;
	while (i < sc->cam_size)
	{
		if (sc->cams[i].nb)
			free(sc->cams[i].nb);
		if (sc->cams[i].tmat)
			free(sc->cams[i].tmat);
		if (sc->cams[i].tmat_i)
			free(sc->cams[i].tmat_i);
		i++;
	}
}

int		objs_free(t_scene *sc, int obj_size, int ret)
{
	int i;

	i = 0;
	while (i < obj_size)
	{
		if (sc->objs[i].type == GROUP)
			gr_free(&sc->objs[i], sc->objs[i].obj.gr.gsize, 1);
		else
		{
			if (sc->objs[i].m->tmat)
				free_ptrs(sc->objs[i].m->tmat, sc->objs[i].m->inv,
						sc->objs[i].m->tinv, NULL);
			if (sc->objs[i].surf->txtr)
				free_ptrs(sc->objs[i].surf->txtr->name, sc->objs[i].surf->txtr,
						NULL, NULL);
			if (sc->objs[i].surf->bmap)
				free_ptrs(sc->objs[i].surf->bmap->name, sc->objs[i].surf->bmap,
						NULL, NULL);
			free_ptrs(sc->objs[i].surf, sc->objs[i].m, sc->objs[i].aabb, NULL);
		}
		i++;
	}
	return (ret);
}

int		gr_free(t_obj *gr, int obj_size, int ret)
{
	int i;

	i = 0;
	while (i < obj_size)
	{
		if (gr->obj.gr.gr[i].type == GROUP)
			gr_free(&gr->obj.gr.gr[i], gr->obj.gr.gr[i].obj.gr.gsize, 1);
		free_ptrs(gr->obj.gr.gr[i].surf, gr->obj.gr.gr[i].m,
				gr->obj.gr.gr[i].aabb, NULL);
		i++;
	}
	free_ptrs(gr->m->tmat, gr->m->inv, gr->m->tinv, gr->m);
	if (gr->surf)
		free(gr->surf);
	free(gr->obj.gr.gr);
	return (ret);
}
