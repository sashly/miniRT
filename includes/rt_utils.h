/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_utils.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 15:49:23 by sashly            #+#    #+#             */
/*   Updated: 2021/03/19 15:49:46 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_UTILS_H
# define RT_UTILS_H

# include <stdlib.h>

# include "lalgebra.h"

void	free_ptrs(void *ptr1, void *ptr2, void *ptr3, void *ptr4);
int		free_ptrs_ret(void *ptr1, void *ptr2, void *ptr3, int ret);
void	setnull_ptrs(void **ptr1, void **ptr2, void **ptr3, void **ptr4);
void	gvec3_col(int r, int g, int b, t_vec3 *col);

#endif
