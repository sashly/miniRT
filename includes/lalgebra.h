/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lalgebra.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 15:53:14 by sashly            #+#    #+#             */
/*   Updated: 2021/03/19 16:02:49 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LALGEBRA_H
# define LALGEBRA_H

# include <math.h>
# include <stdlib.h>
# include <stdio.h>

# define RT_EPSILON	0.0000001
# define RT_EPS_SP	0.001
# define RT_EQNEPS	1e-9
# define RT_PI		3.1415926535897932384
# define RT_PI_2	1.5707963267948966192
# define RT_PID180	0.0174532925199432957
# define RT_180DPI	57.2957795131
# define RT_INVPI	0.3183098861837906715
# define RT_INVPI_2	0.1591549430918953357
# define RT_HUGEVAL	1.0e30

typedef double	t_flt;

typedef struct	s_vec2
{
	t_flt	min;
	t_flt	max;
}				t_vec2;

typedef struct	s_vec3
{
	t_flt	x;
	t_flt	y;
	t_flt	z;
}				t_vec3;

typedef struct	s_vec4
{
	t_flt	x;
	t_flt	y;
	t_flt	z;
	t_flt	w;
}				t_vec4;

typedef struct	s_ivec3
{
	int	x;
	int	y;
	int	z;
}				t_ivec3;

typedef struct	s_nbasis
{
	t_vec3	u;
	t_vec3	v;
	t_vec3	w;
	t_vec3	dummy;
}				t_nbasis;

typedef struct	s_matrix
{
	t_flt		mat44[16];
	unsigned	rows;
	unsigned	cols;
}				t_matrix;

typedef t_matrix	*t_mat4;
typedef t_matrix	*t_mat;
typedef t_matrix	*t_submat;

# define MAT_COL(a) ((a)->cols)
# define MAT_ROW(a) ((a)->rows)
# define MAT_EL(a, i, j) ((a)->mat44[((i) * MAT_COL(a)) + (j)])

# define SWAP_FLT(a, b) {t_flt t = a; a = b; b = t;}

# define FLT_ISZERO(x) ((x) > -RT_EQNEPS && (x) < RT_EQNEPS)

t_flt			ft_fabs(t_flt a);
void			ft_swapf(t_flt *a, t_flt *b);
int				flt_equal(t_flt a, t_flt b);
int				flt_iszero(t_flt myf);
int				solve_quadric(t_flt *c, t_flt *roots);
int				solve_quadric_sp(t_flt *c, t_flt *roots);

t_vec3			gvec3(t_flt x, t_flt y, t_flt z);
t_vec3			vec3_add(t_vec3 v1, t_vec3 v2);
t_vec3			vec3_adn(t_vec3 v, t_flt nbr);
t_vec3			vec3_sub(t_vec3 v1, t_vec3 v2);
t_vec3			vec3_mul(t_vec3 v1, t_vec3 v2);
t_vec3			vec3_muln(t_vec3 v, t_flt nbr);
t_vec3			vec3_div(t_vec3 v1, t_vec3 v2);
t_vec3			vec3_divn(t_vec3 v, t_flt nbr);
t_vec3			vec3_cross(t_vec3 v1, t_vec3 v2);
t_vec3			vec3_unit(t_vec3 vec);
t_vec3			vec3_neg(t_vec3 vec);
t_flt			vec3_len(t_vec3 v);
t_flt			vec3_sqln(t_vec3 v);
t_flt			vec3_dot(t_vec3 v1, t_vec3 v2);
t_flt			vec3_absmax(t_vec3 *vec);
int				vec3_equal(t_vec3 *v1, t_vec3 v2);
int				pvec3_equal(t_vec3 *v1, t_vec3 *v2);
int				vec3_orth(t_vec3 *v1, t_vec3 *v2);
int				vec3_coll(t_vec3 *v1, t_vec3 *v2);

void			pgvec3(t_flt x, t_flt y, t_flt z, t_vec3 *out);
void			pvec3_add(t_vec3 *v1, t_vec3 *v2, t_vec3 *out);
void			pvec3_addc(t_vec3 *vec, t_vec3 c);
void			pvec3_addcomb(t_vec3 *v1, t_flt c, t_vec3 *v2, t_vec3 *out);
t_vec3			pvec3_addcombr(t_vec3 *v1, t_flt c1, t_vec3 *v2, t_flt c2);
void			pvec3_add3(t_vec3 *v1, t_vec3 *v2, t_vec3 *v3, t_vec3 *out);
void			pvec3_add_const(t_vec3 *vec, t_flt c, t_vec3 *out);
void			pvec3_sub(t_vec3 *v1, t_vec3 *v2, t_vec3 *out);
void			pvec3_muln(t_vec3 *v, t_flt nbr);
void			pvec3_mulnr(t_vec3 *v, t_flt nbr, t_vec3 *out);
void			pvec3_mulc(t_vec3 *vec, t_vec3 c);
void			pvec3_mul(t_vec3 *vec, t_vec3 *c);
void			pvec3_divn(t_vec3 *v, t_flt nbr);
t_flt			pvec3_len(t_vec3 *v);
void			pvec3_unit(t_vec3 *vec);
void			pvec3_unitneg(t_vec3 *vec);
void			pvec3_unitsub(t_vec3 *v1, t_vec3 *v2, t_vec3 *out);
void			pvec3_neg(t_vec3 *vec);
t_vec3			pvec3_negr(t_vec3 *vec);
void			pvec3_dot(t_vec3 *v1, t_vec3 *v2, t_flt *out);
t_flt			pvec3_dotr(t_vec3 *v1, t_vec3 *v2);
t_flt			pvec3_dotsub(t_vec3 *v1, t_vec3 *v2, t_vec3 *v3);
void			pvec3_cross(t_vec3 *v1, t_vec3 *v2, t_vec3 *out);
void			pvec3_cap(t_vec3 *vec, t_flt cap);
void			pvec3_pow(t_vec3 *col, t_flt pw);
t_flt			pvec3_max(t_vec3 *vec);
int				pvec3_iszero(t_vec3 *vec);

t_vec4			gvec4(t_flt x, t_flt y, t_flt z, t_flt w);
void			pgvec2(t_flt min, t_flt max, t_vec2 *vec);
t_ivec3			givec3(int x, int y, int z);
void			pgivec3(int x, int y, int z, t_ivec3 *ivec);
void			gnbasis_norm(t_vec3 *vec, t_vec3 c1, t_vec3 c2, t_nbasis *nb);
void			gnbasis_view(t_vec3 *vec, t_nbasis *nb);

int				mat44_create(t_mat4 *new_mat);
int				mat44_ident_create(t_mat4 *ident);
void			mat44_copy(t_mat4 a, t_mat4 tocopy);
void			mat44_ident_fill(t_mat4 ident);
int				mat44_malloc2(t_mat4 *m1, t_mat4 *m2);
int				mat44_malloc3(t_mat4 *m1, t_mat4 *m2, t_mat4 *m3);
void			mat44_mult_mat44(t_mat4 m1, t_mat4 m2, t_mat4 out);
void			mat44_mult_tmat44(t_mat4 m1, t_mat4 m2_t, t_mat4 out);
void			mat44_mult_mat41(t_mat4 m, t_vec4 *v, t_vec4 *out);
void			mat44_mult_mat41_inplace(t_mat4 m, t_vec4 *v);
void			mat44_mult_mat31_inplace(t_mat4 m, t_vec3 *v, int is_point);
void			mat44_transpose(t_mat4 in, t_mat4 out);
void			mat44_transpose_inplace(t_mat4 mat);
int				mat44_inverse(t_mat4 mat, t_mat4 inv);
void			m44tf_transition(t_nbasis *nbasis, t_vec3 *e, t_mat4 out);
void			m44tf_transition_inv(t_nbasis *nbasis, t_vec3 *e, t_mat4 out);
void			m44tf_translation(t_vec3 *point, t_mat4 out);
void			m44tf_translation_m(t_vec3 point, t_mat4 out);
void			m44tf_scaling(t_vec3 scale, t_mat4 out);
void			m44tf_rotate_x(t_flt angle, t_mat4 out);
void			m44tf_rotate_y(t_flt angle, t_mat4 out);
void			m44tf_rotate_z(t_flt angle, t_mat4 out);
int				m44tf_rotate_xyz(t_flt a, t_flt b, t_flt g, t_mat4 out);

void			mat44_print(t_mat4 mat, int fraclen);

#endif
