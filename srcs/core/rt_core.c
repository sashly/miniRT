/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_core.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 14:46:15 by sashly            #+#    #+#             */
/*   Updated: 2021/03/19 14:47:51 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	rt_screen(t_scene *sc, int w0, int w1, unsigned char *pixels)
{
	t_vec3			col;
	int				i[2];
	unsigned char	*buf;

	i[0] = 0;
	while (i[0] < sc->hres)
	{
		i[1] = w0;
		while (i[1] < w1)
		{
			sc->f_sampler(sc, i, &buf, &col);
			rt_process_pixel(sc, &col, i, pixels);
			i[1]++;
		}
		i[0]++;
	}
}

void	rt_trace_ray(t_scene *sc, t_ray *ray, t_vec3 *out_col)
{
	t_hit_rec	hrec;
	t_flt		flip;
	int			hit_flag;

	hit_flag = rt_intersect(sc, ray, RT_HUGEVAL, &hrec);
	if (hit_flag)
	{
		flip = 0.;
		if (sc->objs[hrec.obj_id].type == CONE)
			flip = 0.1;
		ray_point(ray, hrec.t, &hrec.p);
		sc->objs[hrec.obj_id].norm_f(&sc->objs[hrec.obj_id], &hrec, &hrec.n);
		if (pvec3_dotr(&ray->dir, &hrec.n) > flip)
			pvec3_neg(&hrec.n);
		sc->f_shader(sc, ray, &hrec, out_col);
	}
	else
		rt_shade_backg(sc, ray, out_col);
}

int		rt_intersect(t_scene *sc, t_ray *ray, t_flt t_max, t_hit_rec *hr)
{
	int	hit_flag;
	int	i;

	i = 0;
	hit_flag = 0;
	while (i < sc->obj_size)
	{
		if (sc->objs[i].hit_f(ray, &sc->objs[i], t_max, hr))
		{
			hit_flag = 1;
			if (hr->t < t_max)
			{
				t_max = hr->t;
				hr->obj_id = i;
			}
		}
		i++;
	}
	return (hit_flag);
}
