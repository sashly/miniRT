/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_utils_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 13:38:21 by sashly            #+#    #+#             */
/*   Updated: 2021/03/19 13:39:03 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser.h"

int		parse_vec3i(char *str, t_vec3 *col)
{
	int	ec;
	int	rgb[3];

	ec = 0;
	ft_memset(&rgb, 0, sizeof(int) * 3);
	while (*str && ec < 3)
	{
		if (*str && IS_DIGIT(*str))
		{
			while (*str && IS_DIGIT(*str))
				rgb[ec] = 10 * rgb[ec] + (*(str++) - '0');
			if (*str == ',' && *(str++))
				ec++;
		}
		if (ec <= 2 && IS_DIGIT(*str))
			continue;
		else if (ec == 2 && !*str && *(str - 1) != ',' && check_rgb(rgb))
		{
			gvec3_col(rgb[0], rgb[1], rgb[2], col);
			return (1);
		}
		else if (!IS_DIGIT(*str) || !ec || ec == 2)
			return (0);
	}
	return (0);
}

float	ft_atof_m(char *str, int *flen)
{
	float	int_p;
	float	frac_p;
	float	sign;
	char	*s;
	int		n;

	int_p = 0.f;
	frac_p = 0.f;
	s = str;
	sign = (*str == '-') ? -1.f : 1.f;
	if (*str == '-')
		str++;
	while (IS_DIGIT(*str))
		int_p = int_p * 10 + (float)(*(str++) - '0');
	if (*str == '.')
	{
		str++;
		n = -1;
		while (IS_DIGIT(*str))
			frac_p += powf(10, n--) * (*(str++) - '0');
	}
	*flen = str - s;
	return (sign * (int_p + frac_p));
}

int		parse_vec3f(char *str, t_vec3 *v3)
{
	float	vec[3];
	int		flen;
	int		fc;

	fc = 0;
	flen = 0;
	while (*str && fc < 3)
	{
		vec[fc] = ft_atof_m(str, &flen);
		if (!flen || (flen == 1 && *str == '.'))
			return (0);
		str += flen;
		if (fc < 2 && *str == ',' && *(str++))
			fc++;
		else if (fc == 2 && !*str)
		{
			*v3 = gvec3(vec[0], vec[1], vec[2]);
			return (1);
		}
		else
			return (0);
	}
	return (0);
}
