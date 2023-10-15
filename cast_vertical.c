/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_vertical.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 02:07:34 by marvin            #+#    #+#             */
/*   Updated: 2023/10/03 02:07:34 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*extern int	mapx;
extern int	mapy;
extern char	map[];*/

void	init_vrays_value(t_mlx *mlx)
{
	float	ntan;

	ntan = -tan(mlx->rays.ray_angle);
	if (mlx->rays.ray_angle > P2 && mlx->rays.ray_angle < P3)
	{
		mlx->rays.ray_x = (((int)mlx->player.pos_x >> 6) << 6) - 0.0001;
		mlx->rays.ray_y = (mlx->player.pos_x - mlx->rays.ray_x)
			* ntan + mlx->player.pos_y;
		mlx->rays.xo = -64;
		mlx->rays.yo = -(mlx->rays.xo * ntan); 
	}
	if (mlx->rays.ray_angle < P2 || mlx->rays.ray_angle > P3)
	{
		mlx->rays.ray_x = (((int)mlx->player.pos_x >> 6) << 6) + 64;
		mlx->rays.ray_y = (mlx->player.pos_x - mlx->rays.ray_x)
			* ntan + mlx->player.pos_y;
		mlx->rays.xo = 64;
		mlx->rays.yo = -(mlx->rays.xo * ntan); 
	}
	if (mlx->rays.ray_angle == 0 || mlx->rays.ray_angle == PI)
	{
		mlx->rays.ray_y = mlx->player.pos_y;
		mlx->rays.ray_x = mlx->player.pos_x;
		mlx->rays.dof = 16;
	}
}

void	ft_get_vray_length(t_mlx *mlx)
{
	mlx->rays.mx = (int)(mlx->rays.ray_x) >> 6;
	mlx->rays.my = (int)(mlx->rays.ray_y) >> 6;
	if (mlx->rays.mx >= 500)
		mlx->rays.mx = 500;
	mlx->rays.mp = mlx->rays.my * mlx->pars.map_w + mlx->rays.mx;
	if (mlx->rays.mp >= 0 && mlx->rays.mp < mlx->pars.map_w
		* (mlx->pars.map_h + 1) && mlx->pars.map2[mlx->rays.mp] == '1')
	{
		mlx->rays.dof = 16;
	}
	else
	{
		mlx->rays.ray_x += mlx->rays.xo;
		mlx->rays.ray_y += mlx->rays.yo;
		mlx->rays.dof += 1;
	}
}

void	ft_cast_vertical(t_mlx *mlx)
{
	mlx->rays.dof = 0;
	init_vrays_value(mlx);
	while (mlx->rays.dof < 16)
		ft_get_vray_length(mlx);
	mlx->rays.vx = mlx->rays.ray_x;
	mlx->rays.vy = mlx->rays.ray_y;
	mlx->rays.distV = dist(mlx->player.pos_x, mlx->player.pos_y, mlx->rays.vx, mlx->rays.vy);
}
