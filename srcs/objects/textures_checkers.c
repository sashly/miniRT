/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_checkers.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 23:01:48 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 23:04:09 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	checker3d_txtr_sine(t_obj *obj, t_hit_rec *hr, t_vec3 *outcol)
{
	t_flt	sine_f;
	t_flt	rand_eps;
	t_flt	cf;

	cf = 0.75;
	rand_eps = -0.00017328812;
	sine_f = sin(cf * (hr->p.x + rand_eps)) * sin(cf * (hr->p.y + rand_eps))
		* sin(cf * (hr->p.z + rand_eps));
	if (sine_f < 0.)
		*outcol = obj->surf->col;
	else
		*outcol = obj->surf->col1;
}

void	checker3d_txtr_floor(t_obj *obj, t_hit_rec *hr, t_vec3 *outcol)
{
	t_flt	rand_eps;
	t_flt	x;
	t_flt	y;
	t_flt	z;
	t_flt	size;

	size = obj->surf->cf1;
	rand_eps = -0.00017328812;
	x = hr->p.x + rand_eps;
	y = hr->p.y + rand_eps;
	z = hr->p.z + rand_eps;
	if (((int)floor(x / size) + (int)floor(y / size) +
				(int)floor(z / size)) % 2 == 0)
		*outcol = obj->surf->col;
	else
		*outcol = obj->surf->col1;
}

void	checker2d_sphere(t_obj *obj, t_hit_rec *hr, t_vec3 *outcol)
{
	t_flt	u;
	t_flt	v;
	t_flt	size_i;

	size_i = obj->surf->cf1 * 0.01;
	size_i = 1 / size_i;
	get_sphere_uv(hr, &u, &v);
	if (((int)floor(u * size_i) + (int)floor(v * size_i * 0.6)) % 2 == 0)
		*outcol = obj->surf->col;
	else
		*outcol = obj->surf->col1;
}

void	checker2d_outline_retcol(t_obj *obj, int *iuv, int in_outl, t_vec3 *col)
{
	if ((iuv[0] + iuv[1]) % 2 == 0)
	{
		if (!in_outl)
		{
			*col = obj->surf->col;
			return ;
		}
	}
	else
	{
		if (!in_outl)
		{
			*col = obj->surf->col1;
			return ;
		}
	}
	*col = obj->surf->col2;
}

void	checker2d_outline_sphere(t_obj *obj, t_hit_rec *hr, t_vec3 *outcol)
{
	t_flt	uv[2];
	t_flt	cf[4];
	int		iuv[2];
	int		in_outl;

	cf[0] = obj->surf->cf1 * 0.01;
	cf[1] = obj->surf->cf2 * 0.005 / cf[0];
	get_sphere_uv(hr, &uv[0], &uv[1]);
	iuv[0] = floor(uv[0] / cf[0]);
	iuv[1] = floor(uv[1] * 0.6 / cf[0]);
	cf[2] = uv[0] / cf[0] - iuv[0];
	cf[3] = uv[1] * 0.6 / cf[0] - iuv[1];
	in_outl = ((cf[2] < cf[1] || cf[2] > 1. - cf[1]) ||
			(cf[3] < cf[1] || cf[3] > 1. - cf[1]));
	checker2d_outline_retcol(obj, iuv, in_outl, outcol);
}
