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
	if (mlx->player.l == true)
	{
		mlx->player.angle -= 0.02;
		if (mlx->player.angle < 0)
			mlx->player.angle += 2 * PI;
		mlx->player.delta_x = cos(mlx->player.angle);
		mlx->player.delta_y = sin(mlx->player.angle);
	}
	if (mlx->player.r == true)
	{
		mlx->player.angle += 0.02;
		if (mlx->player.angle > 2 * PI)
			mlx->player.angle -= 2 * PI;
		mlx->player.delta_x = cos(mlx->player.angle);
		mlx->player.delta_y = sin(mlx->player.angle);
	}
}

void	ft_setmove(t_mlx *mlx)
{
	w_move(mlx);
	s_move(mlx);
	a_move(mlx);
	d_move(mlx);
	handle_angle(mlx);
}

int	handlekey(int key, t_mlx *mlx)
{
	if (key == 122 || key == 119)
		mlx->player.z = true;
	if (key == 113 || key == 97)
		mlx->player.q = true;
	if (key == 115)
		mlx->player.s = true;
	if (key == 100)
		mlx->player.d = true;
	if (key == 65361)
		mlx->player.l = true;
	if (key == 65363)
		mlx->player.r = true;
	if (key == 65307)
	{
		mlx_loop_end(mlx->mlx_ptr);
		return (0);
	}
	return (0);
}

int	handlekeyrelease(int key, t_mlx *mlx)
{
	if (key == 122 || key == 119)
		mlx->player.z = false;
	if (key == 113 || key == 97)
		mlx->player.q = false;
	if (key == 115)
		mlx->player.s = false;
	if (key == 100)
		mlx->player.d = false;
	if (key == 65361)
		mlx->player.l = false;
	if (key == 65363)
		mlx->player.r = false;
	return (0);
}
