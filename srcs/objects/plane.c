/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 22:58:16 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 22:58:32 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		is_hit_plane(t_ray *ray, t_obj *pl, t_flt t_max, t_hit_rec *hr)
{
	t_flt denom;
	t_flt tmp;

	denom = pvec3_dotr(&pl->obj.pl.n, &ray->dir);
	if (!(denom > -RT_EPSILON && denom < RT_EPSILON))
	{
		tmp = pvec3_dotsub(&pl->obj.pl.p, &ray->orig, &pl->obj.pl.n);
		tmp /= denom;
		if (tmp > RT_EPSILON && tmp < t_max)
		{
			hr->t = tmp;
			return (1);
		}
	}
	return (0);
}

void	plane_norm(t_obj *pl, t_hit_rec *hr, t_vec3 *norm)
{
	(void)hr;
	*norm = pl->obj.pl.n;
}

int		hit_plane(t_ray *ray, t_vec3 *p, t_vec3 *n, t_flt *t)
{
	t_flt denom;
	t_flt tmp;

	denom = pvec3_dotr(n, &ray->dir);
	if (!(denom > -RT_EPSILON && denom < RT_EPSILON))
	{
		tmp = pvec3_dotsub(p, &ray->orig, n);
		tmp /= denom;
		if (tmp > RT_EPSILON)
		{
			*t = tmp;
			return (1);
		}
	}
	return (0);
}
