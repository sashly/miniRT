/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_screen_driver_mt.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 14:50:08 by sashly            #+#    #+#             */
/*   Updated: 2021/03/19 14:52:07 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include "rt_parser.h"
#include <pthread.h>

void	*th_screen(void *th_cont)
{
	t_th_cont	*cont;

	cont = (t_th_cont *)th_cont;
	rt_screen(cont->sc, cont->w0, cont->w1, cont->pixls);
	return (NULL);
}

void	th_cont_fill(t_scene *sc, unsigned char *pxls, int *w, t_th_cont *cont)
{
	cont->sc = sc;
	cont->pixls = pxls;
	cont->w0 = w[0];
	cont->w1 = w[1];
}

int		rt_screen_driver_ret(t_th_cont **th_cont)
{
	free(*th_cont);
	return (1);
}

int		rt_screen_driver(t_scene *sc, unsigned char *pixels)
{
	pthread_t	th[sc->conf.mthred];
	t_th_cont	*th_cont;
	int			th_step;
	int			w[2];
	int			i;

	if (!(th_cont = (t_th_cont *)malloc(sizeof(t_th_cont) * sc->conf.mthred)))
		return (0);
	i = 0;
	w[0] = 0;
	th_step = sc->wres / sc->conf.mthred;
	while (i < sc->conf.mthred)
	{
		w[1] = (i == sc->conf.mthred - 1) ? sc->wres : w[0] + th_step;
		th_cont_fill(sc, pixels, w, &th_cont[i]);
		if (pthread_create(&th[i], NULL, &th_screen, &th_cont[i]) != 0)
			return (0);
		w[0] = w[1];
		i++;
	}
	i = 0;
	while (i < sc->conf.mthred)
		if (pthread_join(th[i++], NULL) != 0)
			return (0);
	return (rt_screen_driver_ret(&th_cont));
}
