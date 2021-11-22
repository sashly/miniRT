/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_error.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 13:22:05 by sashly            #+#    #+#             */
/*   Updated: 2021/03/19 13:22:36 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser.h"

void	rt_error1(char *name, int type)
{
	if (type == ERR_INVNORM)
		ft_putstr3("Error\nInvalid normal vector ('", name, "' identifier).\n");
	else if (type == ERR_INVFOV)
		ft_putstr_fd("Error\nInvalid FOV for camera ('c').\n", 1);
	else if (type == ERR_OUTRNG)
		ft_putstr3("Error\nValue is out of range for '", name, "' ident.\n");
	else if (type == ERR_INVXPM)
		ft_putstr_fd("Error\nInvalid xpm file.\n", 1);
	else if (type == ERR_INVXPM_OP)
		ft_putstr3("Error\nCannot open xpm file:\n", strerror(errno), ".\n");
	else if (type == ERR_INVBSPEC)
		ft_putstr3("Error\nInvalid bonus spec. for '", name, "' ident.\n");
}

int		rt_error(char *name, int type, t_list **fcache)
{
	if (type == ERR_INVEXT)
		ft_putstr3("Error\n'", name, "' has invalid file extension.\n");
	else if (type == ERR_OPEN || type == ERR_READ)
		ft_putstr3("Error\n", strerror(errno), ".\n");
	else if (type == ERR_INVTY)
		ft_putstr3("Error\n'", name, "' is invalid type identifier.\n");
	else if (type == ERR_MISSRTY)
		ft_putstr3("Error\nMissing required '", name, "' type identifier.\n");
	else if (type == ERR_NOODEC)
		ft_putstr3("Error\nIdentifier '", name, "' declared more than once.\n");
	else if (type == ERR_INVSPEC)
		ft_putstr3("Error\nInvalid specification for '", name, "' ident.\n");
	else if (type == ERR_MEMALLOC)
		ft_putstr_fd("Error\nMemory allocation error.\n", 1);
	else if (type == ERR_WRRES)
		ft_putstr_fd("Error\nWrong render resolution size ('R').\n", 1);
	else if (type == ERR_INVRGB)
		ft_putstr3("Error\nInvalid RGB color for '", name, "' identifier.\n");
	else if (type == ERR_NEGV)
		ft_putstr3("Error\nExpected positive value for '", name, "' ident.\n");
	else
		rt_error1(name, type);
	if (*fcache)
		ft_lstclear(fcache, &del_split);
	return (0);
}

int		check_rt_name(char *name)
{
	size_t nlen;

	if ((nlen = ft_strlen(name)) < 3)
		return (0);
	if (ft_strcmp(&name[nlen - 3], ".rt"))
		return (0);
	return (1);
}
