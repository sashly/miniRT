/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 21:51:30 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 21:53:21 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mlx.h"

int		hooks_aaliasing_on(int keycode, t_mlx_ptrs *p)
{
	if (keycode == HOOK_8_AA_ON9)
	{
		ft_putstr_fd("Anti-aliasing: AA9 on.\n", 1);
		if (p->rt_sc->conf.aalias == 9)
			return (0);
		p->rt_sc->conf.aalias = 9;
	}
	else if (keycode == HOOK_9_AA_ON16)
	{
		ft_putstr_fd("Anti-aliasing: AA16 on.\n", 1);
		if (p->rt_sc->conf.aalias == 16)
			return (0);
		p->rt_sc->conf.aalias = 16;
	}
	else if (keycode == HOOK_0_AA_ON25)
	{
		ft_putstr_fd("Anti-aliasing: AA25 on.\n", 1);
		if (p->rt_sc->conf.aalias == 25)
			return (0);
		p->rt_sc->conf.aalias = 25;
	}
	p->rt_sc->f_sampler = &rt_sampler_aa_reg;
	return (1);
}

int		hooks_aaliasing(int keycode, t_mlx_ptrs *p)
{
	if (keycode == HOOK_6_AA_OFF)
	{
		ft_putstr_fd("Anti-aliasing off.\n", 1);
		if (p->rt_sc->conf.aalias == AA_NONE)
			return (1);
		p->rt_sc->conf.aalias = AA_NONE;
		p->rt_sc->f_sampler = &rt_sampler_naa;
	}
	else if (keycode == HOOK_7_AA_ON4)
	{
		ft_putstr_fd("Anti-aliasing: AA4 on.\n", 1);
		if (p->rt_sc->conf.aalias == 4)
			return (1);
		p->rt_sc->conf.aalias = 4;
		p->rt_sc->f_sampler = &rt_sampler_aa_reg;
	}
	else if (!hooks_aaliasing_on(keycode, p))
		return (1);
	if (!rt_screen_driver(p->rt_sc, p->pixels))
		return (0);
	ft_mlx_put_img_to_win(p);
	return (1);
}

int		hooks_camera_kb_ret(t_mlx_ptrs *p)
{
	if (!rt_screen_driver(p->rt_sc, p->pixels))
		return (0);
	ft_mlx_put_img_to_win(p);
	return (1);
}

int		hooks_camera_kb(int kc, t_mlx_ptrs *p)
{
	if (kc == HOOK_CAM_RX)
		camera_rotate(p->rt_sc, 0, CAM_ROT);
	else if (kc == HOOK_CAM_RX_)
		camera_rotate(p->rt_sc, 0, -CAM_ROT);
	else if (kc == HOOK_CAM_RY)
		camera_rotate(p->rt_sc, 1, CAM_ROT);
	else if (kc == HOOK_CAM_RY_)
		camera_rotate(p->rt_sc, 1, -CAM_ROT);
	else if (kc == HOOK_CAM_MX)
		camera_translate(p->rt_sc, 0, CAM_STEP);
	else if (kc == HOOK_CAM_MX_)
		camera_translate(p->rt_sc, 0, -CAM_STEP);
	else if (kc == HOOK_CAM_MY)
		camera_translate(p->rt_sc, 1, CAM_STEP);
	else if (kc == HOOK_CAM_MY_)
		camera_translate(p->rt_sc, 1, -CAM_STEP);
	else if (kc == HOOK_CAM_MZ)
		camera_translate(p->rt_sc, 2, CAM_STEP);
	else if (kc == HOOK_CAM_MZ_)
		camera_translate(p->rt_sc, 2, -CAM_STEP);
	else if (kc == HOOK_CAM_ZI)
		camera_zoom(p->rt_sc, -CAM_ZOOM);
	else if (kc == HOOK_CAM_ZO)
		camera_zoom(p->rt_sc, CAM_ZOOM);
	return (hooks_camera_kb_ret(p));
}
