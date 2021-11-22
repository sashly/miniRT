/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 20:23:48 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 20:25:16 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_ray	gray(t_vec3 orig, t_vec3 dir)
{
	t_ray ray;

	ray.orig = orig;
	ray.dir = dir;
	pvec3_unit(&ray.dir);
	return (ray);
}

void	pgray(t_vec3 *orig, t_vec3 *dir, t_ray *outray)
{
	outray->orig = *orig;
	outray->dir = *dir;
	pvec3_unit(&outray->dir);
}

void	ray_point(t_ray *ray, t_flt t, t_vec3 *point)
{
	point->x = ray->orig.x + t * ray->dir.x;
	point->y = ray->orig.y + t * ray->dir.y;
	point->z = ray->orig.z + t * ray->dir.z;
}

void	ray_copy(t_ray *orig, t_ray *copy)
{
	copy->orig = orig->orig;
	copy->dir = orig->dir;
}
