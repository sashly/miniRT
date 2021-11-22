/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_mat4_inv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 20:58:25 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 21:01:59 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lalgebra.h"
#include "rt_utils.h"

/*
** Cofactor expansion inverse matrix method:
*/

t_flt	mat44_minor(t_mat4 m, t_ivec3 r, t_ivec3 c)
{
	return (m->mat44[4 * r.x + c.x] * (m->mat44[4 * r.y + c.y] *
				m->mat44[4 * r.z + c.z] - m->mat44[4 * r.z + c.y] *
				m->mat44[4 * r.y + c.z]) - m->mat44[4 * r.x + c.y] *
			(m->mat44[4 * r.y + c.x] * m->mat44[4 * r.z + c.z] -
			m->mat44[4 * r.z + c.x] * m->mat44[4 * r.y + c.z]) +
			m->mat44[4 * r.x + c.z] * (m->mat44[4 * r.y + c.x] *
				m->mat44[4 * r.z + c.y] - m->mat44[4 * r.z + c.x] *
				m->mat44[4 * r.y + c.y]));
}

void	mat44_cofactors(t_mat4 m, t_mat4 cof)
{
	cof->mat44[0] = mat44_minor(m, givec3(1, 2, 3), givec3(1, 2, 3));
	cof->mat44[1] = -mat44_minor(m, givec3(0, 2, 3), givec3(1, 2, 3));
	cof->mat44[2] = mat44_minor(m, givec3(0, 1, 3), givec3(1, 2, 3));
	cof->mat44[3] = -mat44_minor(m, givec3(0, 1, 2), givec3(1, 2, 3));
	cof->mat44[4] = -mat44_minor(m, givec3(1, 2, 3), givec3(0, 2, 3));
	cof->mat44[5] = mat44_minor(m, givec3(0, 2, 3), givec3(0, 2, 3));
	cof->mat44[6] = -mat44_minor(m, givec3(0, 1, 3), givec3(0, 2, 3));
	cof->mat44[7] = mat44_minor(m, givec3(0, 1, 2), givec3(0, 2, 3));
	cof->mat44[8] = mat44_minor(m, givec3(1, 2, 3), givec3(0, 1, 3));
	cof->mat44[9] = -mat44_minor(m, givec3(0, 2, 3), givec3(0, 1, 3));
	cof->mat44[10] = mat44_minor(m, givec3(0, 1, 3), givec3(0, 1, 3));
	cof->mat44[11] = -mat44_minor(m, givec3(0, 1, 2), givec3(0, 1, 3));
	cof->mat44[12] = -mat44_minor(m, givec3(1, 2, 3), givec3(0, 1, 2));
	cof->mat44[13] = mat44_minor(m, givec3(0, 2, 3), givec3(0, 1, 2));
	cof->mat44[14] = -mat44_minor(m, givec3(0, 1, 3), givec3(0, 1, 2));
	cof->mat44[15] = mat44_minor(m, givec3(0, 1, 2), givec3(0, 1, 2));
}

t_flt	mat44_determinant(t_mat4 m)
{
	return (m->mat44[0] * mat44_minor(m, givec3(1, 2, 3), givec3(1, 2, 3)) -
			m->mat44[1] * mat44_minor(m, givec3(1, 2, 3), givec3(0, 2, 3)) +
			m->mat44[2] * mat44_minor(m, givec3(1, 2, 3), givec3(0, 1, 3)) -
			m->mat44[3] * mat44_minor(m, givec3(1, 2, 3), givec3(0, 1, 2)));
}

int		mat44_inverse(t_mat4 mat, t_mat4 inv)
{
	t_flt	det;
	t_flt	inv_det;

	det = mat44_determinant(mat);
	if (FLT_ISZERO(det))
		return (0);
	inv_det = 1. / det;
	mat44_cofactors(mat, inv);
	inv->mat44[0] = inv->mat44[0] * inv_det;
	inv->mat44[1] = inv->mat44[1] * inv_det;
	inv->mat44[2] = inv->mat44[2] * inv_det;
	inv->mat44[3] = inv->mat44[3] * inv_det;
	inv->mat44[4] = inv->mat44[4] * inv_det;
	inv->mat44[5] = inv->mat44[5] * inv_det;
	inv->mat44[6] = inv->mat44[6] * inv_det;
	inv->mat44[7] = inv->mat44[7] * inv_det;
	inv->mat44[8] = inv->mat44[8] * inv_det;
	inv->mat44[9] = inv->mat44[9] * inv_det;
	inv->mat44[10] = inv->mat44[10] * inv_det;
	inv->mat44[11] = inv->mat44[11] * inv_det;
	inv->mat44[12] = inv->mat44[12] * inv_det;
	inv->mat44[13] = inv->mat44[13] * inv_det;
	inv->mat44[14] = inv->mat44[14] * inv_det;
	inv->mat44[15] = inv->mat44[15] * inv_det;
	return (1);
}
