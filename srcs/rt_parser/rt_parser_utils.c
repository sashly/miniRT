/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 13:37:59 by sashly            #+#    #+#             */
/*   Updated: 2021/03/19 13:39:58 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser.h"

int	check_rgb(int *rgb)
{
	if (rgb[0] < 0 || rgb[0] > 255)
		return (0);
	if (rgb[1] < 0 || rgb[1] > 255)
		return (0);
	if (rgb[2] < 0 || rgb[2] > 255)
		return (0);
	return (1);
}

int	check_norm(t_vec3 *norm)
{
	if (fabs(norm->x) >= 1.f + RT_EPSILON)
		return (0);
	if (fabs(norm->y) >= 1.f + RT_EPSILON)
		return (0);
	if (fabs(norm->z) >= 1.f + RT_EPSILON)
		return (0);
	if (pvec3_iszero(norm))
		return (0);
	pvec3_unit(norm);
	return (1);
}

int	handle_norm(t_vec3 *norm)
{
	*norm = vec3_unit(*norm);
	if (vec3_absmax(norm) < 0. - RT_EPSILON)
		pvec3_neg(norm);
	return (1);
}

int	check_xpm_file(char *name)
{
	size_t	nlen;
	int		fd;

	if ((nlen = ft_strlen(name)) < 5)
		return (ERR_INVXPM);
	if (ft_strcmp(&name[nlen - 4], ".xpm"))
		return (ERR_INVXPM);
	fd = open(name, O_RDONLY);
	if (fd == -1)
		return (ERR_INVXPM_OP);
	close(fd);
	return (1);
}
