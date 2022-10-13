# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aamajane <aamajane@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/04 15:10:36 by aamajane          #+#    #+#              #
#    Updated: 2022/10/13 23:12:43 by aamajane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	cub3D

BONUS	= 	cub3D_bonus

LIBFT	=	libft/libft.a

SRCS_M	=	mandatory/srcs/main.c \
			mandatory/srcs/checker.c \
			mandatory/srcs/create_game.c \
			mandatory/srcs/player_data.c \
			mandatory/srcs/mlx_hook.c \
			mandatory/srcs/render_frame.c \
			mandatory/srcs/player_update.c \
			mandatory/srcs/raycasting.c \
			mandatory/srcs/ray_horizontal_intercept.c \
			mandatory/srcs/ray_vertical_intercept.c \
			mandatory/srcs/ray_direction.c \
			mandatory/srcs/projection.c \
			mandatory/srcs/utils_checker.c \
			mandatory/srcs/utils_map.c \
			mandatory/srcs/utils_math.c \
			mandatory/srcs/get_next_line.c

OBJS_M	=	$(SRCS_M:.c=.o)

SRCS_B	=	bonus/srcs/main.c \
			bonus/srcs/checker.c \
			bonus/srcs/create_game.c \
			bonus/srcs/images_path.c \
			bonus/srcs/init_images.c \
			bonus/srcs/init_images_extra.c \
			bonus/srcs/player_data.c \
			bonus/srcs/mlx_hook.c \
			bonus/srcs/render_frame.c \
			bonus/srcs/player_update.c \
			bonus/srcs/raycasting.c \
			bonus/srcs/ray_horizontal_intercept.c \
			bonus/srcs/ray_vertical_intercept.c \
			bonus/srcs/ray_direction.c \
			bonus/srcs/projection.c \
			bonus/srcs/sprite.c \
			bonus/srcs/door_checker.c \
			bonus/srcs/door_rendering.c \
			bonus/srcs/enemy_rendering.c \
			bonus/srcs/weapon_rendering.c \
			bonus/srcs/minimap.c \
			bonus/srcs/utils_map.c \
			bonus/srcs/utils_math.c \
			bonus/srcs/utils_sprites.c \
			bonus/srcs/get_next_line.c

OBJS_B	=	$(SRCS_B:.c=.o)

CC		=	cc

CFLAGS	=	-Wall -Wextra -Werror

MLX		=	-lmlx -framework OpenGL -framework AppKit

MATH	=	-lm

LIB		=	ar -rcs

RM		=	rm -rf


all:		$(NAME)

$(NAME):	$(LIBFT) $(OBJS_M)
			@$(CC) $(CFLAGS) $(MLX) $(MATH) $(LIBFT) $(OBJS_M) -o $(NAME)

bonus:		$(BONUS)

$(BONUS):	$(LIBFT) $(OBJS_B)
			@$(CC) $(CFLAGS) $(MLX) $(MATH) $(LIBFT) $(OBJS_B) -o $(BONUS)

$(LIBFT):
			@cd libft && make

.c.o:
			@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

clean:
			@$(RM) $(LIBFT) $(OBJS_M) $(OBJS_B)
			@cd libft && make clean

fclean:		clean
			@$(RM) $(NAME) $(BONUS)

re:			fclean all

.PHONY:		all bonus clean fclean re
