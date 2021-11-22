/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 23:07:08 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 23:07:38 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		is_hit_triangle(t_ray *ray, t_obj *tr, t_flt t_max, t_hit_rec *hr)
{
	t_vec3	vcs[3];
	t_flt	det;
	t_flt	uv[2];
	t_flt	tmp;

	pvec3_cross(&ray->dir, &tr->obj.tr.e2, &vcs[0]);
	det = pvec3_dotr(&tr->obj.tr.e1, &vcs[0]);
	if (det > -RT_EPSILON && det < RT_EPSILON)
		return (0);
	det = 1. / det;
	pvec3_sub(&ray->orig, &tr->obj.tr.p1, &vcs[1]);
	uv[0] = det * pvec3_dotr(&vcs[1], &vcs[0]);
	if (uv[0] <= -RT_EPSILON || uv[0] >= 1. + RT_EPSILON)
		return (0);
	pvec3_cross(&vcs[1], &tr->obj.tr.e1, &vcs[2]);
	uv[1] = det * pvec3_dotr(&ray->dir, &vcs[2]);
	if (uv[1] <= -RT_EPSILON || (uv[0] + uv[1]) >= 1. + RT_EPSILON)
		return (0);
	tmp = det * pvec3_dotr(&tr->obj.tr.e2, &vcs[2]);
	return (hit_return_helper(hr, RT_EPSILON, t_max, tmp));
}

void	triangle_norm(t_obj *tr, t_hit_rec *hr, t_vec3 *norm)
{
	(void)hr;
	*norm = tr->obj.tr.n;
}
