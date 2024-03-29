# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: syakovle <syakovle@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/17 02:23:38 by syakovle          #+#    #+#              #
#    Updated: 2024/01/08 14:00:26 by syakovle         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D.a

CC = cc
AR = ar rcs
RM = rm -f
LIBFT = libft/libft.a
PRINTF = printf/ft_printf.a
MINILIBX = minilibx-linux/libmlx.a

FILES	=	main								\
			init								\
			init_utils							\
			keys								\
			keys_utils							\
			keys_utils_2						\
			display								\
			raycasting/cast_horizontal			\
			raycasting/cast_vertical			\
			raycasting/ray_info					\
			parsing/init_map					\
			parsing/init_map_utils				\
			parsing/parsing						\
			parsing/parsing_map					\
			parsing/parsing_fill_infos			\
			parsing/map_verif					\
			parsing/verif_args					\
			get_next_line/get_next_line_utils	\
			get_next_line/get_next_line			\
			render3d/render3d					\
			get/get								\
			get/get_utils						\
			free

SRCS_DIR = ./
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))

OBJS_DIR = ./
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))


.c.o: $(SRCS)
	$(CC) -g $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS)
	$(AR) $@ $(OBJS)
	@make all -C libft
	@make all -C printf
	@make all -C minilibx-linux
	$(CC) -g3 $(CFLAGS) $(NAME) minilibx-linux/libmlx.a -lm -lX11 -lXext $(PRINTF) $(LIBFT) -o cub3D

all: $(NAME)

clean:
	$(RM) $(OBJS)
	@make clean -C libft
	@make clean -C printf
	@make clean -C minilibx-linux

fclean: clean
	$(RM) $(NAME) cub3D cub3D.a
	@make fclean -C libft
	@make fclean -C printf
	@make clean -C minilibx-linux
	
re: clean all

.PHONY: all clean fclean re
