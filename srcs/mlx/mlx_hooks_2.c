/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 21:53:31 by sashly            #+#    #+#             */
/*   Updated: 2021/03/18 21:53:56 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mlx.h"

int		hooks_objects_set_ptr(t_scene *sc)
{
	int	i;

	if (sc->objs[sc->pobj].type == AABB)
		return (1);
	i = 0;
	while (i < sc->obj_size)
	{
		if (sc->objs[i].type == AABB)
		{
			sc->pobj = i;
			break ;
		}
		i++;
	}
	return (sc->objs[sc->pobj].type == AABB);
}

void	hooks_objects_kb_rot(int kc, t_mlx_ptrs *p)
{
	if (kc == HOOK_OBJ_RX)
		rotate_object(p->rt_sc, 0, -OBJ_ROT);
	else if (kc == HOOK_OBJ_RX_)
		rotate_object(p->rt_sc, 0, OBJ_ROT);
	else if (kc == HOOK_OBJ_RY)
		rotate_object(p->rt_sc, 1, OBJ_ROT);
	else if (kc == HOOK_OBJ_RY_)
		rotate_object(p->rt_sc, 1, -OBJ_ROT);
	else if (kc == HOOK_OBJ_RZ)
		rotate_object(p->rt_sc, 2, -OBJ_ROT);
	else if (kc == HOOK_OBJ_RZ_)
		rotate_object(p->rt_sc, 2, OBJ_ROT);
}

int		hooks_objects_kb(int kc, t_mlx_ptrs *p)
{
	if (!hooks_objects_set_ptr(p->rt_sc))
		return (0);
	if (kc == HOOK_OBJ_MZ)
		move_object(p->rt_sc, 2, OBJ_STEP);
	else if (kc == HOOK_OBJ_MZ_)
		move_object(p->rt_sc, 2, -OBJ_STEP);
	else if (kc == HOOK_OBJ_MX)
		move_object(p->rt_sc, 0, OBJ_STEP);
	else if (kc == HOOK_OBJ_MX_)
		move_object(p->rt_sc, 0, -OBJ_STEP);
	else if (kc == HOOK_OBJ_MY)
		move_object(p->rt_sc, 1, OBJ_STEP);
	else if (kc == HOOK_OBJ_MY_)
		move_object(p->rt_sc, 1, -OBJ_STEP);
	else
		hooks_objects_kb_rot(kc, p);
	if (!rt_screen_driver(p->rt_sc, p->pixels))
		return (0);
	ft_mlx_put_img_to_win(p);
	return (1);
}

void	hooks_change_obj_ptr_prev(t_mlx_ptrs *p)
{
	int	i;

	i = p->rt_sc->pobj - 1;
	while (i >= 0)
	{
		if (p->rt_sc->objs[i].type == AABB)
			break ;
		i--;
	}
	if (i < 0)
	{
		i = p->rt_sc->obj_size - 1;
		while (i >= 0)
		{
			if (p->rt_sc->objs[i].type == AABB)
				break ;
			i--;
		}
	}
	if (p->rt_sc->objs[i].type == AABB)
		p->rt_sc->pobj = i;
}

void	hooks_change_obj_ptr(int kc, t_mlx_ptrs *p)
{
	if (kc == HOOK_OBJ_NEXT)
	{
		kc = p->rt_sc->pobj + 1;
		while (kc < p->rt_sc->obj_size)
		{
			if (p->rt_sc->objs[kc].type == AABB)
				break ;
			kc++;
		}
		if (kc == p->rt_sc->obj_size)
		{
			kc = 0;
			while (kc < p->rt_sc->obj_size)
			{
				if (p->rt_sc->objs[kc].type == AABB)
					break ;
				kc++;
			}
		}
		if (p->rt_sc->objs[kc].type == AABB)
			p->rt_sc->pobj = kc;
	}
	else if (kc == HOOK_OBJ_PREV)
		hooks_change_obj_ptr_prev(p);
}
