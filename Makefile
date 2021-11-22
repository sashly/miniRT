# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sashly <sashly@student.21-school.ru>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/01 20:21:56 by sashly            #+#    #+#              #
#    Updated: 2021/03/01 20:22:08 by sashly           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME        = miniRT
LIBFT       = ./libft/libft.a
LIBFT_DIR   = ./libft/
FLAGS       = -Wall -Wextra -Werror
HEADERS     = ./includes
SRCS        = ./srcs/main.c \
              ./srcs/math/math_ray.c \
              ./srcs/math/math_vec3.c \
              ./srcs/math/math_vec3_1.c \
              ./srcs/math/math_vec3_2.c \
              ./srcs/math/math_pvec3.c \
              ./srcs/math/math_pvec3_1.c \
              ./srcs/math/math_pvec3_2.c \
              ./srcs/math/math_pvec3_3.c \
              ./srcs/math/math_pvec3_4.c \
              ./srcs/math/math_pvec3_5.c \
              ./srcs/math/math_pvec3_6.c \
              ./srcs/math/math_mat4.c \
              ./srcs/math/math_mat4_1.c \
              ./srcs/math/math_mat4_2.c \
              ./srcs/math/math_mat4_inv.c \
              ./srcs/math/math_mat4tf.c \
              ./srcs/math/math_mat4tf_1.c \
              ./srcs/math/math_mat4_print.c \
              ./srcs/math/math_utils.c \
              ./srcs/math/math_utils_1.c \
              ./srcs/math/math_utils_2.c \
              ./srcs/rt_parser/rt_parser_main.c \
              ./srcs/rt_parser/rt_parser_cache.c \
              ./srcs/rt_parser/rt_parser_error.c \
              ./srcs/rt_parser/rt_parser_scene.c \
              ./srcs/rt_parser/rt_parser_bonus.c \
              ./srcs/rt_parser/rt_parser_dict.c \
              ./srcs/rt_parser/rt_parser_memalloc.c \
              ./srcs/rt_parser/rt_parser_free.c \
              ./srcs/rt_parser/rt_parser_objs_main.c \
              ./srcs/rt_parser/rt_parser_objs_ab.c \
              ./srcs/rt_parser/rt_parser_objs_cb.c \
              ./srcs/rt_parser/rt_parser_objs_pl_sq.c \
              ./srcs/rt_parser/rt_parser_objs_sp_el.c \
              ./srcs/rt_parser/rt_parser_objs_quad_tr.c \
              ./srcs/rt_parser/rt_parser_objs_rc_ds.c \
              ./srcs/rt_parser/rt_parser_objs_py.c \
              ./srcs/rt_parser/rt_parser_objs_py_constr.c \
              ./srcs/rt_parser/rt_parser_objs_plus.c \
              ./srcs/rt_parser/rt_parser_objs_plus_1.c \
              ./srcs/rt_parser/rt_parser_utils.c \
              ./srcs/rt_parser/rt_parser_utils_1.c \
              ./srcs/core/savebmp_main.c \
              ./srcs/core/rt_core.c \
              ./srcs/core/rt_sampler.c \
              ./srcs/core/rt_shade_phong.c \
              ./srcs/core/rt_shade_backg_nmap.c \
              ./srcs/core/rt_process_pixel.c \
              ./srcs/core/rt_light.c \
              ./srcs/core/rt_camera.c \
              ./srcs/core/rt_camera_1.c \
              ./srcs/objects/aabb.c \
              ./srcs/objects/aabb_1.c \
              ./srcs/objects/cone.c \
              ./srcs/objects/cylinder.c \
              ./srcs/objects/cylinder_capped.c \
              ./srcs/objects/cylinder_capped_1.c \
              ./srcs/objects/disk.c \
              ./srcs/objects/ellipsoid.c \
              ./srcs/objects/group.c \
              ./srcs/objects/plane.c \
              ./srcs/objects/sphere.c \
              ./srcs/objects/square.c \
              ./srcs/objects/triangle.c \
              ./srcs/objects/rt_objects_utils.c \
              ./srcs/objects/rt_objects_utils_1.c \
              ./srcs/objects/textures_checkers.c \
              ./srcs/objects/textures_sphere.c \
              ./srcs/objects/textures_square.c \
              ./srcs/mlx/mlx_main.c \
              ./srcs/mlx/mlx_load_free.c \
              ./srcs/mlx/mlx_utils.c \
              ./srcs/mlx/mlx_hooks_main.c \
              ./srcs/mlx/mlx_hooks.c \
              ./srcs/mlx/mlx_hooks_1.c \
              ./srcs/mlx/mlx_hooks_2.c \
              ./srcs/utils/rt_utils.c \
              ./srcs/utils/color_filter.c \
              ./srcs/bmp/save_bmp.c
SRCS_M  =     ./srcs/core/rt_screen_driver_ot.c
SRCS_B  =     ./srcs/core/rt_screen_driver_mt.c
OBJS    = $(SRCS:.c=.o)
OBJS_M  = $(SRCS_M:.c=.o)
OBJS_B  = $(SRCS_B:.c=.o)
RM      = rm -f
CC      = gcc

.c.o:
	@${CC} ${FLAGS} -c $< -o ${<:.c=.o} -I${HEADERS}

$(NAME): $(OBJS) $(OBJS_M)
	@make all -C $(LIBFT_DIR)
	${CC} ${FLAGS} -I ${HEADERS} ${OBJS} ${OBJS_M} -L ${LIBFT_DIR} -lft -o ${NAME} -lm -I /usr/local/include/mlx.h \
	    -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

bonus: $(OBJS) $(OBJS_B)
	@make all -C $(LIBFT_DIR)
	${CC} ${FLAGS} -I ${HEADERS} ${OBJS} ${OBJS_B} -L ${LIBFT_DIR} -lft -o ${NAME} -lm -lpthread \
	    -I /usr/local/include/mlx.h -L /usr/local/lib -lmlx -framework OpenGL -framework AppKit

clean:
	$(RM) -f $(OBJS)
	$(RM) -f $(OBJS_M)
	$(RM) -f $(OBJS_B)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME) $(bonus)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re .c.o bonus

# -g -fsanitize=address
# -O2 -ffast-math
