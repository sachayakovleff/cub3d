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
		mlx->player.angle -= 0.02;
		if (mlx->player.angle < 0)
			mlx->player.angle += 2 * PI;
		mlx->player.delta_x = cos(mlx->player.angle);
		mlx->player.delta_y = sin(mlx->player.angle);
	}
	if (mlx->player.d == true)
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
	int		delta_x_neg;
	int		delta_y_neg;

	getdelta(mlx, &delta_x_neg, &delta_y_neg);
	w_move(mlx, delta_x_neg, delta_y_neg);
	if (mlx->player.s == true)
	{
		if (mlx->pars.map[(int)floor(mlx->player.pos_y / 64)][(int)floor
			((mlx->player.pos_x - mlx->player.delta_x) / 64
				- (0.35 * delta_x_neg))] != '1')
			mlx->player.pos_x -= mlx->player.delta_x;
		if (mlx->pars.map[(int)floor((mlx->player.pos_y - mlx->player.delta_y)
					/ 64 - (0.35 * delta_y_neg))][(int)
			floor(mlx->player.pos_x / 64)] != '1')
			mlx->player.pos_y -= mlx->player.delta_y;
	}
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
	return (0);
}
