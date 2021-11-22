/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disk.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 22:55:28 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 22:55:48 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		is_hit_disk(t_ray *ray, t_obj *ds, t_flt t_max, t_hit_rec *hr)
{
	t_vec3	point;
	t_vec3	vec;
	t_flt	tmp;

	if (hit_plane(ray, &ds->obj.ds.p, &ds->obj.ds.n, &tmp))
	{
		ray_point(ray, tmp, &point);
		pvec3_sub(&point, &ds->obj.ds.p, &vec);
		if (pvec3_dotr(&vec, &vec) > ds->obj.ds.rp2)
			return (0);
		if (tmp > RT_EPSILON && tmp < t_max)
		{
			hr->t = tmp;
			return (1);
		}
	}
	return (0);
}

void	disk_norm(t_obj *ds, t_hit_rec *hr, t_vec3 *norm)
{
	(void)hr;
	*norm = ds->obj.ds.n;
}
