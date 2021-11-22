/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 21:59:40 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 22:02:14 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mlx.h"

int		hooks_screenshot(t_mlx_ptrs *p)
{
	static char	name[18];

	if (!name[0])
		ft_strlcpy(name, "screenshot000.bmp", 18);
	else
	{
		if (name[12] != '9')
			name[12] += 1;
		else
		{
			name[12] = '0';
			if (name[11] != '9')
				name[11] += 1;
			else
			{
				name[11] = '0';
				name[10] += 1;
			}
		}
	}
	if (!save_bmp(name, p->pixels, p->rt_sc->hres, p->rt_sc->wres))
		return (0);
	ft_putstr3("Screenshot '", name, "' saved.\n");
	return (1);
}

int		hooks_normalmap(t_mlx_ptrs *p)
{
	if (p->rt_sc->conf.nmap == 0)
	{
		p->rt_sc->conf.nmap = 1;
		p->rt_sc->f_shader = &rt_shade_nmap;
	}
	else
	{
		p->rt_sc->conf.nmap = 0;
		p->rt_sc->f_shader = &rt_shade_phong;
	}
	if (!rt_screen_driver(p->rt_sc, p->pixels))
		return (0);
	ft_mlx_put_img_to_win(p);
	return (1);
}

void	hooks_colfilters_rgb(t_mlx_ptrs *p)
{
	if (p->rt_sc->conf.cfilt != CF_RED && p->rt_sc->conf.cfilt != CF_GREEN)
	{
		p->rt_sc->conf.cfilt = CF_RED;
		p->rt_sc->conf.f_colfilt = &colfilt_red;
	}
	else
	{
		if (p->rt_sc->conf.cfilt == CF_RED && p->rt_sc->conf.cfilt++)
			p->rt_sc->conf.f_colfilt = &colfilt_green;
		else if (p->rt_sc->conf.cfilt == CF_GREEN && p->rt_sc->conf.cfilt++)
			p->rt_sc->conf.f_colfilt = &colfilt_blue;
	}
}

int		hooks_colfilters(int keycode, t_mlx_ptrs *p)
{
	if (keycode == HOOK_2_CF_OFF)
	{
		if (p->rt_sc->conf.cfilt == CF_NONE)
			return (1);
		p->rt_sc->conf.cfilt = CF_NONE;
	}
	else if (keycode == HOOK_3_CF_GRAY)
	{
		p->rt_sc->conf.cfilt = CF_GRAY;
		p->rt_sc->conf.f_colfilt = &colfilt_grayscale;
	}
	else if (keycode == HOOK_4_CF_SEPIA)
	{
		p->rt_sc->conf.cfilt = CF_SEPIA;
		p->rt_sc->conf.f_colfilt = &colfilt_sepia;
	}
	else
		hooks_colfilters_rgb(p);
	if (!rt_screen_driver(p->rt_sc, p->pixels))
		return (0);
	ft_mlx_put_img_to_win(p);
	return (1);
}
