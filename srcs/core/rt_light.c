/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_light.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 14:48:05 by sashly            #+#    #+#             */
/*   Updated: 2021/03/19 14:48:17 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	get_l_pointlight(t_light *light, t_vec3 *point, t_vec3 *l)
{
	pvec3_unitsub(&light->pos, point, l);
}

void	get_l_directional(t_light *light, t_vec3 *point, t_vec3 *l)
{
	*point = *point;
	*l = light->pos;
}
