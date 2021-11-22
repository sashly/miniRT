/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_camera_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 14:45:27 by sashly            #+#    #+#             */
/*   Updated: 2021/03/19 14:45:58 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	camera_rotate_onlmat(t_scene *sc, int xyz, int angle)
{
	t_camera	*cam;
	t_matrix	mult;
	t_matrix	rot;

	cam = &sc->cams[sc->pcam];
	if (xyz == 0)
		m44tf_rotate_x(angle, &rot);
	else if (xyz == 1)
		m44tf_rotate_y(angle, &rot);
	else if (xyz == 2)
		m44tf_rotate_z(angle, &rot);
	mat44_mult_mat44(cam->tmat, &rot, &mult);
	mat44_copy(cam->tmat, &mult);
	mat44_inverse(cam->tmat, cam->tmat_i);
}

void	camera_translate_onlmat(t_scene *sc, int xyz, t_flt step)
{
	t_camera	*cam;
	t_matrix	tran;
	t_matrix	mul;
	t_vec3		move;

	cam = &sc->cams[sc->pcam];
	if (xyz == 0)
		pgvec3(step, 0., 0., &move);
	else if (xyz == 1)
		pgvec3(0., step, 0., &move);
	else if (xyz == 2)
		pgvec3(0., 0., -step, &move);
	mat44_mult_mat31_inplace(cam->tmat, &move, 0);
	pvec3_addc(&cam->pos, move);
	m44tf_translation(&move, &tran);
	mat44_mult_mat44(&tran, cam->tmat, &mul);
	mat44_copy(cam->tmat, &mul);
	mat44_inverse(cam->tmat, cam->tmat_i);
}
