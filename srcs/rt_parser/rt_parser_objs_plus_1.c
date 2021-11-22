/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser_objs_plus_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 13:31:21 by sashly            #+#    #+#             */
/*   Updated: 2021/03/19 13:32:13 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt_parser.h"

int		set_plus_normsine_sp(t_scene *sc, char **spl, int i)
{
	t_flt	tmp;
	int		flen;

	if (!spl[i + 2] || spl[i + 3])
		return (ERR_INVSPEC);
	tmp = ft_atof_m(spl[i + 2], &flen);
	if (*(spl[i + 2] + flen) || tmp <= 0.)
		return (ERR_INVSPEC);
	sc->objs[sc->pobj + 1].surf->cf1 = tmp;
	sc->objs[sc->pobj + 1].norm_f = &sphere_norm_perturb_sin_new;
	return (1);
}

int		set_plus_texture(t_scene *sc, char **spl, int id, int i)
{
	int	ret;

	if (!(id == 3 || id == 5))
		return (ERR_INVSPEC);
	if (!spl[i + 2] || spl[i + 3])
		return (ERR_INVSPEC);
	if ((ret = check_xpm_file(spl[i + 2])) != 1)
		return (ret);
	sc->objs[sc->pobj + 1].surf->txtr = (t_pic *)malloc(sizeof(t_pic));
	if (!sc->objs[sc->pobj + 1].surf->txtr)
		return (ERR_MEMALLOC);
	sc->objs[sc->pobj + 1].surf->txtr->name = ft_strdup(spl[i + 2]);
	if (!sc->objs[sc->pobj + 1].surf->txtr->name)
		return (ERR_MEMALLOC);
	sc->objs[sc->pobj + 1].surf->colmod_f = COLMOD_PTXTR;
	if (id == 3)
		sc->objs[sc->pobj + 1].surf->f_txtr = uv_mapping_sphere;
	else
		sc->objs[sc->pobj + 1].surf->f_txtr = uv_mapping_square;
	sc->conf.pics_to_load++;
	return (1);
}

int		set_plus_bmap(t_scene *sc, char **spl, int id, int i)
{
	int		ret;
	t_flt	tmp;

	if (!(id == 3 || id == 5))
		return (ERR_INVSPEC);
	if (!spl[i + 2] || !spl[i + 3] || spl[i + 4])
		return (ERR_INVSPEC);
	if ((ret = check_xpm_file(spl[i + 2])) != 1)
		return (ret);
	tmp = ft_atof_m(spl[i + 3], &ret);
	if (*(spl[i + 3] + ret) || tmp <= 0.)
		return (ERR_INVSPEC);
	sc->objs[sc->pobj + 1].surf->bmap = (t_pic *)malloc(sizeof(t_pic));
	if (!sc->objs[sc->pobj + 1].surf->bmap)
		return (ERR_MEMALLOC);
	sc->objs[sc->pobj + 1].surf->bmap->name = ft_strdup(spl[i + 2]);
	if (!sc->objs[sc->pobj + 1].surf->bmap->name)
		return (ERR_MEMALLOC);
	sc->objs[sc->pobj + 1].surf->normmod_f = NORMMOD_BUMP;
	sc->objs[sc->pobj + 1].surf->bmap_cf = tmp;
	sc->objs[sc->pobj + 1].norm_f = &sphere_bump_mapping;
	if (id == 5)
		sc->objs[sc->pobj + 1].norm_f = &square_bump_mapping;
	sc->conf.pics_to_load++;
	return (1);
}

int		set_plus_textrbmap_ret(t_scene *sc, int id, t_flt tmp)
{
	sc->objs[sc->pobj + 1].surf->colmod_f = COLMOD_PTXTR;
	sc->objs[sc->pobj + 1].surf->normmod_f = NORMMOD_BUMP;
	sc->objs[sc->pobj + 1].surf->bmap_cf = tmp;
	sc->objs[sc->pobj + 1].surf->f_txtr = uv_mapping_sphere;
	sc->objs[sc->pobj + 1].norm_f = &sphere_bump_mapping;
	if (id == 5)
	{
		sc->objs[sc->pobj + 1].surf->f_txtr = uv_mapping_square;
		sc->objs[sc->pobj + 1].norm_f = &square_bump_mapping;
	}
	sc->conf.pics_to_load += 2;
	return (1);
}

int		set_plus_textrbmap(t_scene *sc, char **spl, int id, int i)
{
	int		ret;
	t_flt	tmp;

	if (!(id == 3 || id == 5))
		return (ERR_INVBSPEC);
	if (!spl[i + 2] || !spl[i + 3] || !spl[i + 4] || spl[i + 5])
		return (ERR_INVBSPEC);
	if ((ret = check_xpm_file(spl[i + 2])) != 1)
		return (ret);
	if ((ret = check_xpm_file(spl[i + 3])) != 1)
		return (ret);
	tmp = ft_atof_m(spl[i + 4], &ret);
	if (*(spl[i + 4] + ret) || tmp <= 0.)
		return (ERR_INVBSPEC);
	if (!(sc->objs[sc->pobj + 1].surf->bmap = (t_pic *)malloc(sizeof(t_pic))))
		return (ERR_MEMALLOC);
	if (!(sc->objs[sc->pobj + 1].surf->bmap->name = ft_strdup(spl[i + 3])))
		return (ERR_MEMALLOC);
	if (!(sc->objs[sc->pobj + 1].surf->txtr = (t_pic *)malloc(sizeof(t_pic))))
		return (ERR_MEMALLOC);
	if (!(sc->objs[sc->pobj + 1].surf->txtr->name = ft_strdup(spl[i + 2])))
		return (ERR_MEMALLOC);
	return (set_plus_textrbmap_ret(sc, id, tmp));
}
