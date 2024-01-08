/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakovle <syakovle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:03:08 by syakovle          #+#    #+#             */
/*   Updated: 2024/01/08 15:14:11 by syakovle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <math.h>

void	get_ray_angle(t_mlx *mlx)
{
	if (mlx->rays.ray_angle < 0)
		mlx->rays.ray_angle += 2 * PI;
	if (mlx->rays.ray_angle > 2 * PI)
		mlx->rays.ray_angle -= 2 * PI;
	mlx->rays.disth = 100000;
	mlx->rays.distv = 100000;
}

void	get_ray_collision(t_mlx *mlx)
{
	if (mlx->rays.disth > mlx->rays.distv)
	{
		mlx->rays.ray_x = mlx->rays.vx;
		mlx->rays.ray_y = mlx->rays.vy;
		mlx->render3d.distance = mlx->rays.distv
			* cos(mlx->rays.ray_angle - mlx->player.angle);
	}
	if (mlx->rays.disth < mlx->rays.distv)
	{
		mlx->rays.ray_x = mlx->rays.hx;
		mlx->rays.ray_y = mlx->rays.hy;
		mlx->render3d.distance = mlx->rays.disth
			* cos(mlx->rays.ray_angle - mlx->player.angle);
	}
}

void	ft_draw_rays(t_mlx *mlx)
{
	mlx->rays.ray = 0;
	mlx->rays.ray_angle = mlx->player.angle 
		+ atan((mlx->rays.ray - 1400 / 2)
			/ ((mlx->win_x / 2) / tan((120 * (M_PI / 180)) / 2)));
	while (mlx->rays.ray < 1400)
	{
		get_ray_angle(mlx);
		ft_cast_vertical(mlx);
		ft_cast_horizontal(mlx);
		get_ray_collision(mlx);
		edit_3d_image(mlx);
		mlx->rays.ray++;
		mlx->rays.ray_angle += DR / 32;
		mlx->rays.ray_angle = mlx->player.angle
		 	+ atan((mlx->rays.ray - 1400 / 2)
		 		/ ((mlx->win_x / 2) / tan((120 * (M_PI / 180)) / 2)));
		if (mlx->rays.ray_angle < 0)
			mlx->rays.ray_angle += 2 * M_PI;
		if (mlx->rays.ray_angle > 2 * M_PI)
			mlx->rays.ray_angle -= 2 * M_PI;
	}
}
