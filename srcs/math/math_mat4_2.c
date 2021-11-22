/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_mat4_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 20:49:28 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 20:50:27 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lalgebra.h"
#include "rt_utils.h"

void	mat44_mult_mat31_inplace(t_mat4 m, t_vec3 *v, int is_point)
{
	t_vec4	tmp;
	t_flt	w;

	w = (is_point) ? 1. : 0.;
	tmp.x = m->mat44[0] * v->x + m->mat44[1] * v->y + m->mat44[2] * v->z +
		m->mat44[3] * w;
	tmp.y = m->mat44[4] * v->x + m->mat44[5] * v->y + m->mat44[6] * v->z +
		m->mat44[7] * w;
	tmp.z = m->mat44[8] * v->x + m->mat44[9] * v->y + m->mat44[10] * v->z +
		m->mat44[11] * w;
	tmp.w = m->mat44[12] * v->x + m->mat44[13] * v->y + m->mat44[14] * v->z +
		m->mat44[15] * w;
	v->x = tmp.x;
	v->y = tmp.y;
	v->z = tmp.z;
}

void	mat44_transpose(t_mat4 in, t_mat4 out)
{
	out->mat44[0] = in->mat44[0];
	out->mat44[4] = in->mat44[1];
	out->mat44[8] = in->mat44[2];
	out->mat44[12] = in->mat44[3];
	out->mat44[1] = in->mat44[4];
	out->mat44[5] = in->mat44[5];
	out->mat44[9] = in->mat44[6];
	out->mat44[13] = in->mat44[7];
	out->mat44[2] = in->mat44[8];
	out->mat44[6] = in->mat44[9];
	out->mat44[10] = in->mat44[10];
	out->mat44[14] = in->mat44[11];
	out->mat44[3] = in->mat44[12];
	out->mat44[7] = in->mat44[13];
	out->mat44[11] = in->mat44[14];
	out->mat44[15] = in->mat44[15];
}

void	mat44_transpose_inplace(t_mat4 mat)
{
	SWAP_FLT(mat->mat44[1], mat->mat44[4]);
	SWAP_FLT(mat->mat44[2], mat->mat44[8]);
	SWAP_FLT(mat->mat44[3], mat->mat44[12]);
	SWAP_FLT(mat->mat44[6], mat->mat44[9]);
	SWAP_FLT(mat->mat44[7], mat->mat44[13]);
	SWAP_FLT(mat->mat44[11], mat->mat44[14]);
}
