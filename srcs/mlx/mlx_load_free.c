/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_load_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 21:55:01 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 21:58:08 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mlx.h"
#include "rt_parser.h"

void	free_mlx_images(t_mlx_ptrs *p)
{
	int i;

	if (p->wimg)
	{
		mlx_destroy_image(p->mlx, p->wimg->img);
		free(p->wimg);
	}
	if (p->pics_size)
	{
		i = 0;
		while (i < p->pics_size)
			mlx_destroy_image(p->mlx, p->pics[i++].img);
		free(p->pics);
	}
}

int		free_mlx_ptrs(t_mlx_ptrs *p)
{
	free_rt_scene(p->rt_sc, 1);
	if (p->wimg || p->pics)
		free_mlx_images(p);
	if (p->pixels)
		free(p->pixels);
	if (p->win)
		mlx_destroy_window(p->mlx, p->win);
	exit(EXIT_SUCCESS);
	return (1);
}

int		ft_mlx_load_texture(t_scene *sc, t_mlx_ptrs *p, int i, int k)
{
	p->pics[k].img = mlx_xpm_file_to_image(p->mlx,
			sc->objs[i].surf->txtr->name, &p->pics[k].img_w, &p->pics[k].img_h);
	if (!p->pics[k].img)
		return (0);
	p->pics[k].addr = mlx_get_data_addr(p->pics[k].img, &p->pics[k].bpp,
			&p->pics[k].line_len, &p->pics[k].endian);
	sc->objs[i].surf->txtr->arr = p->pics[k].addr;
	if (!sc->objs[i].surf->txtr->arr)
		return (0);
	sc->objs[i].surf->txtr->w = p->pics[k].img_w;
	sc->objs[i].surf->txtr->h = p->pics[k].img_h;
	p->ppic++;
	return (1);
}

int		ft_mlx_load_bmap(t_scene *sc, t_mlx_ptrs *p, int i, int k)
{
	p->pics[k].img = mlx_xpm_file_to_image(p->mlx,
			sc->objs[i].surf->bmap->name, &p->pics[k].img_w, &p->pics[k].img_h);
	if (!p->pics[k].img)
		return (0);
	p->pics[k].addr = mlx_get_data_addr(p->pics[k].img, &p->pics[k].bpp,
			&p->pics[k].line_len, &p->pics[k].endian);
	sc->objs[i].surf->bmap->arr = p->pics[k].addr;
	if (!sc->objs[i].surf->bmap->arr)
		return (0);
	sc->objs[i].surf->bmap->w = p->pics[k].img_w;
	sc->objs[i].surf->bmap->h = p->pics[k].img_h;
	p->ppic++;
	return (1);
}

int		ft_mlx_load_skybox(t_scene *sc, t_mlx_ptrs *p, int k)
{
	p->pics[k].img = mlx_xpm_file_to_image(p->mlx,
			sc->back->skybox->lookup.name,
			&p->pics[k].img_w, &p->pics[k].img_h);
	if (!p->pics[k].img)
		return (0);
	p->pics[k].addr = mlx_get_data_addr(p->pics[k].img, &p->pics[k].bpp,
			&p->pics[k].line_len, &p->pics[k].endian);
	sc->back->skybox->lookup.arr = p->pics[k].addr;
	if (!sc->back->skybox->lookup.arr)
		return (0);
	sc->back->skybox->lookup.w = p->pics[k].img_w;
	sc->back->skybox->lookup.h = p->pics[k].img_h;
	p->ppic++;
	return (1);
}
