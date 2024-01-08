/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakovle <syakovle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 19:18:21 by syakovle          #+#    #+#             */
/*   Updated: 2023/10/27 18:34:2 by syakovle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	getdelta2(int *delta_x_neg, int *delta_y_neg, float angle)
{
	*delta_x_neg = 1;
	*delta_y_neg = 1;
	if (cos(angle) < 0)
		*delta_x_neg = -1;
	if (sin(angle) < 0)
		*delta_y_neg = -1;
}

void	d_move(t_mlx *mlx)
{
	float	rangle;
	int		delta_x_neg;
	int		delta_y_neg;

	rangle = mlx->player.angle + P2;
	if (rangle < 0)
		rangle += 2 * PI;
	if (rangle > 2 * PI)
		rangle -= 2 * PI;
	getdelta2(&delta_x_neg, &delta_y_neg, rangle);
	if (mlx->player.d == true)
	{
		if (mlx->pars.map[(int)floor(mlx->player.pos_y
					/ 64)][(int)floor((mlx->player.pos_x + cos(rangle))
				/ 64 + (0.2 * delta_x_neg))] != '1' &&
			mlx->pars.map[(int)floor(mlx->player.pos_y / 64)]
				[(int)floor((mlx->player.pos_x + cos(rangle))
					/ 64 + (0.2 * delta_x_neg))] != '1')
			mlx->player.pos_x += cos(rangle) * 2;
		if (mlx->pars.map[(int)floor((mlx->player.pos_y + sin(rangle))
					/ 64 + (0.2 * delta_y_neg))]
			[(int)floor(mlx->player.pos_x / 64)] != '1')
			mlx->player.pos_y += sin(rangle) * 2;
	}
}

void	a_move(t_mlx *mlx)
{
	float	rangle;
	int		delta_x_neg;
	int		delta_y_neg;

	rangle = mlx->player.angle + P2;
	if (rangle < 0)
		rangle += 2 * PI;
	if (rangle > 2 * PI)
		rangle -= 2 * PI;
	getdelta2(&delta_x_neg, &delta_y_neg, rangle);
	if (mlx->player.q == true)
	{
		if (mlx->pars.map[(int)floor(mlx->player.pos_y / 64)][(int)floor
			((mlx->player.pos_x - cos(rangle)) / 64
				- (0.2 * delta_x_neg))] != '1')
			mlx->player.pos_x -= cos(rangle) * 2;
		if (mlx->pars.map[(int)floor((mlx->player.pos_y - sin(rangle))
					/ 64 - (0.2 * delta_y_neg))][(int)
			floor(mlx->player.pos_x / 64)] != '1')
			mlx->player.pos_y -= sin(rangle) * 2;
	}
}

void	s_move(t_mlx *mlx)
{
	int		delta_x_neg;
	int		delta_y_neg;

	getdelta(mlx, &delta_x_neg, &delta_y_neg);
	if (mlx->player.s == true)
	{
		if (mlx->pars.map[(int)floor(mlx->player.pos_y / 64)][(int)floor
			((mlx->player.pos_x - mlx->player.delta_x) / 64
				- (0.2 * delta_x_neg))] != '1')
			mlx->player.pos_x -= mlx->player.delta_x;
		if (mlx->pars.map[(int)floor((mlx->player.pos_y - mlx->player.delta_y)
					/ 64 - (0.2 * delta_y_neg))][(int)
			floor(mlx->player.pos_x / 64)] != '1')
			mlx->player.pos_y -= mlx->player.delta_y;
	}
}

void	w_move(t_mlx *mlx)
{
	int		delta_x_neg;
	int		delta_y_neg;

	getdelta(mlx, &delta_x_neg, &delta_y_neg);
	if (mlx->player.z == true)
	{
		if (mlx->pars.map[(int)floor(mlx->player.pos_y
					/ 64)][(int)floor((mlx->player.pos_x + mlx->player.delta_x)
				/ 64 + (0.2 * delta_x_neg))] != '1' &&
			mlx->pars.map[(int)floor(mlx->player.pos_y / 64)]
				[(int)floor((mlx->player.pos_x + mlx->player.delta_x)
					/ 64 + (0.2 * delta_x_neg))] != '1')
			mlx->player.pos_x += mlx->player.delta_x * 2;
		if (mlx->pars.map[(int)floor((mlx->player.pos_y + mlx->player.delta_y)
					/ 64 + (0.2 * delta_y_neg))]
			[(int)floor(mlx->player.pos_x / 64)] != '1')
			mlx->player.pos_y += mlx->player.delta_y * 2;
	}
}
