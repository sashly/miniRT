/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_filter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 21:27:24 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 21:28:38 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	colfilt_grayscale(t_vec3 *col)
{
	t_flt	avrg;

	avrg = (col->x + col->y + col->z) / 3.;
	col->x = avrg;
	col->y = avrg;
	col->z = avrg;
}

void	colfilt_sepia(t_vec3 *c)
{
	t_vec3 sepia;

	sepia.x = .393 * c->x + .769 * c->y + .189 * c->z;
	sepia.y = .349 * c->x + .686 * c->y + .168 * c->z;
	sepia.z = .272 * c->x + .534 * c->y + .131 * c->z;
	pvec3_cap(&sepia, 1.);
	pgvec3(sepia.x, sepia.y, sepia.z, c);
}

void	colfilt_red(t_vec3 *col)
{
	col->y = 0.;
	col->z = 0.;
}

void	colfilt_green(t_vec3 *col)
{
	col->x = 0.;
	col->z = 0.;
}

void	colfilt_blue(t_vec3 *col)
{
	col->x = 0.;
	col->y = 0.;
}
