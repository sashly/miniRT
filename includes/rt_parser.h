/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_parser.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 15:50:31 by sashly            #+#    #+#             */
/*   Updated: 2021/03/19 15:52:53 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_PARSER_H
# define RT_PARSER_H

# include "libft.h"
# include "mini_rt.h"

# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <math.h>

# define DICT_SIZE		21
# define IND_COUNT_SIZE	8

# define ERR_INVEXT		1
# define ERR_OPEN		2
# define ERR_READ		3
# define ERR_INVTY		0
# define ERR_MISSRTY	-1
# define ERR_NOODEC		-2
# define ERR_INVSPEC	-3
# define ERR_MEMALLOC	-4
# define ERR_WRRES		-5
# define ERR_INVRGB		-6
# define ERR_NEGV		-7
# define ERR_INVNORM	-8
# define ERR_INVFOV		-9
# define ERR_OUTRNG		-10
# define ERR_INVXPM		-11
# define ERR_INVXPM_OP	-12
# define ERR_INVBSPEC	-13

int		parser_main(char *name, t_scene **scene);
int		cache_file(int fd, t_list **head);
int		check_and_count_cache(t_list *head, int *count, char **errstr);
int		build_rt_scene_main(t_scene **sc, t_list *fcache,
			int *count, char **errstr);
void	rt_scene_init(t_scene *sc, int *count);
int		rt_scene_content(t_scene *scene, t_list *fcache, char **errstr);

int		rt_scene_memalloc(t_scene **sc, int *c);
int		objs_memalloc(t_scene *sc, int obj_size);
int		gr_memalloc(t_obj *gr, int obj_size);
int		free_rt_scene(t_scene *scene, int ret);
int		objs_free(t_scene *sc, int obj_size, int ret);
int		gr_free(t_obj *gr, int obj_size, int ret);
void	cams_free(t_scene *sc);
void	del_split(void *content);
int		check_rgb(int *rgb);
int		check_norm(t_vec3 *norm);
int		handle_norm(t_vec3 *norm);
float	ft_atof_m(char *str, int *flen);
int		parse_vec3i(char *str, t_vec3 *col);
int		parse_vec3f(char *str, t_vec3 *v3);

int		find_ident(char *str);
int		count_ident(char *str, int *count, int *i);
int		check_ident_spec(char **split, int index);
int		ident_size(int id);

int		rt_error(char *name, int type, t_list **fcache);
int		check_rt_name(char *name);
int		check_xpm_file(char *name);

int		set_resolution(t_scene *scene, char **split);
int		set_amblight(t_scene *scene, char **split);
int		set_light(t_scene *sc, char **split, int mod);
int		set_direct_light(t_scene *sc, int mod);
int		set_cameras(t_scene *sc, char **split);
int		set_bonus(t_scene *scene, char **split, int id);
int		set_background(t_scene *sc, char **split);
int		set_back_skybox(t_scene *sc, char **split);
int		set_aaliasing(t_scene *sc, char **split);
int		set_colorfilter(t_scene *sc, char **split);
int		set_objects(t_scene *sc, char **spl, int id);
void	set_material(t_obj *obj, t_vec3 *col, t_flt *kffs);
int		set_sphere_raw(t_scene *scene, char **split);
int		set_sphere(t_vec3 *v3, t_flt rad, t_obj *sp);
int		set_ellips_raw(t_scene *scene, char **split);
int		set_ellipsoid(t_vec3 *v3, float *f, float *angls, t_obj *el);
int		set_plane_raw(t_scene *scene, char **split);
int		set_plane(t_vec3 *cd, t_vec3 *n, t_vec3 *col, t_obj *pl);
int		set_square_raw(t_scene *scene, char **split);
int		set_square(t_vec3 *v3, float side, t_obj *sq);
int		set_triang_raw(t_scene *scene, char **split);
int		set_triangle(t_vec3 *v3, t_obj *tr);
int		set_quadr_raw(t_scene *scene, char **split, int mod);
int		set_cylinder(t_vec3 *v3, float *f, int cap, t_obj *cy);
int		set_cone(t_vec3 *v3, float *f, t_obj *cn);
int		set_rect_raw(t_scene *scene, char **split);
int		set_rectangle(t_vec3 *v3, t_obj *rc);
int		set_disk_raw(t_scene *scene, char **split);
int		set_disk(t_vec3 *v3, float rad, t_obj *ds);
int		set_aabb_raw(t_scene *scene, char **split);
int		set_aabb(t_vec3 *v3, float *f, float *angls, t_obj *ab);
int		set_pyramid_raw(t_scene *scene, char **split);
int		set_pyramid(t_vec3 *v3, float *f, t_obj *py);
int		pyramid_construct(t_vec3 *v3, float *f, t_obj *py);
int		set_cube_raw(t_scene *scene, char **split);
int		set_cube(t_vec3 *v3, float side, t_obj *cb);
int		cube_construct(t_vec3 *v3, float side, t_obj *cb);
int		set_plus_bonus(t_scene *sc, char **spl, int id);
int		set_plus_checker3d(t_scene *sc, char **spl, int i);
int		set_plus_checker2d_sp(t_scene *sc, char **spl, int i, int is_outl);
int		set_plus_checker2do_sp(t_scene *sc, char **spl, int i);
int		set_plus_normsine_sp(t_scene *sc, char **spl, int i);
int		set_plus_texture(t_scene *sc, char **spl, int id, int i);
int		set_plus_bmap(t_scene *sc, char **spl, int id, int i);
int		set_plus_textrbmap(t_scene *sc, char **spl, int id, int i);

#endif
