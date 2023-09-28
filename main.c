/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 15:07:23 by syakovle          #+#    #+#             */
/*   Updated: 2023/09/28 14:44:30 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include <stdio.h>
#include <X11/Xlib.h>



int mapx = 8;
int mapy = 8;
int pixelsize = 64;

int map[] = 
{
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1, 0, 1,
	1, 0, 0, 0, 1, 1, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
};


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
		mlx->player.pos_x += mlx->player.delta_x;
		mlx->player.pos_y += mlx->player.delta_y;
	}
	if (mlx->player.q == true)
	{
		mlx->player.angle -= 0.005;
		if (mlx->player.angle < 0)
			mlx->player.angle += 2 * PI;
		mlx->player.delta_x = cos(mlx->player.angle);
		mlx->player.delta_y = sin(mlx->player.angle);
	}
	if (mlx->player.s == true)
	{
		mlx->player.pos_x -= mlx->player.delta_x;
		mlx->player.pos_y -= mlx->player.delta_y;
	}
	if (mlx->player.d == true)
	{
		mlx->player.angle += 0.005;
		if (mlx->player.angle > 2 * PI )
			mlx->player.angle -= 2 * PI;
		mlx->player.delta_x = cos(mlx->player.angle);
		mlx->player.delta_y = sin(mlx->player.angle);
	}
	printf("angle: %f\n delta_x : %f\n delta_y : %f\n", mlx->player.angle, mlx->player.delta_x, mlx->player.delta_y);
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

int draw_line(void *mlx, void *win, int beginX, int beginY, int endX, int endY, int color)
{
	double deltaX = endX - beginX;
	double deltaY = endY - beginY;
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	double pixelX = beginX;
	double pixelY = beginY;
	while (pixels)
	{
    	mlx_pixel_put(mlx, win, pixelX, pixelY, color);
    	pixelX += deltaX;
    	pixelY += deltaY;
    	--pixels;
	}
	return (0);
}

int ft_display_player(t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_player.img, mlx->player.pos_x, mlx->player.pos_y);

	draw_line(mlx->mlx_ptr, mlx->win_ptr, mlx->player.pos_x, mlx->player.pos_y, mlx->player.pos_x + mlx->player.delta_x * 20, mlx->player.pos_y + mlx->player.delta_y * 20, 0x00FF0000);
	return (0);
}

int ft_display_ground(t_mlx *mlx)
{
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_font.img, 0, 0);
	return (0);
}

int	ft_display_map(t_mlx *mlx)
{
	int x = 0;
	int y = 0;

	while (y < mapy)
	{
		while (x < mapx)
		{
			if (map[y * mapx + x] == 1)
			{
				mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_wall.img, x * 64, y * 64);
			}
			else if (map[y * mapx + x] == 0)
			{
				mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ground.img, x * 64, y * 64);
			}
			x++;
		}
		x = 0;
		y++;
	}


	return (0);
}

int	handleloop(t_mlx *mlx)
{
	ft_display_map(mlx);
	ft_display_player(mlx);
	ft_setmove(mlx);
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void editimage(t_data *data, int size_x, int size_y, int color)
{
	int win_x = 0;
	int win_y = 0;

	while (win_y < size_y)
	{
        while (win_x < size_x)
        {
        	my_mlx_pixel_put(data, win_x, win_y, color);
            win_x++;
        }
        win_x = 0;
        win_y++;
    }
}

void initimages(t_mlx *mlx)
{
	mlx->img_font.img = mlx_new_image(mlx->mlx_ptr, 1920, 1080);
	mlx->img_font.addr = mlx_get_data_addr(mlx->img_font.img, &mlx->img_font.bits_per_pixel, &mlx->img_font.line_length,
								&mlx->img_font.endian);
	mlx->img_ground.img = mlx_new_image(mlx->mlx_ptr, 62, 62);
	mlx->img_ground.addr = mlx_get_data_addr(mlx->img_ground.img, &mlx->img_ground.bits_per_pixel, &mlx->img_ground.line_length,
								&mlx->img_ground.endian);
	editimage(&mlx->img_ground, 62, 62, 0x000000FF);
	mlx->img_wall.img = mlx_new_image(mlx->mlx_ptr, 62, 62);
	mlx->img_wall.addr = mlx_get_data_addr(mlx->img_wall.img, &mlx->img_wall.bits_per_pixel, &mlx->img_wall.line_length,
								&mlx->img_wall.endian);
	editimage(&mlx->img_wall, 62, 62, 0x0000FF00);
	mlx->img_player.img = mlx_new_image(mlx->mlx_ptr, 16, 16);
	mlx->img_player.addr = mlx_get_data_addr(mlx->img_player.img, &mlx->img_player.bits_per_pixel, &mlx->img_player.line_length,
								&mlx->img_player.endian);
	editimage(&mlx->img_player, 16, 16, 0xFF000000);
}

void init(t_mlx *mlx)
{
	mlx->player.pos_x = 50;
	mlx->player.pos_y = 50;
	mlx->player.z = false;
	mlx->player.q = false;
	mlx->player.s = false;
	mlx->player.d = false;
	mlx->win_x = 1080;
	mlx->win_y = 1080;
	mlx->mlx_ptr = mlx_init();
	mlx->player.delta_x = 0;
	mlx->player.delta_y = 0;
	mlx->player.angle = 0;
	initimages(mlx);
}

int	main(int ac, char **av)
{
	t_mlx	mlx;

	(void) ac;
	(void) av;
	init(&mlx);
	editimage(&mlx.img_font, 1920, 1080, 0x00000000);
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, mlx.win_x, mlx.win_y, "cub3d");
	mlx_hook(mlx.win_ptr, 17, 1L << 17, ft_close, &mlx);
	mlx_hook(mlx.win_ptr, KeyPress, KeyPressMask, handlekey, &mlx);
	mlx_hook(mlx.win_ptr, KeyRelease, KeyReleaseMask, handlekeyrelease, &mlx);
	ft_display_ground(&mlx);
	mlx_loop_hook(mlx.mlx_ptr, handleloop, &mlx);
	mlx_loop(mlx.mlx_ptr);
}
