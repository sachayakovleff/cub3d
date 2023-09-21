/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:07:23 by syakovle          #+#    #+#             */
/*   Updated: 2023/09/21 00:18:32 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>
#include <X11/Xlib.h>

int	ft_close(t_mlx *mlx)
{
	ft_printf("closed \n");
	mlx_loop_end(mlx->mlx_ptr);
	return (0);
}

void	ft_setmove(t_mlx *mlx)
{
	if (mlx->player.z == true)
	{
		mlx->player.pos_y -= 1;
	}
	if (mlx->player.q == true)
	{
		mlx->player.pos_x -= 1;
	}
	if (mlx->player.s == true)
	{
		mlx->player.pos_y += 1;
	}
	if (mlx->player.d == true)
	{
		mlx->player.pos_x += 1;
	}
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

int handlekeyrelease(int key, t_mlx *mlx)
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

int ft_display_player(t_mlx *mlx)
{
	mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, mlx->player.pos_x, mlx->player.pos_y, 0x000000FF);
	mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, mlx->player.pos_x + 1, mlx->player.pos_y, 0x000000FF);
	mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, mlx->player.pos_x + 2, mlx->player.pos_y, 0x000000FF);
	mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, mlx->player.pos_x + 2, mlx->player.pos_y + 1, 0x000000FF);
	mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, mlx->player.pos_x + 1, mlx->player.pos_y + 2, 0x000000FF);
	mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, mlx->player.pos_x + 1, mlx->player.pos_y + 1, 0x000000FF);
	mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, mlx->player.pos_x, mlx->player.pos_y + 1, 0x000000FF);
	mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, mlx->player.pos_x, mlx->player.pos_y + 2, 0x000000FF);

	return (0);
}

int ft_display_ground(t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_font.img, 0, 0);
	return (0);
}

int	ft_display_walls(t_mlx *mlx)
{
	mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, 50, 100, 0x0000FF00);
	return (0);
}

int	handleloop(t_mlx *mlx)
{
	ft_display_ground(mlx);
	ft_setmove(mlx);
	ft_display_player(mlx);
	ft_display_walls(mlx);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main(int ac, char **av)
{
	t_mlx	mlx;

	(void) ac;
	(void) av;
	int win_x = 0;
	int win_y = 0;
	mlx.player.pos_x = 50;
	mlx.player.pos_y = 50;
	mlx.player.z = false;
	mlx.player.q = false;
	mlx.player.s = false;
	mlx.player.d = false;
	mlx.win_x = 1080;
	mlx.win_y = 1080;
	mlx.mlx_ptr = mlx_init();
	mlx.img_font.img = mlx_new_image(mlx.mlx_ptr, 1920, 1080);
	mlx.img_font.addr = mlx_get_data_addr(mlx.img_font.img, &mlx.img_font.bits_per_pixel, &mlx.img_font.line_length,
								&mlx.img_font.endian);
    while (win_y < 1080)
	{
        while (win_x < 1920)
        {
        	my_mlx_pixel_put(&mlx.img_font, win_x, win_y, 0x00000000);
            win_x++;
        }
        win_x = 0;
        win_y++;
    }
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, mlx.win_x, mlx.win_y, "cub3d");
	mlx_hook(mlx.win_ptr, 17, 1L << 17, ft_close, &mlx);
	mlx_hook(mlx.win_ptr, KeyPress, KeyPressMask, handlekey, &mlx);
	mlx_hook(mlx.win_ptr, KeyRelease, KeyReleaseMask, handlekeyrelease, &mlx);
	mlx_loop_hook(mlx.mlx_ptr, handleloop, &mlx);
	mlx_loop(mlx.mlx_ptr);
}
