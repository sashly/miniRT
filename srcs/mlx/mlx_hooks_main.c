/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 21:49:59 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 21:51:19 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mlx.h"

int		hmlx_red_cross(t_mlx_ptrs *ptrs)
{
	free_mlx_ptrs(ptrs);
	exit(EXIT_SUCCESS);
	return (1);
}

int		hooks_mlx_main_ret(int k, t_mlx_ptrs *p)
{
	if ((k == HOOK_OBJ_RX || k == HOOK_OBJ_RX_ || k == HOOK_OBJ_RY ||
		k == HOOK_OBJ_RY_ || k == HOOK_OBJ_RZ || k == HOOK_OBJ_RZ_ ||
		k == HOOK_OBJ_MX || k == HOOK_OBJ_MX_ || k == HOOK_OBJ_MY ||
		k == HOOK_OBJ_MY_ || k == HOOK_OBJ_MZ || k == HOOK_OBJ_MZ_)
		&& !hooks_objects_kb(k, p))
		return (0);
	else if (k == HOOK_OBJ_PREV || k == HOOK_OBJ_NEXT)
		hooks_change_obj_ptr(k, p);
	return (1);
}

int		hooks_mlx_main(int k, t_mlx_ptrs *p)
{
	if (k == HOOK_ESC)
		hooks_esc(p);
	else if (k == HOOK_C_CAM && !hooks_camera_change(p))
		return (0);
	else if (k == HOOK_P_SCREEN && !hooks_screenshot(p))
		return (0);
	else if (k == HOOK_1_NMOD && !hooks_normalmap(p))
		return (0);
	else if ((k == HOOK_2_CF_OFF || k == HOOK_3_CF_GRAY || k == HOOK_4_CF_SEPIA
		|| k == HOOK_5_CF_RGB) && !hooks_colfilters(k, p))
		return (0);
	else if ((k == HOOK_6_AA_OFF || k == HOOK_7_AA_ON4 || k == HOOK_8_AA_ON9 ||
		k == HOOK_9_AA_ON16 || k == HOOK_0_AA_ON25) && !hooks_aaliasing(k, p))
		return (0);
	else if ((k == HOOK_CAM_RX || k == HOOK_CAM_RX_ || k == HOOK_CAM_RY ||
		k == HOOK_CAM_RY_ || k == HOOK_CAM_MX || k == HOOK_CAM_MX_ ||
		k == HOOK_CAM_MY || k == HOOK_CAM_MY_ || k == HOOK_CAM_MZ ||
		k == HOOK_CAM_MZ_ || k == HOOK_CAM_ZI || k == HOOK_CAM_ZO)
		&& !hooks_camera_kb(k, p))
		return (0);
	else
		hooks_mlx_main_ret(k, p);
	return (1);
}

void	hooks_esc(t_mlx_ptrs *p)
{
	free_mlx_ptrs(p);
	exit(EXIT_SUCCESS);
}

int		hooks_camera_change(t_mlx_ptrs *p)
{
	int c;

	if (p->rt_sc->pcam < p->rt_sc->cam_size - 1)
		p->rt_sc->pcam++;
	else
		p->rt_sc->pcam = 0;
	c = p->rt_sc->pcam;
	if (!p->rt_sc->cams[c].tmat)
		if (!p->rt_sc->cams[c].constr(&p->rt_sc->cams[c], p->rt_sc->wres,
					p->rt_sc->hres))
			return (0);
	if (!rt_screen_driver(p->rt_sc, p->pixels))
		return (0);
	ft_mlx_put_img_to_win(p);
	return (1);
}
