/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakovle <syakovle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:03:08 by syakovle          #+#    #+#             */
/*   Updated: 2023/10/26 19:38:41 by syakovle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	mlx->rays.ray_angle = mlx->player.angle;
	mlx->rays.ray = 0;
	mlx->rays.ray_angle = mlx->player.angle - (DR * 30);
	while (mlx->rays.ray < 1200)
	{
		get_ray_angle(mlx);
		ft_cast_vertical(mlx);
		ft_cast_horizontal(mlx);
		get_ray_collision(mlx);
		edit_3d_image(mlx);
		mlx->rays.ray++;
		mlx->rays.ray_angle += (DR / 20);
		if (mlx->rays.ray_angle < 0)
			mlx->rays.ray_angle += 2 * PI;
		if (mlx->rays.ray_angle > 2 * PI)
			mlx->rays.ray_angle -= 2 * PI;
	}
}
