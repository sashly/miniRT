/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_camera.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 14:43:14 by sashly            #+#    #+#             */
/*   Updated: 2021/03/19 14:45:17 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		pinhole_construct(t_camera *cam, int wres, int hres)
{
	if (!cam->tmat && !(mat44_malloc2(&cam->tmat, &cam->tmat_i)))
		return (0);
	if (!cam->nb)
		cam->nb = (t_nbasis *)malloc(sizeof(t_nbasis));
	if (!cam->nb)
		free_ptrs_ret(cam->tmat, cam->tmat_i, NULL, 0);
	cam->asp = (t_flt)hres / (t_flt)wres;
	cam->hlf_w = tan(cam->fov * 0.5);
	cam->hlf_h = cam->asp * cam->hlf_w;
	cam->pix_size = 2. * cam->hlf_w / (t_flt)wres;
	gnbasis_view(&cam->orient, cam->nb);
	m44tf_transition(cam->nb, &cam->pos, cam->tmat);
	mat44_inverse(cam->tmat, cam->tmat_i);
	cam->get_ray = &pinhole_pixel_ray;
	return (1);
}

void	pinhole_pixel_ray(t_camera *cam, t_flt u, t_flt v, t_ray *out)
{
	t_vec3	pixel;
	t_vec3	dir;

	pgvec3(-cam->hlf_w + u, -cam->hlf_h + v, -1., &pixel);
	mat44_mult_mat31_inplace(cam->tmat, &pixel, 1);
	pvec3_sub(&pixel, &cam->pos, &dir);
	pgray(&cam->pos, &dir, out);
}

void	camera_rotate(t_scene *sc, int xy, t_flt angle)
{
	t_camera	*cam;
	t_vec3		*orient;
	t_matrix	rot;

	cam = &sc->cams[sc->pcam];
	orient = &sc->cams[sc->pcam].orient;
	if (xy == 0)
		m44tf_rotate_x(angle, &rot);
	else if (xy == 1)
		m44tf_rotate_y(angle, &rot);
	mat44_mult_mat31_inplace(cam->tmat_i, orient, 0);
	mat44_mult_mat31_inplace(&rot, orient, 0);
	mat44_mult_mat31_inplace(cam->tmat, orient, 0);
	cam->constr(cam, sc->wres, sc->hres);
}

void	camera_translate(t_scene *sc, int xyz, t_flt step)
{
	t_camera	*cam;
	t_vec3		move;

	cam = &sc->cams[sc->pcam];
	if (xyz == 0)
		pgvec3(step, 0., 0., &move);
	else if (xyz == 1)
		pgvec3(0., step, 0., &move);
	else if (xyz == 2)
		pgvec3(0., 0., -step, &move);
	mat44_mult_mat31_inplace(cam->tmat, &move, 0);
	pvec3_addc(&cam->pos, move);
	cam->constr(cam, sc->wres, sc->hres);
}

void	camera_zoom(t_scene *sc, t_flt zoom)
{
	t_camera	*cam;
	t_flt		fov;

	cam = &sc->cams[sc->pcam];
	fov = cam->fov * RT_180DPI;
	if (fov + zoom >= 4. && fov + zoom <= 176.)
	{
		fov += zoom;
		cam->fov = fov * RT_PID180;
		cam->hlf_w = tan(cam->fov * 0.5);
		cam->hlf_h = cam->asp * cam->hlf_w;
		cam->pix_size = 2. * cam->hlf_w / (t_flt)sc->wres;
	}
}
