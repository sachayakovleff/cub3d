/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render3d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 18:08:16 by syakovle          #+#    #+#             */
/*   Updated: 2023/10/22 17:08:35 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	convertrgb(int color[3])
{
	return (((color[0] & 0xff) << 16)
		+ ((color[1] & 0xff) << 8) + (color[2] & 0xff));
}

int	isvalid(t_mlx *mlx)
{
	if (mlx->rays.ray_x <= 0 || mlx->rays.ray_y <= 0
		|| mlx->render3d.distance > 10000)
		return (-1);
	if (mlx->rays.ray_x / 64 > mlx->pars.map_w)
		return (-1);
	if (mlx->rays.ray_y / 64 > mlx->pars.map_h)
		return (-1);
	return (0);
}

int gettexture(t_mlx *mlx, int y)
{
	if (mlx->rays.distH < mlx->rays.distV)
	{
		if (mlx->rays.ray_angle > PI)
			return (gettexture_n(mlx, y, &mlx->img_n));
		else
			return (gettexture_s(mlx, y, &mlx->img_s));
	}
	else
	{
		if (mlx->rays.ray_angle > P2 && mlx->rays.ray_angle < P3)
			return (gettexture_w(mlx, y, &mlx->img_w));
		else
			return (gettexture_e(mlx, y, &mlx->img_e));
	}
}

void	set_pixels_by_line(t_mlx *mlx)
{
	int	y;

	y = 0;
	while (y++ <= mlx->win_y)
	{
		if (y < 0)
			continue ;
		else if ((y < mlx->render3d.wall_top_pixel && mlx->rays.ray_x > 0)
			|| (y < mlx->win_y / 2 && isvalid(mlx) == -1))
			my_mlx_pixel_put(&(mlx->img_3d), mlx->rays.ray
				* 1, y, convertrgb(mlx->pars.c_colors));
		else if ((y > mlx->render3d.wall_bottom_pixel && mlx->rays.ray_x > 0)
			|| (y >= mlx->win_y / 2 && isvalid(mlx) == -1))
			my_mlx_pixel_put(&(mlx->img_3d), mlx->rays.ray, 
				y, convertrgb(mlx->pars.f_colors));
		else
			my_mlx_pixel_put(&(mlx->img_3d), mlx->rays.ray,
				y, gettexture(mlx, y));
	}
}

void	edit_3d_image(t_mlx *mlx)
{
	mlx->render3d.projected_wall_h = (64 / mlx->render3d.distance)
		* ((mlx->win_x / 2) / tan((120 * (PI / 180)) / 2));
	mlx->render3d.wall_strip_h = (int)mlx->render3d.projected_wall_h;
	mlx->render3d.wall_top_pixel = (mlx->win_y / 2)
		- (mlx->render3d.wall_strip_h / 2) -20;
	mlx->render3d.wall_bottom_pixel = (mlx->win_y / 2)
		+ (mlx->render3d.wall_strip_h / 2) + 20;
	set_pixels_by_line(mlx);
}