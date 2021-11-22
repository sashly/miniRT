/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_mat4tf_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 20:57:15 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 20:57:39 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lalgebra.h"
#include "rt_utils.h"

void	m44tf_rotate_x(t_flt angle, t_mat4 out)
{
	angle *= RT_PID180;
	out->mat44[0] = 1;
	out->mat44[1] = 0;
	out->mat44[2] = 0;
	out->mat44[3] = 0;
	out->mat44[4] = 0;
	out->mat44[5] = cos(angle);
	out->mat44[6] = (-1.) * sin(angle);
	out->mat44[7] = 0;
	out->mat44[8] = 0;
	out->mat44[9] = sin(angle);
	out->mat44[10] = cos(angle);
	out->mat44[11] = 0;
	out->mat44[12] = 0;
	out->mat44[13] = 0;
	out->mat44[14] = 0;
	out->mat44[15] = 1;
}

void	m44tf_rotate_y(t_flt angle, t_mat4 out)
{
	angle *= RT_PID180;
	out->mat44[0] = cos(angle);
	out->mat44[1] = 0;
	out->mat44[2] = sin(angle);
	out->mat44[3] = 0;
	out->mat44[4] = 0;
	out->mat44[5] = 1;
	out->mat44[6] = 0;
	out->mat44[7] = 0;
	out->mat44[8] = (-1.) * sin(angle);
	out->mat44[9] = 0;
	out->mat44[10] = cos(angle);
	out->mat44[11] = 0;
	out->mat44[12] = 0;
	out->mat44[13] = 0;
	out->mat44[14] = 0;
	out->mat44[15] = 1;
}

void	m44tf_rotate_z(t_flt angle, t_mat4 out)
{
	angle *= RT_PID180;
	out->mat44[0] = cos(angle);
	out->mat44[1] = (-1.) * sin(angle);
	out->mat44[2] = 0;
	out->mat44[3] = 0;
	out->mat44[4] = sin(angle);
	out->mat44[5] = cos(angle);
	out->mat44[6] = 0;
	out->mat44[7] = 0;
	out->mat44[8] = 0;
	out->mat44[9] = 0;
	out->mat44[10] = 1;
	out->mat44[11] = 0;
	out->mat44[12] = 0;
	out->mat44[13] = 0;
	out->mat44[14] = 0;
	out->mat44[15] = 1;
}

int		m44tf_rotate_xyz(t_flt a, t_flt b, t_flt g, t_mat4 out)
{
	t_matrix	rot;
	t_matrix	mult;

	m44tf_rotate_x(a, &rot);
	m44tf_rotate_y(b, out);
	mat44_mult_mat44(&rot, out, &mult);
	m44tf_rotate_z(g, &rot);
	mat44_mult_mat44(&mult, &rot, out);
	return (1);
}
