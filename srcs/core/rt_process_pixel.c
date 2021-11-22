/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_process_pixel.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 14:48:48 by sashly            #+#    #+#             */
/*   Updated: 2021/03/19 14:49:05 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	rt_process_pixel(t_scene *sc, t_vec3 *col, int *i, unsigned char *pixs)
{
	sc->conf.f_tonemap(col);
	if (sc->conf.cfilt != CF_NONE)
		sc->conf.f_colfilt(col);
	if (sc->conf.gamma != 1.)
		pvec3_pow(col, 1. / sc->conf.gamma);
	pixs[(sc->wres * i[0] + i[1]) * 3 + 0] = 255 * col->x;
	pixs[(sc->wres * i[0] + i[1]) * 3 + 1] = 255 * col->y;
	pixs[(sc->wres * i[0] + i[1]) * 3 + 2] = 255 * col->z;
}

void	rt_tonemap_cap(t_vec3 *col)
{
	if (col->x > 1.)
		col->x = 1.;
	if (col->y > 1.)
		col->y = 1.;
	if (col->z > 1.)
		col->z = 1.;
}

void	rt_tonemap_clamp(t_vec3 *col)
{
	t_flt max;

	max = pvec3_max(col);
	if (max > 1.)
		pvec3_muln(col, 1. / max);
}
