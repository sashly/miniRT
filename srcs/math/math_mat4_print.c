/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_mat4_print.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 20:50:38 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 20:56:10 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lalgebra.h"
#include "rt_utils.h"

/*
** Print a 4x4 matrix:
*/

t_flt	ft_mat44_max(t_mat4 mat)
{
	t_flt		max;
	unsigned	i;
	unsigned	j;

	i = 0;
	max = mat->mat44[0];
	while (i < mat->rows)
	{
		j = 0;
		while (j < mat->cols)
		{
			if (fabs(mat->mat44[mat->cols * i + j]) > max)
				max = fabs(mat->mat44[mat->cols * i + j]);
			j++;
		}
		i++;
	}
	return (max);
}

int		mat44_is_negelem(t_mat4 mat)
{
	unsigned i;

	i = 0;
	while (i < mat->rows * mat->cols)
	{
		if (mat->mat44[i] < 0.f || mat->mat44[i] == -0.f)
			return (1);
		i++;
	}
	return (0);
}

int		float_intlen(t_flt num)
{
	int	intpart;
	int	intlen;

	intlen = (num < 1.0) ? 1 : 0;
	intpart = (int)num;
	while (intpart)
	{
		intpart /= 10;
		intlen++;
	}
	return (intlen);
}

void	mat44_print(t_mat4 mat, int fraclen)
{
	int			max_intlen;
	int			corr;
	unsigned	i;
	unsigned	j;

	i = 0;
	corr = mat44_is_negelem(mat);
	corr += (fraclen) ? 1 : 0;
	max_intlen = float_intlen(ft_mat44_max(mat));
	while (i < mat->rows)
	{
		j = 0;
		while (j < mat->cols)
		{
			if (!j)
				printf("|%*.*f|", max_intlen + fraclen + corr, fraclen,
						mat->mat44[i * mat->cols + j]);
			else
				printf("%*.*f|", max_intlen + fraclen + corr, fraclen,
						mat->mat44[i * mat->cols + j]);
			j++;
		}
		printf("\n");
		i++;
	}
}
