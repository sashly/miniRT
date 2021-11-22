/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_mat4_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 20:46:57 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 20:48:42 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lalgebra.h"
#include "rt_utils.h"

int		mat44_malloc3(t_mat4 *m1, t_mat4 *m2, t_mat4 *m3)
{
	if (!(*m1 = (t_matrix *)malloc(sizeof(t_matrix))))
		return (0);
	(*m1)->rows = 4;
	(*m1)->cols = 4;
	if (!(*m2 = (t_matrix *)malloc(sizeof(t_matrix))))
	{
		free(*m1);
		*m1 = NULL;
		return (0);
	}
	(*m2)->rows = 4;
	(*m2)->cols = 4;
	if (!(*m3 = (t_matrix *)malloc(sizeof(t_matrix))))
	{
		free(*m1);
		*m1 = NULL;
		free(*m2);
		*m2 = NULL;
		return (0);
	}
	(*m3)->rows = 4;
	(*m3)->cols = 4;
	return (1);
}

void	mat44_mult_mat44(t_mat4 m1, t_mat4 m2, t_mat4 out)
{
	int i;

	i = 0;
	while (i < 4)
	{
		out->mat44[i * 4 + 0] = m1->mat44[i * 4 + 0] * m2->mat44[0 * 4 + 0] +
								m1->mat44[i * 4 + 1] * m2->mat44[1 * 4 + 0] +
								m1->mat44[i * 4 + 2] * m2->mat44[2 * 4 + 0] +
								m1->mat44[i * 4 + 3] * m2->mat44[3 * 4 + 0];
		out->mat44[i * 4 + 1] = m1->mat44[i * 4 + 0] * m2->mat44[0 * 4 + 1] +
								m1->mat44[i * 4 + 1] * m2->mat44[1 * 4 + 1] +
								m1->mat44[i * 4 + 2] * m2->mat44[2 * 4 + 1] +
								m1->mat44[i * 4 + 3] * m2->mat44[3 * 4 + 1];
		out->mat44[i * 4 + 2] = m1->mat44[i * 4 + 0] * m2->mat44[0 * 4 + 2] +
								m1->mat44[i * 4 + 1] * m2->mat44[1 * 4 + 2] +
								m1->mat44[i * 4 + 2] * m2->mat44[2 * 4 + 2] +
								m1->mat44[i * 4 + 3] * m2->mat44[3 * 4 + 2];
		out->mat44[i * 4 + 3] = m1->mat44[i * 4 + 0] * m2->mat44[0 * 4 + 3] +
								m1->mat44[i * 4 + 1] * m2->mat44[1 * 4 + 3] +
								m1->mat44[i * 4 + 2] * m2->mat44[2 * 4 + 3] +
								m1->mat44[i * 4 + 3] * m2->mat44[3 * 4 + 3];
		i++;
	}
}

void	mat44_mult_tmat44(t_mat4 m1, t_mat4 m2_t, t_mat4 out)
{
	int i;

	i = 0;
	while (i < 4)
	{
		out->mat44[i * 4 + 0] = m1->mat44[i * 4 + 0] * m2_t->mat44[0 * 4 + 0] +
								m1->mat44[i * 4 + 1] * m2_t->mat44[0 * 4 + 1] +
								m1->mat44[i * 4 + 2] * m2_t->mat44[0 * 4 + 2] +
								m1->mat44[i * 4 + 3] * m2_t->mat44[0 * 4 + 3];
		out->mat44[i * 4 + 1] = m1->mat44[i * 4 + 0] * m2_t->mat44[1 * 4 + 0] +
								m1->mat44[i * 4 + 1] * m2_t->mat44[1 * 4 + 1] +
								m1->mat44[i * 4 + 2] * m2_t->mat44[1 * 4 + 2] +
								m1->mat44[i * 4 + 3] * m2_t->mat44[1 * 4 + 3];
		out->mat44[i * 4 + 2] = m1->mat44[i * 4 + 0] * m2_t->mat44[2 * 4 + 0] +
								m1->mat44[i * 4 + 1] * m2_t->mat44[2 * 4 + 1] +
								m1->mat44[i * 4 + 2] * m2_t->mat44[2 * 4 + 2] +
								m1->mat44[i * 4 + 3] * m2_t->mat44[2 * 4 + 3];
		out->mat44[i * 4 + 3] = m1->mat44[i * 4 + 0] * m2_t->mat44[3 * 4 + 0] +
								m1->mat44[i * 4 + 1] * m2_t->mat44[3 * 4 + 1] +
								m1->mat44[i * 4 + 2] * m2_t->mat44[3 * 4 + 2] +
								m1->mat44[i * 4 + 3] * m2_t->mat44[3 * 4 + 3];
		i++;
	}
}

void	mat44_mult_mat41(t_mat4 m, t_vec4 *v, t_vec4 *out)
{
	out->x = m->mat44[0] * v->x + m->mat44[1] * v->y + m->mat44[2] * v->z +
		m->mat44[3] * v->w;
	out->y = m->mat44[4] * v->x + m->mat44[5] * v->y + m->mat44[6] * v->z +
		m->mat44[7] * v->w;
	out->z = m->mat44[8] * v->x + m->mat44[9] * v->y + m->mat44[10] * v->z +
		m->mat44[11] * v->w;
	out->w = m->mat44[12] * v->x + m->mat44[13] * v->y + m->mat44[14] * v->z +
		m->mat44[15] * v->w;
}

void	mat44_mult_mat41_inplace(t_mat4 m, t_vec4 *v)
{
	t_vec4	tmp;

	tmp.x = m->mat44[0] * v->x + m->mat44[1] * v->y + m->mat44[2] * v->z +
			m->mat44[3] * v->w;
	tmp.y = m->mat44[4] * v->x + m->mat44[5] * v->y + m->mat44[6] * v->z +
			m->mat44[7] * v->w;
	tmp.z = m->mat44[8] * v->x + m->mat44[9] * v->y + m->mat44[10] * v->z +
			m->mat44[11] * v->w;
	tmp.w = m->mat44[12] * v->x + m->mat44[13] * v->y + m->mat44[14] * v->z +
			m->mat44[15] * v->w;
	v->x = tmp.x;
	v->y = tmp.y;
	v->z = tmp.z;
	v->w = tmp.w;
}
