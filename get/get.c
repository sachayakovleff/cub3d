/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakovle <syakovle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:09:36 by syakovle          #+#    #+#             */
/*   Updated: 2023/10/20 18:26:00 by syakovle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	getwall(t_mlx *mlx, int x, int y)
{
	if ((int)(mlx->player.pos_x / 64 + x / 30.) < 0 || (int)(mlx->player.pos_x
		/ 64 + x / 30.) >= ft_strlen(mlx->pars.map[0]))
		return (0xFF000000);
	if ((int)(mlx->player.pos_y / 64 + y / 30.) < 0 || (int)(mlx->player.pos_y
		/ 64 + y / 30.) >= mlx->pars.map_h + 1)
		return (0x00000000);
	if (mlx->pars.map[(int)(mlx->player.pos_y / 64 + y / 30.)][(int)
			(mlx->player.pos_x / 64 + x / 30.)] == '1')
		return (0x0000FF00);
	if (mlx->pars.map[(int)(mlx->player.pos_y / 64 + y / 30.)][(int)
			(mlx->player.pos_x / 64 + x / 30.)] == '0')
		return (0x000000FF);
	return (0x00FF0000);
}

int	gettexture(t_mlx *mlx, int y, t_data *data)
{
	char	*dst;
	float	renderheight;
	float	rendery;
	float	renderwidth;
	float	width;

	renderheight = mlx->render3d.wall_bottom_pixel
		- mlx->render3d.wall_top_pixel;
	rendery = 1500 * ((y - mlx->render3d.wall_top_pixel) / renderheight);
	renderwidth = fmod(mlx->rays.ray_x, 64) / 64;
	width = renderwidth * 1500;
	dst = data->addr + ((int) rendery * data->line_length
			+ (int) width * (data->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

int	gettexture2(t_mlx *mlx, int y, t_data *data)
{
	char	*dst;
	float	renderheight;
	float	rendery;
	float	renderwidth;
	float	width;

	renderheight = (mlx->render3d.wall_bottom_pixel
			- mlx->render3d.wall_top_pixel);
	rendery = 1500 * ((y - mlx->render3d.wall_top_pixel) / renderheight);
	renderwidth = fmod(mlx->rays.ray_y, 64) / 64;
	width = renderwidth * 1500;
	dst = data->addr + (((int) rendery) * data->line_length
			+ (int)width * (data->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}
