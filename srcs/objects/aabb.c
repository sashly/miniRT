/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 22:46:28 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 22:47:38 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	check_axis(t_flt ray_orig, t_flt ray_dir, t_vec2 *t)
{
	t_flt tmin_num;
	t_flt tmax_num;

	tmin_num = -1 - ray_orig;
	tmax_num = 1 - ray_orig;
	t->min = tmin_num / ray_dir;
	t->max = tmax_num / ray_dir;
	if (t->min > t->max)
		ft_swapf(&t->min, &t->max);
}

t_flt	maxf3(t_flt a, t_flt b, t_flt c)
{
	if (a > b)
		return ((a > c) ? a : c);
	return ((b > c) ? b : c);
}

t_flt	minf3(t_flt a, t_flt b, t_flt c)
{
	if (a < b)
		return ((a < c) ? a : c);
	return ((b < c) ? b : c);
}

void	aabb_local_norm(t_vec3 *point, t_vec3 *norm)
{
	t_flt	maxc;

	maxc = maxf3(fabs(point->x), fabs(point->y), fabs(point->z));
	if (maxc - fabs(point->x) <= RT_EPSILON)
		pgvec3(point->x, 0., 0., norm);
	else if (maxc - fabs(point->y) <= RT_EPSILON)
		pgvec3(0., point->y, 0., norm);
	else
		pgvec3(0., 0., point->z, norm);
}

int		is_hit_aabb(t_ray *ray, t_obj *ab, t_flt t_max, t_hit_rec *hr)
{
	t_ray	oray;
	t_vec2	at[3];
	t_flt	tmin;
	t_flt	tmax;

	get_objray(ab, ray, &oray);
	check_axis(oray.orig.x, oray.dir.x, &at[0]);
	check_axis(oray.orig.y, oray.dir.y, &at[1]);
	check_axis(oray.orig.z, oray.dir.z, &at[2]);
	tmin = maxf3(at[0].min, at[1].min, at[2].min);
	tmax = minf3(at[0].max, at[1].max, at[2].max);
	if (tmin < tmax && (tmin > RT_EPSILON && tmin < t_max))
	{
		hr->t = tmin;
		ray_point(&oray, tmin, &hr->p);
		aabb_local_norm(&hr->p, &hr->n);
		norm_to_world(ab, &hr->n);
		return (1);
	}
	return (0);
}
