/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   savebmp_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 14:56:01 by sashly            #+#    #+#             */
/*   Updated: 2021/03/19 14:56:46 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include "rt_parser.h"

int		save_bmp_main_close(t_scene *sc, unsigned char *pixels, int is_error)
{
	if (is_error)
		ft_putstr_fd("Error\nAn error occurred during the saving.\n", 1);
	else
		ft_putstr_fd("The image successfully saved!\n", 1);
	free_rt_scene(sc, 0);
	if (pixels)
		free(pixels);
	return (!is_error);
}

int		save_bmp_main(t_scene *sc)
{
	unsigned char	*pixels;

	pixels = (unsigned char *)malloc(sizeof(unsigned char) * sc->hres *
			sc->wres * 3);
	anti_mlx_check(sc);
	if (!pixels || !rt_screen_driver(sc, pixels))
		return (save_bmp_main_close(sc, pixels, 1));
	if (!save_bmp("out_000.bmp", pixels, sc->hres, sc->wres))
		return (save_bmp_main_close(sc, pixels, 1));
	return (save_bmp_main_close(sc, pixels, 0));
}

/*
**	the function to search and unset textures that supposed to be loaded by mlx;
*/

void	anti_mlx_unset_bump(t_obj *obj)
{
	free(obj->surf->bmap->name);
	free(obj->surf->bmap);
	obj->surf->bmap = NULL;
	obj->surf->normmod_f = NORMMOD_DEF;
	if (obj->type == SPHERE)
		obj->norm_f = &sphere_norm;
	else if (obj->type == SQUARE)
		obj->norm_f = &square_norm;
}

void	anti_mlx_check(t_scene *sc)
{
	int	i;

	i = 0;
	if (sc->back->mod == BG_SKYBOX)
	{
		free(sc->back->skybox->lookup.name);
		free(sc->back->skybox->sp.surf);
		free(sc->back->skybox);
		sc->back->skybox = NULL;
		sc->back->mod = BG_MONO;
	}
	while (i < sc->obj_size)
	{
		if (sc->objs[i].surf->colmod_f == COLMOD_PTXTR)
		{
			free(sc->objs[i].surf->txtr->name);
			free(sc->objs[i].surf->txtr);
			sc->objs[i].surf->txtr = NULL;
			sc->objs[i].surf->colmod_f = COLMOD_MONO;
		}
		if (sc->objs[i].surf->normmod_f == NORMMOD_BUMP)
			anti_mlx_unset_bump(&sc->objs[i]);
		i++;
	}
	sc->conf.pics_to_load = 0;
}
