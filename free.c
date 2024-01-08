/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakovle <syakovle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 17:59:28 by syakovle          #+#    #+#             */
/*   Updated: 2023/11/07 17:55:00 by syakovle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_destroy_image(void *mlx_ptr, void *data)
{
	if (mlx_ptr != NULL && data != NULL)
		mlx_destroy_image(mlx_ptr, data);
}

void	ft_free(t_mlx *mlx)
{
	if (mlx->mlx_ptr != NULL && mlx->win_ptr != NULL)
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	ft_destroy_image(mlx->mlx_ptr, mlx->img_e.img);
	ft_destroy_image(mlx->mlx_ptr, mlx->img_n.img);
	ft_destroy_image(mlx->mlx_ptr, mlx->img_s.img);
	ft_destroy_image(mlx->mlx_ptr, mlx->img_w.img);
	ft_destroy_image(mlx->mlx_ptr, mlx->img_empty.img);
	ft_destroy_image(mlx->mlx_ptr, mlx->img_ground.img);
	ft_destroy_image(mlx->mlx_ptr, mlx->img_wall.img);
	ft_destroy_image(mlx->mlx_ptr, mlx->img_font.img);
	ft_destroy_image(mlx->mlx_ptr, mlx->img_player.img);
	ft_destroy_image(mlx->mlx_ptr, mlx->amontign.img);
	ft_destroy_image(mlx->mlx_ptr, mlx->syakovle.img);
	if (mlx->mlx_ptr != NULL)
	{
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
	}
}
