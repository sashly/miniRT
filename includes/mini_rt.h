/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_rt.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 16:14:58 by sashly            #+#    #+#             */
/*   Updated: 2021/03/19 16:59:14 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <stdio.h>
# include <float.h>
# include <stddef.h>
# include <math.h>

# include "lalgebra.h"
# include "rt_utils.h"

typedef struct			s_ray
{
	t_vec3	orig;
	t_vec3	dir;
}						t_ray;

t_ray					gray(t_vec3 orig, t_vec3 dir);
void					pgray(t_vec3 *orig, t_vec3 *dir, t_ray *outray);
void					ray_point(t_ray *ray, t_flt t, t_vec3 *point);
void					ray_copy(t_ray *orig, t_ray *copy);

# define NONE      0
# define SPHERE    1
# define CYLINDER  2
# define PLANE     3
# define SQUARE    4
# define TRIANGLE  5
# define CONE      6
# define RECTANGLE 7
# define DISK      8
# define AABB      9
# define GROUP     10
# define ELLIPSD   11

typedef struct			s_sphere
{
	t_vec3	cent;
	t_flt	r;
	t_flt	rp2;
}						t_sphere;

typedef struct			s_plane
{
	t_vec3	p;
	t_vec3	n;
}						t_plane;

typedef struct			s_cylinder
{
	t_vec3	a;
	t_vec3	b;
	t_vec3	na;
	t_flt	r;
	t_flt	rp2;
	t_flt	h;
	int		cap;
}						t_cylinder;

typedef struct			s_triangle
{
	t_vec3	p1;
	t_vec3	p2;
	t_vec3	p3;
	t_vec3	e1;
	t_vec3	e2;
	t_vec3	n;
}						t_triangle;

typedef struct			s_square
{
	t_vec3	p;
	t_vec3	n;
	t_flt	side;
	t_flt	sd2;
}						t_square;

typedef struct			s_disk
{
	t_vec3	p;
	t_vec3	n;
	t_flt	r;
	t_flt	rp2;
}						t_disk;

typedef struct			s_rectangle
{
	t_vec3	p;
	t_vec3	a;
	t_vec3	b;
	t_vec3	n;
	t_flt	sqa;
	t_flt	sqb;
}						t_rectangle;

typedef struct			s_ellipsoid
{
	t_vec3	cent;
	t_flt	r1;
	t_flt	r2;
	t_flt	r3;
}						t_ellipsoid;

typedef struct			s_cone
{
	t_vec3	c;
	t_vec3	n;
	t_vec3	ph;
	t_flt	r;
	t_flt	h;
	t_flt	sin_th;
	int		cap;
}						t_cone;

typedef struct			s_aabb
{
	t_vec3	p;
	t_flt	lx;
	t_flt	ly;
	t_flt	lz;
}						t_aabb;

typedef struct s_obj	t_obj;

typedef struct			s_group
{
	t_obj	*gr;
	int		gsize;
}						t_group;

typedef union			u_prim
{
	t_sphere	sp;
	t_ellipsoid	el;
	t_cylinder	cy;
	t_plane		pl;
	t_square	sq;
	t_triangle	tr;
	t_cone		cn;
	t_rectangle	rc;
	t_disk		ds;
	t_aabb		ab;
	t_group		gr;
}						t_prim;

typedef struct			s_hit_rec
{
	t_vec3	p;
	t_vec3	n;
	t_flt	t;
	int		obj_id;
}						t_hit_rec;

# define DEF_AMB	0.2
# define DEF_DIFF	0.9
# define DEF_SPEC	0.9
# define DEF_SHIN	200
# define DEF_REFL	0.
# define DEF_TRAN	0.
# define DEF_REFI	1.

typedef struct			s_pic
{
	char	*name;
	char	*arr;
	int		w;
	int		h;
}						t_pic;

# define COLMOD_MONO	0
# define COLMOD_FTXTR	1
# define COLMOD_PTXTR	2

# define NORMMOD_DEF	0
# define NORMMOD_F		1
# define NORMMOD_BUMP	2

typedef	void			(*t_ftexture)(t_obj *obj, t_hit_rec *hit_rec,
		t_vec3 *outcol);

typedef struct			s_surf
{
	t_vec3		col;
	int			colmod_f;
	int			normmod_f;
	t_vec3		col1;
	t_vec3		col2;
	t_flt		cf1;
	t_flt		cf2;
	t_ftexture	f_txtr;
	t_pic		*txtr;
	t_pic		*bmap;
	t_flt		bmap_cf;
	t_flt		kamb;
	t_flt		kdiff;
	t_flt		kspec;
	t_flt		kshin;
	t_flt		krefl;
	t_flt		ktran;
	t_flt		ref_ind;
}						t_surf;

typedef struct			s_trmat
{
	t_mat4	tmat;
	t_mat4	inv;
	t_mat4	tinv;
}						t_trmat;

typedef int				(*t_fhit)(t_ray *, t_obj *, t_flt, t_hit_rec *);

typedef void			(*t_fnorm)(t_obj *, t_hit_rec *, t_vec3 *);

struct					s_obj
{
	int		type;
	int		obj_id;
	t_prim	obj;
	t_surf	*surf;
	t_trmat	*m;
	t_fhit	hit_f;
	t_fnorm	norm_f;
	t_obj	*aabb;
	t_obj	*parent;
};

# define LIGHT_AMB	0
# define LIGHT_SPOT	1
# define LIGHT_DIR	2

typedef struct s_light	t_light;

typedef void			(*t_fgetl)(t_light *light, t_vec3 *point, t_vec3 *l);

struct					s_light
{
	int		type;
	t_vec3	pos;
	t_vec3	col;
	t_flt	ints;
	t_fgetl	f_gl;
};

typedef struct s_camera	t_camera;

typedef void			(*t_fget_ray)(t_camera *, t_flt, t_flt, t_ray *);

typedef int				(*t_fcam_const)(t_camera *, int, int);

struct					s_camera
{
	t_vec3			pos;
	t_vec3			orient;
	t_flt			fov;
	t_nbasis		*nb;
	t_mat4			tmat;
	t_mat4			tmat_i;
	t_fget_ray		get_ray;
	t_fcam_const	constr;
	t_flt			hlf_w;
	t_flt			hlf_h;
	t_flt			pix_size;
	t_flt			asp;
};

# define BG_MONO		0
# define BG_LERP		1
# define BG_SKYBOX		2

# define SKYBOX_SIZE	1000.

typedef struct			s_skybox
{
	t_obj	sp;
	t_pic	lookup;
	t_flt	ints;
}						t_skybox;

typedef struct			s_backg
{
	int			mod;
	t_vec3		col1;
	t_vec3		col2;
	t_skybox	*skybox;
}						t_backg;

# define CF_NONE	0
# define CF_GRAY	1
# define CF_SEPIA	2
# define CF_RED		3
# define CF_GREEN	4
# define CF_BLUE	5

# define AA_NONE	0
# define MT_NONE	0
# define NM_NONE	0

# define MT_DEFL	4

# define RT_GAMMA	1.

# define RT_TONEMAP	0

typedef	void			(*t_fcflt)(t_vec3 *);

typedef	void			(*t_ftnmap)(t_vec3 *);

typedef struct			s_conf
{
	char		cfilt;
	t_fcflt		f_colfilt;
	t_ftnmap	f_tonemap;
	char		aalias;
	char		mthred;
	char		nmap;
	t_flt		gamma;
	int			pics_to_load;
}						t_conf;

typedef struct s_scene	t_scene;

typedef	void			(*t_fshadr)(t_scene *, t_ray *, t_hit_rec *, t_vec3 *);

typedef void			(*t_fsamplr)(t_scene *, int *,
		unsigned char **, t_vec3 *);

struct					s_scene
{
	t_camera	*cams;
	t_light		*ambl;
	t_light		*lgts;
	t_obj		*objs;
	t_backg		*back;
	t_conf		conf;
	t_fsamplr	f_sampler;
	t_fshadr	f_shader;
	int			hres;
	int			wres;
	int			cam_size;
	int			lgt_size;
	int			obj_size;
	int			pcam;
	int			plgt;
	int			pobj;
};

typedef	struct			s_th_cont
{
	t_scene			*sc;
	unsigned char	*pixls;
	int				w0;
	int				w1;
}						t_th_cont;

int						save_bmp_main(t_scene *sc);
void					anti_mlx_check(t_scene *sc);
int						rt_screen_driver(t_scene *sc, unsigned char *pixels);

void					rt_screen(t_scene *sc, int w0, int w1,
		unsigned char *pixels);
void					rt_sampler_naa(t_scene *sc, int *i,
		unsigned char **buf, t_vec3 *col);
void					rt_sampler_aa_reg(t_scene *sc, int *i,
		unsigned char **buf, t_vec3 *cl);
void					rt_trace_ray(t_scene *sc, t_ray *ray, t_vec3 *out_col);
int						rt_intersect(t_scene *sc, t_ray	*ray, t_flt t_max,
		t_hit_rec *hr);
int						rt_is_shadowed(t_scene *sc, t_light *light,
		t_hit_rec *hr, t_vec3 *l);
void					rt_shade_phong(t_scene *sc, t_ray *ray, t_hit_rec *hr,
		t_vec3 *out_col);
void					rt_shade_nmap(t_scene *sc, t_ray *ray, t_hit_rec *hr,
		t_vec3 *out_col);
void					rt_shade_backg(t_scene *sc, t_ray *ray,
		t_vec3 *out_col);
void					rt_shade_skybox(t_scene *sc, t_ray *ray,
		t_vec3 *out_col);
void					rt_process_pixel(t_scene *sc, t_vec3 *col, int *i,
		unsigned char *pixs);
void					rt_tonemap_cap(t_vec3 *col);
void					rt_tonemap_clamp(t_vec3 *col);

int						pinhole_construct(t_camera *cam, int wres, int hres);
void					pinhole_pixel_ray(t_camera *cam, t_flt u, t_flt v,
		t_ray *out);
void					camera_rotate(t_scene *sc, int xy, t_flt angle);
void					camera_translate(t_scene *sc, int xyz, t_flt step);
void					camera_zoom(t_scene *sc, t_flt zoom);
void					camera_rotate_onlmat(t_scene *sc, int xyz, int angle);
void					camera_translate_onlmat(t_scene *sc, int xyz,
		t_flt step);
void					get_l_pointlight(t_light *light, t_vec3 *point,
		t_vec3 *l);
void					get_l_directional(t_light *light, t_vec3 *point,
		t_vec3 *l);

int						is_hit_sphere(t_ray *ray, t_obj *sp, t_flt t_max,
		t_hit_rec *hr);
int						is_hit_sphere_alg(t_ray *ray, t_obj *sp, t_flt t_max,
		t_hit_rec *hr);
int						is_hit_sphere_gs(t_ray *ray, t_obj *sp, t_flt t_max,
		t_hit_rec *hr);
void					sphere_norm(t_obj *sp, t_hit_rec *hr, t_vec3 *norm);
void					sphere_norm_perturb_sin_new(t_obj *sp, t_hit_rec *hr,
		t_vec3 *norm);
void					sphere_bump_mapping(t_obj *sp, t_hit_rec *hr,
		t_vec3 *norm);
int						is_hit_plane(t_ray *ray, t_obj *pl, t_flt t_max,
		t_hit_rec *hr);
void					plane_norm(t_obj *pl, t_hit_rec *hr, t_vec3 *norm);
int						hit_plane(t_ray *ray, t_vec3 *p, t_vec3 *n, t_flt *t);
int						is_hit_triangle(t_ray *ray, t_obj *tr, t_flt t_max,
		t_hit_rec *hr);
void					triangle_norm(t_obj *tr, t_hit_rec *hr, t_vec3 *norm);
int						is_hit_square(t_ray *ray, t_obj *sq, t_flt t_max,
		t_hit_rec *hr);
void					square_norm(t_obj *sq, t_hit_rec *hr, t_vec3 *norm);
void					square_bump_mapping(t_obj *sq, t_hit_rec *hr,
		t_vec3 *norm);
int						is_hit_disk(t_ray *ray, t_obj *ds, t_flt t_max,
		t_hit_rec *hr);
void					disk_norm(t_obj *ds, t_hit_rec *hr, t_vec3 *norm);
int						is_hit_cylinder_la(t_ray *ray, t_obj *cy, t_flt t_max,
		t_hit_rec *hr);
void					cylinder_norm_la(t_obj *cy, t_hit_rec *hr,
		t_vec3 *norm);
int						cy_tmat_build(t_obj *cy);
int						is_hit_cone(t_ray *ray, t_obj *cn, t_flt t_max,
		t_hit_rec *hr);
void					cone_norm(t_obj *cy, t_hit_rec *hr, t_vec3 *norm);
int						cn_tmat_build(t_obj *cn);
int						is_hit_aabb(t_ray *ray, t_obj *ab, t_flt t_max,
		t_hit_rec *hr);
int						ab_tmat_build(t_obj *ab, t_flt a, t_flt b, t_flt g);
void					aabb_norm(t_obj *ab, t_hit_rec *hr, t_vec3 *norm);
int						is_hit_ellipsoid(t_ray *ray, t_obj *el, t_flt t_max,
		t_hit_rec *hr);
void					ellipsoid_norm(t_obj *el, t_hit_rec *hr, t_vec3 *norm);
int						el_tmat_build(t_obj *el, t_flt a, t_flt b, t_flt g);
int						is_hit_cylinder_cp_t(t_ray *ray, t_obj *cp, t_flt t_max,
		t_hit_rec *hr);
void					cylinder_norm_cp_t(t_obj *cp, t_hit_rec *hr,
		t_vec3 *norm);
int						check_cap(t_ray *ray, t_flt t);
int						is_hit_group(t_ray *ray, t_obj *gr, t_flt t_max,
		t_hit_rec *hr);
void					group_norm(t_obj *gr, t_hit_rec *hr, t_vec3 *norm);
int						group_tmat_build(t_obj *gr);
int						cb_tmat_build(t_obj *cb, t_vec3 *p0, t_vec3 *norm);

int						hit_return_helper(t_hit_rec *hr, t_flt t_min,
		t_flt t_max, t_flt tmp);
void					get_objray(t_obj *obj, t_ray *wray, t_ray *oray);
void					norm_to_world(t_obj *obj, t_vec3 *norm);
void					move_object(t_scene *sc, int xyz, t_flt step);
void					rotate_object(t_scene *sc, int xyz, t_flt angle);
void					move_object_local(t_scene *sc, int xyz, t_flt step);

void					checker3d_txtr_sine(t_obj *obj, t_hit_rec *hr,
		t_vec3 *outcol);
void					checker3d_txtr_floor(t_obj *obj, t_hit_rec *hr,
		t_vec3 *outcol);
void					bgrt_to_vec3(char *bgrt, t_vec3 *out_col);
void					checker2d_sphere(t_obj *obj, t_hit_rec *hr,
		t_vec3 *outcol);
void					checker2d_outline_sphere(t_obj *obj, t_hit_rec *hr,
		t_vec3 *outcol);
void					get_sphere_uv(t_hit_rec *hr, t_flt *u, t_flt *v);
void					get_square_uv(t_obj *sq, t_hit_rec *hr,
		t_flt *u, t_flt *v);
void					uv_mapping_sphere(t_obj *obj, t_hit_rec *hr,
		t_vec3 *outcol);
void					uv_mapping_square(t_obj *obj, t_hit_rec *hr,
		t_vec3 *outcol);

void					colfilt_grayscale(t_vec3 *col);
void					colfilt_sepia(t_vec3 *c);
void					colfilt_red(t_vec3 *col);
void					colfilt_green(t_vec3 *col);
void					colfilt_blue(t_vec3 *col);

int						save_bmp(const char *filename,
		const unsigned char *pixels, int h, int w);

#endif
