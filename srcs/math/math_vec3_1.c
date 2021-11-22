/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_vec3_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 19:10:34 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 20:13:55 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lalgebra.h"

t_vec3	vec3_adn(t_vec3 v, t_flt nbr)
{
	t_vec3 ret;

	ret.x = v.x + nbr;
	ret.y = v.y + nbr;
	ret.z = v.z + nbr;
	return (ret);
}

t_vec3	vec3_muln(t_vec3 v, t_flt nbr)
{
	t_vec3 ret;

	ret.x = v.x * nbr;
	ret.y = v.y * nbr;
	ret.z = v.z * nbr;
	return (ret);
}

t_vec3	vec3_divn(t_vec3 v, t_flt nbr)
{
	t_vec3	ret;
	t_flt	n_inv;

	n_inv = 1. / nbr;
	ret.x = v.x * n_inv;
	ret.y = v.y * n_inv;
	ret.z = v.z * n_inv;
	return (ret);
}

t_flt	vec3_len(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_flt	vec3_sqln(t_vec3 v)
{
	return (v.x * v.x + v.y * v.y + v.z * v.z);
}
