/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:09:36 by syakovle          #+#    #+#             */
/*   Updated: 2023/10/31 01:29:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	getletter(char value)
{
	return (value == 'N' || value == 'S' || value == 'E' || value == 'W');
}

int	getwall(t_mlx *mlx, int x, int y)
{
	if ((int)(mlx->player.pos_x / 64 + x / 30.) < 0 || (int)(mlx->player.pos_x
		/ 64 + x / 30.) >= ft_strlen(mlx->pars.map[0]))
		return (0xFF000000);
	if ((int)(mlx->player.pos_y / 64 + y / 30.) < 0 || (int)(mlx->player.pos_y
		/ 64 + y / 30.) >= mlx->pars.map_h + 1)
		return (0x00660000);
	if (mlx->pars.map[(int)(mlx->player.pos_y / 64 + y / 30.)][(int)
			(mlx->player.pos_x / 64 + x / 30.)] == '1')
		return (0x0000FF00);
	if (mlx->pars.map[(int)(mlx->player.pos_y / 64 + y / 30.)][(int)
			(mlx->player.pos_x / 64 + x / 30.)] == '0')
		return (0x000000FF);
	if (getletter(mlx->pars.map[(int)(mlx->player.pos_y / 64 + y / 30.)][(int)
		(mlx->player.pos_x / 64 + x / 30.)]) == true)
		return (0x0000FFFF);
	return (0x00FF0000);
}

int	gettexture_n(t_mlx *mlx, int y, t_data *data)
{
	char	*dst;
	float	renderheight;
	float	rendery;
	float	renderwidth;
	float	width;

	renderheight = mlx->render3d.wall_bottom_pixel
		- mlx->render3d.wall_top_pixel;
	rendery = mlx->pars.n_t.y_size * (
			(y - mlx->render3d.wall_top_pixel) / renderheight);
	renderwidth = fmod(mlx->rays.ray_x, 64) / 64;
	width = renderwidth * mlx->pars.n_t.x_size;
	dst = data->addr + ((int) rendery * data->line_length
			+ (int) width * (data->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

int	gettexture_w(t_mlx *mlx, int y, t_data *data)
{
	char	*dst;
	float	renderheight;
	float	rendery;
	float	renderwidth;
	float	width;

	renderheight = (mlx->render3d.wall_bottom_pixel
			- mlx->render3d.wall_top_pixel);
	rendery = mlx->pars.w_t.y_size * (
			(y - mlx->render3d.wall_top_pixel) / renderheight);
	renderwidth = fmod(mlx->rays.ray_y, 64) / 64;
	width = renderwidth * mlx->pars.w_t.x_size;
	width = mlx->pars.w_t.x_size - width;
	dst = data->addr + (((int) rendery) * data->line_length
			+ (int)width * (data->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

int	gettexture_s(t_mlx *mlx, int y, t_data *data)
{
	char	*dst;
	float	renderheight;
	float	rendery;
	float	renderwidth;
	float	width;

	renderheight = mlx->render3d.wall_bottom_pixel
		- mlx->render3d.wall_top_pixel;
	rendery = mlx->pars.s_t.y_size * (
			(y - mlx->render3d.wall_top_pixel) / renderheight);
	renderwidth = fmod(mlx->rays.ray_x, 64) / 64;
	width = renderwidth * mlx->pars.s_t.x_size;
	width = mlx->pars.s_t.x_size - width;
	dst = data->addr + ((int) rendery * data->line_length
			+ (int) width * (data->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

int	gettexture_e(t_mlx *mlx, int y, t_data *data)
{
	char	*dst;
	float	renderheight;
	float	rendery;
	float	renderwidth;
	float	width;

	renderheight = (mlx->render3d.wall_bottom_pixel
			- mlx->render3d.wall_top_pixel);
	rendery = mlx->pars.e_t.y_size * (
			(y - mlx->render3d.wall_top_pixel) / renderheight);
	renderwidth = fmod(mlx->rays.ray_y, 64) / 64;
	width = renderwidth * mlx->pars.e_t.x_size;
	dst = data->addr + (((int) rendery) * data->line_length
			+ (int)width * (data->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}
