/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:43:01 by marvin            #+#    #+#             */
/*   Updated: 2023/10/02 17:43:01 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_display_player(t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_player.img,
		mlx->player.pos_x, mlx->player.pos_y);
	draw_line(mlx->mlx_ptr, mlx->win_ptr, mlx->player.pos_x, mlx->player.pos_y,
		mlx->player.pos_x + mlx->player.delta_x * 20, mlx->player.pos_y
		+ mlx->player.delta_y * 20, 0x00FF0000);
	return (0);
}

int	ft_display_ground(t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr,
		mlx->img_font.img, 0, 0);
	return (0);
}

int	handleloop(t_mlx *mlx)
{
	ft_display_map(mlx);
	ft_display_player(mlx);
	ft_draw_rays(mlx);
	ft_setmove(mlx);
	return (0);
}
