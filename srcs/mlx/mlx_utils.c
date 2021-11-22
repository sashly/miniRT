/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 21:54:11 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 21:54:50 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mlx.h"

int		get_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	ft_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;

	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	ft_mlx_put_img_to_win(t_mlx_ptrs *p)
{
	int	color;
	int i;

	i = 0;
	while (i < p->wimg->img_w * p->wimg->img_h * 3)
	{
		color = get_trgb(0, (int)p->pixels[i], (int)p->pixels[i + 1],
				(int)p->pixels[i + 2]);
		ft_mlx_pixel_put(p->wimg, ((i / 3) % p->wimg->img_w),
			p->wimg->img_h - 1 - ((i / 3) / p->wimg->img_w), color);
		i += 3;
	}
	mlx_put_image_to_window(p->mlx, p->win, p->wimg->img, 0, 0);
}

void	ft_mlx_resolution_restrict(t_scene *rt_sc)
{
	if (rt_sc->wres > R_MAX_WIDTH)
		rt_sc->wres = R_MAX_WIDTH;
	if (rt_sc->hres > R_MAX_HEIGHT)
		rt_sc->hres = R_MAX_HEIGHT;
	rt_sc->cams[rt_sc->pcam].constr(&rt_sc->cams[rt_sc->pcam], rt_sc->wres,
									rt_sc->hres);
}
