/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_mat4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 20:45:57 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 20:46:44 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lalgebra.h"
#include "rt_utils.h"

int		mat44_create(t_mat4 *new_mat)
{
	if (!(*new_mat = (t_matrix *)malloc(sizeof(t_matrix))))
		return (0);
	(*new_mat)->rows = 4;
	(*new_mat)->cols = 4;
	return (1);
}

int		mat44_ident_create(t_mat4 *ident)
{
	if (!mat44_create(ident))
		return (0);
	(*ident)->mat44[0] = 1;
	(*ident)->mat44[1] = 0;
	(*ident)->mat44[2] = 0;
	(*ident)->mat44[3] = 0;
	(*ident)->mat44[4] = 0;
	(*ident)->mat44[5] = 1;
	(*ident)->mat44[6] = 0;
	(*ident)->mat44[7] = 0;
	(*ident)->mat44[8] = 0;
	(*ident)->mat44[9] = 0;
	(*ident)->mat44[10] = 1;
	(*ident)->mat44[11] = 0;
	(*ident)->mat44[12] = 0;
	(*ident)->mat44[13] = 0;
	(*ident)->mat44[14] = 0;
	(*ident)->mat44[15] = 1;
	return (1);
}

void	mat44_ident_fill(t_mat4 ident)
{
	ident->mat44[0] = 1;
	ident->mat44[1] = 0;
	ident->mat44[2] = 0;
	ident->mat44[3] = 0;
	ident->mat44[4] = 0;
	ident->mat44[5] = 1;
	ident->mat44[6] = 0;
	ident->mat44[7] = 0;
	ident->mat44[8] = 0;
	ident->mat44[9] = 0;
	ident->mat44[10] = 1;
	ident->mat44[11] = 0;
	ident->mat44[12] = 0;
	ident->mat44[13] = 0;
	ident->mat44[14] = 0;
	ident->mat44[15] = 1;
}

void	mat44_copy(t_mat4 a, t_mat4 tocopy)
{
	a->mat44[0] = tocopy->mat44[0];
	a->mat44[1] = tocopy->mat44[1];
	a->mat44[2] = tocopy->mat44[2];
	a->mat44[3] = tocopy->mat44[3];
	a->mat44[4] = tocopy->mat44[4];
	a->mat44[5] = tocopy->mat44[5];
	a->mat44[6] = tocopy->mat44[6];
	a->mat44[7] = tocopy->mat44[7];
	a->mat44[8] = tocopy->mat44[8];
	a->mat44[9] = tocopy->mat44[9];
	a->mat44[10] = tocopy->mat44[10];
	a->mat44[11] = tocopy->mat44[11];
	a->mat44[12] = tocopy->mat44[12];
	a->mat44[13] = tocopy->mat44[13];
	a->mat44[14] = tocopy->mat44[14];
	a->mat44[15] = tocopy->mat44[15];
}

int		mat44_malloc2(t_mat4 *m1, t_mat4 *m2)
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
	return (1);
}
