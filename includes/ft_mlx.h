/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mlx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sashly <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 15:40:53 by sashly            #+#    #+#             */
/*   Updated: 2021/03/19 15:46:33 by sashly           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MLX_H
# define FT_MLX_H

# include "mini_rt.h"
# include "libft.h"

# include <mlx.h>

# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <stdlib.h>

typedef struct	s_img
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		img_w;
	int		img_h;
	char	*name;
}				t_img;

typedef struct	s_mlx_ptrs
{
	void			*mlx;
	void			*win;
	t_img			*wimg;
	t_img			*pics;
	int				pics_size;
	int				ppic;
	t_scene			*rt_sc;
	unsigned char	*pixels;
}				t_mlx_ptrs;

int				mlx_main(t_scene *rt_scene);
int				ft_mlx_init_ptrs(t_scene *rt_sc, t_mlx_ptrs *p);
int				ft_mlx_handle_pics(t_scene *sc, t_mlx_ptrs *p);
int				ft_mlx_load_texture(t_scene *sc, t_mlx_ptrs *p, int i, int k);
int				ft_mlx_load_bmap(t_scene *sc, t_mlx_ptrs *p, int i, int k);
int				ft_mlx_load_skybox(t_scene *sc, t_mlx_ptrs *p, int k);
int				free_mlx_ptrs(t_mlx_ptrs *p);
void			free_mlx_images(t_mlx_ptrs *p);

int				get_trgb(int t, int r, int g, int b);
void			ft_mlx_pixel_put(t_img *img, int x, int y, int color);
void			ft_mlx_put_img_to_win(t_mlx_ptrs *p);
void			ft_mlx_resolution_restrict(t_scene *rt_sc);

int				hmlx_red_cross(t_mlx_ptrs *ptrs);
int				hooks_mlx_main(int keycode, t_mlx_ptrs *p);
void			hooks_esc(t_mlx_ptrs *p);
int				hooks_camera_change(t_mlx_ptrs *p);
int				hooks_screenshot(t_mlx_ptrs *p);
int				hooks_normalmap(t_mlx_ptrs *p);
int				hooks_colfilters(int keycode, t_mlx_ptrs *p);
int				hooks_aaliasing(int keycode, t_mlx_ptrs *p);
int				hooks_camera_kb(int kc, t_mlx_ptrs *p);
int				hooks_objects_kb(int kc, t_mlx_ptrs *p);
void			hooks_change_obj_ptr(int kc, t_mlx_ptrs *p);

# define R_MAX_WIDTH		2560
# define R_MAX_HEIGHT		1395

# define CAM_STEP			2.
# define CAM_ROT			2.
# define CAM_ZOOM			5.

# define OBJ_STEP			2.
# define OBJ_ROT			2.

# define HOOK_ESC			53
# define HOOK_C_CAM			8
# define HOOK_P_SCREEN		35
# define HOOK_1_NMOD		18
# define HOOK_2_CF_OFF		19
# define HOOK_3_CF_GRAY		20
# define HOOK_4_CF_SEPIA	21
# define HOOK_5_CF_RGB		23
# define HOOK_6_AA_OFF		22
# define HOOK_7_AA_ON4		26
# define HOOK_8_AA_ON9		28
# define HOOK_9_AA_ON16		25
# define HOOK_0_AA_ON25		29
# define HOOK_CAM_RY		123
# define HOOK_CAM_RY_		124
# define HOOK_CAM_RX		126
# define HOOK_CAM_RX_		125
# define HOOK_CAM_MX		2
# define HOOK_CAM_MX_		0
# define HOOK_CAM_MY		14
# define HOOK_CAM_MY_		12
# define HOOK_CAM_MZ		13
# define HOOK_CAM_MZ_		1
# define HOOK_CAM_ZI		24
# define HOOK_CAM_ZO		27
# define HOOK_OBJ_MX		4
# define HOOK_OBJ_MX_		3
# define HOOK_OBJ_MY		17
# define HOOK_OBJ_MY_		5
# define HOOK_OBJ_MZ		16
# define HOOK_OBJ_MZ_		15
# define HOOK_OBJ_RX		34
# define HOOK_OBJ_RX_		40
# define HOOK_OBJ_RY		38
# define HOOK_OBJ_RY_		37
# define HOOK_OBJ_RZ		31
# define HOOK_OBJ_RZ_		32
# define HOOK_OBJ_PREV		43
# define HOOK_OBJ_NEXT		47

#endif
