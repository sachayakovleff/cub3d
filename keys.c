/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:35:29 by marvin            #+#    #+#             */
/*   Updated: 2023/10/02 17:35:29 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_close(t_mlx *mlx)
{
	ft_printf("closed \n");
	mlx_loop_end(mlx->mlx_ptr);
	return (0);
}

void	handle_angle(t_mlx *mlx)
{
	if (mlx->player.q == true)
	{
		mlx->player.angle -= 0.005;
		if (mlx->player.angle < 0)
			mlx->player.angle += 2 * PI;
		mlx->player.delta_x = cos(mlx->player.angle);
		mlx->player.delta_y = sin(mlx->player.angle);
	}
	if (mlx->player.d == true)
	{
		mlx->player.angle += 0.005;
		if (mlx->player.angle > 2 * PI)
			mlx->player.angle -= 2 * PI;
		mlx->player.delta_x = cos(mlx->player.angle);
		mlx->player.delta_y = sin(mlx->player.angle);
	}
}

void	ft_setmove(t_mlx *mlx)
{
	int	pos_x = (int)floor(mlx->player.pos_x / 64);
	int	pos_y = (int)floor(mlx->player.pos_y / 64);
	int	delta_x_neg = 1;
	int	delta_y_neg = 1;
	if (mlx->player.delta_x < 0)
		delta_x_neg = -1;
	if (mlx->player.delta_y < 0)
		delta_y_neg = -1;

	if (mlx->player.z == true)
	{
		if (map[((int)floor((mlx->player.pos_x + mlx->player.delta_x / 2) / 64 + (0.2 * delta_x_neg)) + pos_y * 8)] != '1')
			mlx->player.pos_x += mlx->player.delta_x / 2;
		if (map[((int)floor((mlx->player.pos_y + mlx->player.delta_y / 2) / 64 + (0.2 * delta_y_neg)) * 8 + pos_x)] != '1')
			mlx->player.pos_y += mlx->player.delta_y / 2;
	}
	if (mlx->player.s == true)
	{
		if (map[((int)floor((mlx->player.pos_x - mlx->player.delta_x / 2) / 64 - (0.2 * delta_x_neg)) + pos_y * 8)] != '1')
			mlx->player.pos_x -= mlx->player.delta_x / 2;
		if (map[((int)floor((mlx->player.pos_y - mlx->player.delta_y / 2) / 64 - (0.2 * delta_y_neg)) * 8 + pos_x)] != '1')
			mlx->player.pos_y -= mlx->player.delta_y / 2;
	}
	handle_angle(mlx);
}

int	handlekey(int key, t_mlx *mlx)
{
	if (key == 122)
		mlx->player.z = true;
	if (key == 113)
		mlx->player.q = true;
	if (key == 115)
		mlx->player.s = true;
	if (key == 100)
		mlx->player.d = true;
	if (key == 65307)
	{
		mlx_loop_end(mlx->mlx_ptr);
		return (0);
	}
	return (0);
}

int	handlekeyrelease(int key, t_mlx *mlx)
{
	if (key == 122)
		mlx->player.z = false;
	if (key == 113)
		mlx->player.q = false;
	if (key == 115)
		mlx->player.s = false;
	if (key == 100)
		mlx->player.d = false;
	return (0);
}
