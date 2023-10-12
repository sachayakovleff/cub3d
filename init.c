/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:33:40 by marvin            #+#    #+#             */
/*   Updated: 2023/10/02 17:33:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	imginit(t_data *data, t_mlx *mlx, int img_sizex, int img_sizey)
{
	data->img = mlx_new_image(mlx->mlx_ptr, img_sizex, img_sizey);
	data->addr = mlx_get_data_addr(data->img, &(data->bits_per_pixel),
			&(data->line_length), &(data->endian));
}

void	initimages(t_mlx *mlx)
{
	imginit(&mlx->img_font, mlx, 1920, 1080);
	imginit(&mlx->img_ground, mlx, 62, 62);
	editimage(&mlx->img_ground, 62, 62, 0x000000FF);
	imginit(&mlx->img_wall, mlx, 62, 62);
	editimage(&mlx->img_wall, 62, 62, 0x0000FF00);
	imginit(&mlx->img_player, mlx, 16, 16);
	editimage(&mlx->img_player, 8, 8, 0xFF000000);
}

void	init(t_mlx *mlx)
{
	mlx->player.pos_x = 290;
	mlx->player.pos_y = 500;
	mlx->player.z = false;
	mlx->player.q = false;
	mlx->player.s = false;
	mlx->player.d = false;
	mlx->win_x = 1080;
	mlx->win_y = 1080;
	mlx->mlx_ptr = mlx_init();
	mlx->player.delta_x = 1;
	mlx->player.delta_y = 0;
	mlx->player.angle = 0;
	initimages(mlx);
}
