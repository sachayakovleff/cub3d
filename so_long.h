/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:57:07 by syakovle          #+#    #+#             */
/*   Updated: 2023/09/23 20:25:52 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "minilibx-linux/mlx.h"
# include "printf/ft_printf.h"
# include "libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdbool.h>

typedef struct s_player
{
	float	pos_y;
	float	pos_x;
	float	delta_x;
	float	delta_y;
	bool	z;
	bool	q;
	bool	s;
	bool	d;
}				t_player;

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	int 		win_x;
	int 		win_y;
	t_data		img_font;
	t_data		img_wall;
	t_data		img_ground;
	t_data		img_player;
	t_player	player;
}				t_mlx;

#endif