/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakovle <syakovle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 19:18:21 by syakovle          #+#    #+#             */
/*   Updated: 2023/10/26 19:38:54 by syakovle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	getdelta(t_mlx *mlx, int *delta_x_neg, int *delta_y_neg)
{
	*delta_x_neg = 1;
	*delta_y_neg = 1;
	if (mlx->player.delta_x < 0)
		*delta_x_neg = -1;
	if (mlx->player.delta_y < 0)
		*delta_y_neg = -1;
}

void	w_move(t_mlx *mlx, int delta_x_neg, int delta_y_neg)
{
	if (mlx->player.z == true)
	{
		if (mlx->pars.map[(int)floor(mlx->player.pos_y
					/ 64)][(int)floor((mlx->player.pos_x + mlx->player.delta_x)
				/ 64 + (0.35 * delta_x_neg))] != '1' &&
			mlx->pars.map[(int)floor(mlx->player.pos_y / 64)]
				[(int)floor((mlx->player.pos_x + mlx->player.delta_x)
					/ 64 + (0.35 * delta_x_neg))] != '1')
			mlx->player.pos_x += mlx->player.delta_x;
		if (mlx->pars.map[(int)floor((mlx->player.pos_y + mlx->player.delta_y)
					/ 64 + (0.35 * delta_y_neg))]
			[(int)floor(mlx->player.pos_x / 64)] != '1')
			mlx->player.pos_y += mlx->player.delta_y;
	}
}
