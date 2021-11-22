/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_mat4tf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 20:56:30 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 20:57:00 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lalgebra.h"
#include "rt_utils.h"

/*
** Transformation matrices:
*/

void	m44tf_transition(t_nbasis *nbasis, t_vec3 *e, t_mat4 out)
{
	out->mat44[0] = nbasis->u.x;
	out->mat44[1] = nbasis->v.x;
	out->mat44[2] = nbasis->w.x;
	out->mat44[3] = e->x;
	out->mat44[4] = nbasis->u.y;
	out->mat44[5] = nbasis->v.y;
	out->mat44[6] = nbasis->w.y;
	out->mat44[7] = e->y;
	out->mat44[8] = nbasis->u.z;
	out->mat44[9] = nbasis->v.z;
	out->mat44[10] = nbasis->w.z;
	out->mat44[11] = e->z;
	out->mat44[12] = 0;
	out->mat44[13] = 0;
	out->mat44[14] = 0;
	out->mat44[15] = 1;
}

void	m44tf_transition_inv(t_nbasis *nbasis, t_vec3 *e, t_mat4 out)
{
	out->mat44[0] = nbasis->u.x;
	out->mat44[1] = nbasis->u.y;
	out->mat44[2] = nbasis->u.z;
	out->mat44[3] = e->x;
	out->mat44[4] = nbasis->v.x;
	out->mat44[5] = nbasis->v.y;
	out->mat44[6] = nbasis->v.z;
	out->mat44[7] = e->y;
	out->mat44[8] = nbasis->w.x;
	out->mat44[9] = nbasis->w.y;
	out->mat44[10] = nbasis->w.z;
	out->mat44[11] = e->z;
	out->mat44[12] = 0;
	out->mat44[13] = 0;
	out->mat44[14] = 0;
	out->mat44[15] = 1;
}

void	m44tf_translation(t_vec3 *point, t_mat4 out)
{
	out->mat44[0] = 1;
	out->mat44[1] = 0;
	out->mat44[2] = 0;
	out->mat44[3] = point->x;
	out->mat44[4] = 0;
	out->mat44[5] = 1;
	out->mat44[6] = 0;
	out->mat44[7] = point->y;
	out->mat44[8] = 0;
	out->mat44[9] = 0;
	out->mat44[10] = 1;
	out->mat44[11] = point->z;
	out->mat44[12] = 0;
	out->mat44[13] = 0;
	out->mat44[14] = 0;
	out->mat44[15] = 1;
}

void	m44tf_translation_m(t_vec3 point, t_mat4 out)
{
	out->mat44[0] = 1;
	out->mat44[1] = 0;
	out->mat44[2] = 0;
	out->mat44[3] = point.x;
	out->mat44[4] = 0;
	out->mat44[5] = 1;
	out->mat44[6] = 0;
	out->mat44[7] = point.y;
	out->mat44[8] = 0;
	out->mat44[9] = 0;
	out->mat44[10] = 1;
	out->mat44[11] = point.z;
	out->mat44[12] = 0;
	out->mat44[13] = 0;
	out->mat44[14] = 0;
	out->mat44[15] = 1;
}

void	m44tf_scaling(t_vec3 scale, t_mat4 out)
{
	out->mat44[0] = scale.x;
	out->mat44[1] = 0;
	out->mat44[2] = 0;
	out->mat44[3] = 0;
	out->mat44[4] = 0;
	out->mat44[5] = scale.y;
	out->mat44[6] = 0;
	out->mat44[7] = 0;
	out->mat44[8] = 0;
	out->mat44[9] = 0;
	out->mat44[10] = scale.z;
	out->mat44[11] = 0;
	out->mat44[12] = 0;
	out->mat44[13] = 0;
	out->mat44[14] = 0;
	out->mat44[15] = 1;
}
