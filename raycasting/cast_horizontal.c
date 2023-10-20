/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_horizontal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 01:56:26 by marvin            #+#    #+#             */
/*   Updated: 2023/10/03 01:56:26 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

/*extern int	mapx;
extern int	mapy;
extern char	map[];*/

float	dist(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	ft_get_hray_length(t_mlx *mlx)
{
	mlx->rays.mx = (int)(mlx->rays.ray_x) >> 6;
	mlx->rays.my = (int)(mlx->rays.ray_y) >> 6;
	if (mlx->rays.mx >= 500)
		mlx->rays.mx = 500;
	mlx->rays.mp = mlx->rays.my * mlx->pars.map_w + mlx->rays.mx;
	if (mlx->rays.mp >= 0 && mlx->rays.mp < mlx->pars.map_w * (mlx->pars.map_h + 1)
		&& mlx->pars.map2[mlx->rays.mp] == '1')
	{
		mlx->rays.hx = mlx->rays.ray_x;
		mlx->rays.hy = mlx->rays.ray_y;
		mlx->rays.distH = dist(mlx->player.pos_x, mlx->player.pos_y,
				mlx->rays.hx, mlx->rays.hy);
		mlx->rays.dof = 16;
	}
	else
	{
		mlx->rays.ray_x += mlx->rays.xo;
		mlx->rays.ray_y += mlx->rays.yo;
		mlx->rays.dof += 1;
	}
}

void	init_hrays_values(t_mlx *mlx)
{
	float	atan;

	atan = -1 / tan(mlx->rays.ray_angle);
	if (mlx->rays.ray_angle > PI)
	{
		mlx->rays.ray_y = (((int)mlx->player.pos_y >> 6) << 6) - 0.0001;
		mlx->rays.ray_x = (mlx->player.pos_y - mlx->rays.ray_y)
			* atan + mlx->player.pos_x;
		mlx->rays.yo = -64;
		mlx->rays.xo = -(mlx->rays.yo * atan); 
	}
	if (mlx->rays.ray_angle < PI)
	{
		mlx->rays.ray_y = (((int)mlx->player.pos_y >> 6) << 6) + 64;
		mlx->rays.ray_x = (mlx->player.pos_y - mlx->rays.ray_y)
			* atan + mlx->player.pos_x;
		mlx->rays.yo = 64;
		mlx->rays.xo = -(mlx->rays.yo * atan); 
	}
	if (mlx->rays.ray_angle == 0 || mlx->rays.ray_angle == PI)
	{
		mlx->rays.ray_x = mlx->player.pos_x;
		mlx->rays.ray_y = mlx->player.pos_y;
		mlx->rays.dof = 16;
	}
}

void	ft_cast_horizontal(t_mlx *mlx)
{
	mlx->rays.dof = 0;
	init_hrays_values(mlx);
	while (mlx->rays.dof < 16)
		ft_get_hray_length(mlx);
	mlx->rays.hx = mlx->rays.ray_x;
	mlx->rays.hy = mlx->rays.ray_y;
	mlx->rays.distH = dist(mlx->player.pos_x, mlx->player.pos_y, mlx->rays.hx, mlx->rays.hy);	
}
