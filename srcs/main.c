/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 14:58:58 by sashly            #+#    #+#             */
/*   Updated: 2021/03/19 19:16:53 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include "rt_parser.h"
#include "ft_mlx.h"
#include "libft.h"

void	main_usage_check(void)
{
	ft_putstr_fd("Error\nInvalid number of arguments (expected 1 or 2) or", 1);
	ft_putstr_fd(" an invalid argument.\n", 1);
	ft_putstr_fd("Usage: %s <scene.rt> / %s <scene.rt> --save\n", 1);
}

int		main_check_args(int argc, char **argv)
{
	if (argc == 3 && (ft_strcmp(argv[2], "--save")) != 0)
		return (0);
	return (1);
}

int		main(int argc, char **argv)
{
	t_scene	*sc;
	int		p;

	sc = NULL;
	if ((argc == 2 || argc == 3) && main_check_args(argc, argv))
	{
		p = parser_main(argv[1], &sc);
		if (p && argc == 2)
			mlx_main(sc);
		else if (p)
			save_bmp_main(sc);
	}
	else
		main_usage_check();
	return (0);
}
