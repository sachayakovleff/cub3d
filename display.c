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

int	ft_display_map(t_mlx *mlx, int x, int y)
{
	int		i;
	int		j;
	t_data	map;

	x = y;
	y = x;
	i = -250;
	j = -250;
	imginit(&map, mlx, 500, 500);
	while (j < 250)
	{
		while (i < 250)
		{
			my_mlx_pixel_put(&map, i + 250, j + 250,
				getwall(mlx, i - 8, j - 28));
			i++;
		}
		i = -250;
		j++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr,
		map.img, 0, mlx->win_y / 4);
	mlx_destroy_image(mlx->mlx_ptr, map.img);
	return (0);
}

int	ft_display_player(t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_player.img,
		250, mlx->win_y / 2);
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
	ft_display_map(mlx, 0, 0);
	ft_display_player(mlx);
	if (mlx->img_3d.img == NULL)
		return (printf("error: Couldn't load img_3d\n"),
			mlx_loop_end(mlx->mlx_ptr));
	mlx->img_3d.addr = mlx_get_data_addr(mlx->img_3d.img,
			&(mlx->img_3d.bits_per_pixel),
			&(mlx->img_3d.line_length), &mlx->img_3d.endian);
	ft_draw_rays(mlx);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr,
		mlx->img_3d.img, 500, 0);
	ft_setmove(mlx);
	return (0);
}
