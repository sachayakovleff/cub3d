/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:33:03 by marvin            #+#    #+#             */
/*   Updated: 2023/10/02 17:46:07 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "minilibx-linux/mlx.h"
# include "printf/ft_printf.h"
# include "libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdbool.h>
# define PI 3.1415926535
# define P2 PI / 2
# define P3 3 * PI / 2
# define DR 0.0174533
# include <math.h>
# include <stdio.h>
# include <X11/Xlib.h>

typedef struct s_player
{
	float	pos_y;
	float	pos_x;
	float	delta_x;
	float	delta_y;
	float	angle;
	bool	z;
	bool	q;
	bool	s;
	bool	d;
}				t_player;

typedef struct	s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct	s_rays
{
	int 	ray;
	int 	mx;
	int 	my;
	int		mp;
	int 	dof;
	float	ray_x;
	float	ray_y;
	float	ray_angle;
	float	xo;
	float	yo;
	
	float	distH;
	float	hx;
	float	hy;
	
	float	distV;
	float	vx;
	float	vy;
}				t_rays;

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
	t_rays		rays;
}				t_mlx;

void 	initimages(t_mlx *mlx);
void 	init(t_mlx *mlx);
int		ft_close(t_mlx *mlx);
void	ft_setmove(t_mlx *mlx);
int		handlekey(int key, t_mlx *mlx);
int 	handlekeyrelease(int key, t_mlx *mlx);
void 	editimage(t_data *data, int size_x, int size_y, int color);
int 	ft_display_player(t_mlx *mlx);
int 	ft_display_ground(t_mlx *mlx);
int		ft_display_map(t_mlx *mlx);
int		handleloop(t_mlx *mlx);
int 	draw_line(void *mlx, void *win, int beginX, int beginY, int endX, int endY, int color);
void	ft_draw_rays(t_mlx *mlx);
#endif