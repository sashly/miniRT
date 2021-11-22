/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_screen_driver_ot.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 14:52:16 by sashly            #+#    #+#             */
/*   Updated: 2021/03/19 14:52:33 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include "rt_parser.h"

int	rt_screen_driver(t_scene *sc, unsigned char *pixels)
{
	rt_screen(sc, 0, sc->wres, pixels);
	return (1);
}
