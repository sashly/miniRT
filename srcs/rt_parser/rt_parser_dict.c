/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_dict.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 13:17:55 by sashly            #+#    #+#             */
/*   Updated: 2021/03/19 13:19:59 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser.h"

/*
**	RT_FILE type identifiers (elements which are defined by a capital letter
** 	can only be declared once in the scene):
**	"c" - camera; "l" - spot light; "dl" - directional light; "R" - resolution;
**	"A" - ambient light; "B" - background; "CF" - color filter (gray, sepia,
**	r, g, b); AA - anti-aliasing;
**	Objects: "sp" - sphere; "pl" - plane; "sq" - square; "tr" - triangle;
**	"cy" - cylinder; "cp" - capped cylinder; "cn" - cone; "rc" - rectangle;
**	"ds" - disk; "ab" - aabb; "cb" - cube; "py" - pyramid; "el" - ellipsoid;
*/

char *g_dict[DICT_SIZE] = {"c", "l", "dl", "sp", "pl", "sq", "tr", "cy", "cp",
	"cn", "rc", "ds", "ab", "cb", "py", "el", "R", "A", "CF", "AA", "B"};

char g_dict_m[DICT_SIZE] = {3, 3, 3, 3, 3, 4, 4, 5, 5, 5, 4, 4, 8, 4, 5, 8, 2,
	2, 1, 1, 1};

int	count_ident(char *str, int *count, int *i)
{
	int index;

	index = 0;
	while (index < DICT_SIZE)
	{
		if (!ft_strcmp(str, g_dict[index]))
		{
			if (index >= 16)
				count[3 + (index - 16)]++;
			else if (index >= 0 && index < 3)
				count[(index) ? 1 : 0]++;
			else if (index >= 3)
				count[2]++;
			if (count[3] > 1 || count[4] > 1 || count[5] > 1 || count[6] > 1
				|| count[7] > 1)
				return (ERR_NOODEC);
			*i = index;
			return (1);
		}
		index++;
	}
	return (0);
}

int	check_ident_spec(char **split, int index)
{
	int	count;
	int	i;

	if (index > 19)
		return (1);
	i = 1;
	count = 0;
	while (split[i++])
		count++;
	if (count > g_dict_m[index] && !ft_strcmp(split[g_dict_m[index] + 1], "+"))
		return (1);
	if (count != g_dict_m[index])
		return (0);
	return (1);
}

int	find_ident(char *str)
{
	int index;

	index = 0;
	while (index < DICT_SIZE)
	{
		if (!(ft_strcmp(str, g_dict[index])))
			return (index);
		index++;
	}
	return (-1);
}

int	ident_size(int id)
{
	return (g_dict_m[id]);
}
