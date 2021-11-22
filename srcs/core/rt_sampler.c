/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_sampler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 14:49:19 by sashly            #+#    #+#             */
/*   Updated: 2021/03/19 14:49:47 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	rt_sampler_naa(t_scene *sc, int *i, unsigned char **buf, t_vec3 *col)
{
	t_ray	prim_ray;
	t_flt	u;
	t_flt	v;

	(void)buf;
	u = (((t_flt)i[1] + 0.5) * sc->cams[sc->pcam].pix_size);
	v = (((t_flt)i[0] + 0.5) * sc->cams[sc->pcam].pix_size);
	sc->cams[sc->pcam].get_ray(&sc->cams[sc->pcam], u, v, &prim_ray);
	rt_trace_ray(sc, &prim_ray, col);
}

void	rt_sampler_aa_reg(t_scene *sc, int *i, unsigned char **buf, t_vec3 *col)
{
	t_ray	pr;
	t_vec3	col_buf;
	t_flt	uv[2];
	t_flt	pq[2];
	t_flt	st;

	(void)buf;
	pgvec3(0., 0., 0., col);
	st = 1. / (double)sc->conf.aalias;
	pq[0] = 0.;
	while (pq[0] < 1. - RT_EPSILON)
	{
		pq[1] = 0.;
		while (pq[1] < 1. - RT_EPSILON)
		{
			uv[0] = ((i[1] + pq[1] + st * 0.5) * sc->cams[sc->pcam].pix_size);
			uv[1] = ((i[0] + pq[0] + st * 0.5) * sc->cams[sc->pcam].pix_size);
			sc->cams[sc->pcam].get_ray(&sc->cams[sc->pcam], uv[0], uv[1], &pr);
			rt_trace_ray(sc, &pr, &col_buf);
			pvec3_addc(col, col_buf);
			pq[1] += st;
		}
		pq[0] += st;
	}
	pvec3_muln(col, 1. / (sc->conf.aalias * sc->conf.aalias));
}
