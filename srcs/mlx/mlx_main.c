/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 21:58:23 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 21:59:01 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mlx.h"
#include "rt_parser.h"

int		ft_mlx_init_ptrs(t_scene *rt_sc, t_mlx_ptrs *p)
{
	p->win = NULL;
	p->wimg = NULL;
	p->pics = NULL;
	p->pics_size = 0;
	if (rt_sc->wres > R_MAX_WIDTH || rt_sc->hres > R_MAX_HEIGHT)
		ft_mlx_resolution_restrict(rt_sc);
	p->rt_sc = rt_sc;
	p->ppic = 0;
	if (!(p->wimg = (t_img *)malloc(sizeof(t_img))))
		return (0);
	if (!(ft_mlx_handle_pics(rt_sc, p)))
		return (0);
	p->pixels = (unsigned char *)malloc(sizeof(unsigned char)
			* p->rt_sc->wres * p->rt_sc->hres * 3);
	if (!p->pixels)
		return (0);
	return (1);
}

int		ft_mlx_handle_pics(t_scene *sc, t_mlx_ptrs *p)
{
	int i;

	i = 0;
	if (!p->pics_size && sc->conf.pics_to_load != 0)
	{
		p->pics = (t_img *)malloc(sizeof(t_img) * sc->conf.pics_to_load);
		if (!p->pics)
			return (0);
		p->pics_size = sc->conf.pics_to_load;
	}
	while (i < sc->obj_size)
	{
		if (sc->objs[i].surf->colmod_f == COLMOD_PTXTR)
			if (!ft_mlx_load_texture(sc, p, i, p->ppic))
				return (0);
		if (sc->objs[i].surf->normmod_f == NORMMOD_BUMP)
			if (!ft_mlx_load_bmap(sc, p, i, p->ppic))
				return (0);
		i++;
	}
	if (sc->back->mod == BG_SKYBOX)
		if (!ft_mlx_load_skybox(sc, p, p->ppic))
			return (0);
	return (1);
}

int		ft_mlx_get_wimg(t_mlx_ptrs *p)
{
	p->wimg->img = mlx_new_image(p->mlx, p->rt_sc->wres, p->rt_sc->hres);
	if (!p->wimg->img)
		return (0);
	p->wimg->addr = mlx_get_data_addr(p->wimg->img, &p->wimg->bpp,
			&p->wimg->line_len, &p->wimg->endian);
	if (!p->wimg->addr)
		return (0);
	p->wimg->img_w = p->rt_sc->wres;
	p->wimg->img_h = p->rt_sc->hres;
	return (1);
}

int		mlx_main(t_scene *rt_scene)
{
	t_mlx_ptrs p;

	p.mlx = mlx_init();
	if (!ft_mlx_init_ptrs(rt_scene, &p))
		return (free_mlx_ptrs(&p));
	p.win = mlx_new_window(p.mlx, p.rt_sc->wres, p.rt_sc->hres, "miniRT");
	rt_screen_driver(p.rt_sc, p.pixels);
	if (!ft_mlx_get_wimg(&p))
		return (free_mlx_ptrs(&p));
	ft_mlx_put_img_to_win(&p);
	mlx_hook(p.win, 2, 0, &hooks_mlx_main, &p);
	mlx_hook(p.win, 17, 0, &hmlx_red_cross, &p);
	mlx_loop(p.mlx);
	return (1);
}
