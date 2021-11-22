/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_objects_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 22:58:46 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 22:59:25 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		hit_return_helper(t_hit_rec *hr, t_flt t_min, t_flt t_max, t_flt tmp)
{
	if (tmp > t_min && tmp < t_max)
	{
		hr->t = tmp;
		return (1);
	}
	return (0);
}

void	get_objray(t_obj *obj, t_ray *wray, t_ray *oray)
{
	ray_copy(wray, oray);
	mat44_mult_mat31_inplace(obj->m->inv, &oray->orig, 1);
	mat44_mult_mat31_inplace(obj->m->inv, &oray->dir, 0);
}

void	norm_to_world(t_obj *obj, t_vec3 *norm)
{
	mat44_mult_mat31_inplace(obj->m->tinv, norm, 0);
	pvec3_unit(norm);
}

void	move_object(t_scene *sc, int xyz, t_flt step)
{
	t_obj		*obj;
	t_matrix	tran;
	t_matrix	mul;
	t_vec3		move;

	obj = &sc->objs[sc->pobj];
	if (xyz == 0)
		pgvec3(-step, 0., 0., &move);
	else if (xyz == 1)
		pgvec3(0., -step, 0., &move);
	else if (xyz == 2)
		pgvec3(0., 0., -step, &move);
	mat44_mult_mat31_inplace(obj->m->inv, &move, 0);
	m44tf_translation(&move, &tran);
	mat44_mult_mat44(&tran, obj->m->inv, &mul);
	mat44_copy(obj->m->inv, &mul);
	mat44_transpose(obj->m->inv, obj->m->tinv);
	mat44_inverse(obj->m->inv, obj->m->tmat);
}

void	rotate_object(t_scene *sc, int xyz, t_flt angle)
{
	t_obj		*obj;
	t_matrix	rot;
	t_matrix	mul;

	obj = &sc->objs[sc->pobj];
	if (xyz == 0)
		m44tf_rotate_x(angle, &rot);
	else if (xyz == 1)
		m44tf_rotate_y(angle, &rot);
	else if (xyz == 2)
		m44tf_rotate_z(angle, &rot);
	mat44_mult_mat44(obj->m->tmat, &rot, &mul);
	mat44_copy(obj->m->tmat, &mul);
	mat44_inverse(obj->m->tmat, obj->m->inv);
	mat44_transpose(obj->m->inv, obj->m->tinv);
}
