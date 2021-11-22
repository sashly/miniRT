/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_objs_py_constr.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 13:32:51 by sashly            #+#    #+#             */
/*   Updated: 2021/03/19 13:33:42 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser.h"

void	py_raw_set_color(t_vec3 *raw, t_vec3 *color)
{
	raw[2] = *color;
	raw[6] = *color;
	raw[10] = *color;
	raw[14] = *color;
	raw[18] = *color;
}

void	py_raw_set_points(t_vec3 *pts, t_vec3 *v3, t_vec3 *raw)
{
	raw[0] = v3[0];
	raw[1] = v3[1];
	pvec3_neg(&raw[1]);
	raw[3] = pts[0];
	raw[4] = pts[1];
	raw[5] = pts[4];
	raw[7] = pts[1];
	raw[8] = pts[2];
	raw[9] = pts[4];
	raw[11] = pts[2];
	raw[12] = pts[3];
	raw[13] = pts[4];
	raw[15] = pts[3];
	raw[16] = pts[0];
	raw[17] = pts[4];
}

void	py_comp_points(t_vec3 *v3, float *f, t_vec3 *pts)
{
	t_nbasis	nb;
	t_vec3		help[4];

	gnbasis_norm(&v3[1], gvec3(1., 0., 0.), gvec3(0., 1., 0.), &nb);
	pvec3_mulnr(&nb.w, f[0] / 2, &help[0]);
	pvec3_mulnr(&nb.u, f[0] / 2, &help[1]);
	help[2] = vec3_neg(help[0]);
	help[3] = vec3_neg(help[1]);
	pvec3_add3(&v3[0], &help[0], &help[1], &pts[0]);
	pvec3_add3(&v3[0], &help[2], &help[1], &pts[1]);
	pvec3_add3(&v3[0], &help[2], &help[3], &pts[2]);
	pvec3_add3(&v3[0], &help[0], &help[3], &pts[3]);
	pvec3_addcomb(&v3[0], f[1], &v3[1], &pts[4]);
}

int		pyramid_construct(t_vec3 *v3, float *f, t_obj *py)
{
	t_vec3		pts[5];
	t_vec3		raw[19];

	if (!gr_memalloc(py, 5))
		return (ERR_MEMALLOC);
	py->type = GROUP;
	py->obj.gr.gsize = 5;
	py_raw_set_color(raw, &v3[2]);
	py_comp_points(v3, f, pts);
	handle_norm(&v3[1]);
	py_raw_set_points(pts, v3, raw);
	set_square(v3, f[0], &py->obj.gr.gr[0]);
	set_triangle(&raw[3], &py->obj.gr.gr[1]);
	set_triangle(&raw[7], &py->obj.gr.gr[2]);
	set_triangle(&raw[11], &py->obj.gr.gr[3]);
	set_triangle(&raw[15], &py->obj.gr.gr[4]);
	group_tmat_build(py);
	py->hit_f = &is_hit_group;
	py->norm_f = &group_norm;
	return (1);
}
