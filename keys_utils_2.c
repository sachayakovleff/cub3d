/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_utils_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakovle <syakovle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:33:32 by syakovle          #+#    #+#             */
/*   Updated: 2023/11/07 18:36:59 by syakovle         ###   ########.fr       */
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
