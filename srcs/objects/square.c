/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 23:01:12 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 23:01:35 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		is_hit_square(t_ray *ray, t_obj *sq, t_flt t_max, t_hit_rec *hr)
{
	t_nbasis	nb;
	t_vec3		lvec;
	t_vec3		p;
	t_flt		uv[2];
	t_flt		tmp;

	if (hit_plane(ray, &sq->obj.sq.p, &sq->obj.sq.n, &tmp))
	{
		ray_point(ray, tmp, &p);
		pvec3_sub(&p, &sq->obj.sq.p, &lvec);
		gnbasis_norm(&sq->obj.sq.n, gvec3(1., 0., 0.), gvec3(0., 1., 0.), &nb);
		uv[0] = pvec3_dotr(&lvec, &nb.u);
		if (uv[0] < -sq->obj.sq.sd2 - 1e-5 || uv[0] > sq->obj.sq.sd2 + 1e-5)
			return (0);
		uv[1] = pvec3_dotr(&lvec, &nb.w);
		if (uv[1] < -sq->obj.sq.sd2 - 1e-5 || uv[1] > sq->obj.sq.sd2 + 1e-5)
			return (0);
		return (hit_return_helper(hr, RT_EPSILON, t_max, tmp));
	}
	return (0);
}

void	square_norm(t_obj *sq, t_hit_rec *hr, t_vec3 *norm)
{
	(void)hr;
	*norm = sq->obj.sq.n;
}
