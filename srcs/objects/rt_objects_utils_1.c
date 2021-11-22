/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_objects_utils_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 22:59:34 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 23:00:20 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	move_object_local(t_scene *sc, int xyz, t_flt step)
{
	t_obj		*obj;
	t_matrix	tran;
	t_matrix	mul;
	t_vec3		move;

	obj = &sc->objs[sc->pobj];
	if (xyz == 0)
		pgvec3(step, 0., 0., &move);
	else if (xyz == 1)
		pgvec3(0., step, 0., &move);
	else if (xyz == 2)
		pgvec3(0., 0., step, &move);
	m44tf_translation(&move, &tran);
	mat44_mult_mat44(&tran, obj->m->inv, &mul);
	mat44_copy(obj->m->inv, &mul);
	mat44_transpose(obj->m->inv, obj->m->tinv);
	mat44_inverse(obj->m->inv, obj->m->tmat);
}

void	bgrt_to_vec3(char *bgrt, t_vec3 *out_col)
{
	out_col->z = (unsigned char)bgrt[0] / 255.;
	out_col->y = (unsigned char)bgrt[1] / 255.;
	out_col->x = (unsigned char)bgrt[2] / 255.;
	if (bgrt[3] != 0)
	{
		out_col->x = 1.;
		out_col->y = 1.;
		out_col->z = 1.;
	}
}
