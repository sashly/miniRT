/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 21:20:21 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 21:22:09 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_utils.h"

void	free_ptrs(void *ptr1, void *ptr2, void *ptr3, void *ptr4)
{
	if (ptr1)
		free(ptr1);
	if (ptr2)
		free(ptr2);
	if (ptr3)
		free(ptr3);
	if (ptr4)
		free(ptr4);
}

int		free_ptrs_ret(void *ptr1, void *ptr2, void *ptr3, int ret)
{
	if (ptr1)
		free(ptr1);
	if (ptr2)
		free(ptr2);
	if (ptr3)
		free(ptr3);
	return (ret);
}

void	setnull_ptrs(void **ptr1, void **ptr2, void **ptr3, void **ptr4)
{
	if (ptr1 && *ptr1)
		*ptr1 = NULL;
	if (ptr2 && *ptr2)
		*ptr2 = NULL;
	if (ptr3 && *ptr3)
		*ptr3 = NULL;
	if (ptr4 && *ptr4)
		*ptr4 = NULL;
}

void	gvec3_col(int r, int g, int b, t_vec3 *col)
{
	col->x = r / 255.1;
	col->y = g / 255.1;
	col->z = b / 255.1;
}
