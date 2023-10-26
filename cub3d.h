/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakovle <syakovle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:33:03 by marvin            #+#    #+#             */
/*   Updated: 2023/10/26 19:44:10 by syakovle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "minilibx-linux/mlx.h"
# include "printf/ft_printf.h"
# include "libft/libft.h"
# include "parsing/init_map.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdbool.h>
# define PI 3.1415926535
# define P2 1.570796327
# define P3 4.712388981
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

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		width;
	int		height;
	int		endian;
}				t_data;

typedef struct s_rays
{
	int		ray;
	int		mx;
	int		my;
	int		mp;
	int		dof;
	float	ray_x;
	float	ray_y;
	float	ray_angle;
	float	xo;
	float	yo;
	float	disth;
	float	hx;
	float	hy;
	float	distv;
	float	vx;
	float	vy;
}				t_rays;

typedef struct s_render_3d
{
	float	distance;
	float	projected_wall_h;
	int		wall_strip_h;
	int		wall_top_pixel;
	int		wall_bottom_pixel;
}				t_render_3d;

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			win_x;
	int			win_y;
	t_pars		pars;
	t_data		img_empty;
	t_data		img_w;
	t_data		img_e;
	t_data		img_s;
	t_data		img_n;
	t_data		img_3d;
	t_data		img_font;
	t_data		img_wall;
	t_data		img_ground;
	t_data		img_player;
	t_player	player;
	t_rays		rays;
	t_render_3d	render3d;
}				t_mlx;

void	getdelta(t_mlx *mlx, int *delta_x_neg, int *delta_y_neg);
void	w_move(t_mlx *mlx, int delta_x_neg, int delta_y_neg);
void	ft_free(t_mlx *mlx);
void	initimages(t_mlx *mlx);
void	init(t_mlx *mlx);
int		ft_close(t_mlx *mlx);
void	ft_setmove(t_mlx *mlx);
int		handlekey(int key, t_mlx *mlx);
int		handlekeyrelease(int key, t_mlx *mlx);
void	editimage(t_data *data, int size_x, int size_y, int color);
int		ft_display_player(t_mlx *mlx);
int		ft_display_ground(t_mlx *mlx);
int		ft_display_map(t_mlx *mlx, int x, int y);
int		handleloop(t_mlx *mlx);
void	ft_draw_rays(t_mlx *mlx);
void	ft_get_hray_length(t_mlx *mlx);
void	init_hrays_values(t_mlx *mlx);
void	ft_cast_horizontal(t_mlx *mlx);
float	dist(float ax, float ay, float bx, float by);
void	ft_cast_vertical(t_mlx *mlx);
void	get_ray_angle(t_mlx *mlx);
void	imginit(t_data *data, t_mlx *mlx, int img_sizex, int img_sizey);
void	get_ray_collision(t_mlx *mlx);
int		parsing_main(int argc, char **argv, t_mlx *mlx);
void	free_pars_struct(t_pars *pars);
void	edit_3d_image(t_mlx *mlx);
int		gettexture_n(t_mlx *mlx, int y, t_data *data);
int		gettexture_w(t_mlx *mlx, int y, t_data *data);
int		gettexture_e(t_mlx *mlx, int y, t_data *data);
int		gettexture_s(t_mlx *mlx, int y, t_data *data);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		getwall(t_mlx *mlx, int x, int y);
int		ft_display_map(t_mlx *mlx, int x, int y);

#endif