/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:33:44 by marvin            #+#    #+#             */
/*   Updated: 2023/10/04 17:21:39 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	mapx = 8;
int	mapy = 8;
int	pixelsize = 64;

int	map[] = 
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

int draw_line(void *mlx, void *win, int beginX, int beginY, int endX, int endY, int color)
{
	double deltaX = endX - beginX;
	double deltaY = endY - beginY;
	int pixels = sqrt((deltaX * deltaX) + (deltaY * deltaY));
	deltaX /= pixels;
	deltaY /= pixels;
	double pixelX = beginX;
	double pixelY = beginY;
	if (pixels > 5000)
		pixels = 5000;
	while (pixels)
	{
		if (pixelX < mapx * pixelsize && pixelY < mapy * pixelsize)
			mlx_pixel_put(mlx, win, pixelX, pixelY, color);
		pixelX += deltaX;
		pixelY += deltaY;
		--pixels;
	}
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	ft_display_map(t_mlx *mlx, int x, int y)
{
	static int	i = 0;

	if (i % 50 != 0)
		return (i++, 0);
	while (y < mapy)
	{
		while (x < mapx)
		{
			if (map[y * mapx + x] == 1)
			{
				mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr,
					mlx->img_wall.img, x * 64, y * 64);
			}
			else if (map[y * mapx + x] == 0)
			{
				mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr,
					mlx->img_ground.img, x * 64, y * 64);
			}
			x++;
		}
		x = 0;
		y++;
	}
	return (i++, 0);
}

void	get_ray_angle(t_mlx *mlx)
{
	if (mlx->rays.ray_angle < 0)
		mlx->rays.ray_angle += 2 * PI;
	if (mlx->rays.ray_angle > 2 * PI)
		mlx->rays.ray_angle -= 2 * PI;
	mlx->rays.distH = 100000;
	mlx->rays.distV = 100000;
}

void	get_ray_collision(t_mlx *mlx)
{
	if (mlx->rays.distH > mlx->rays.distV)
	{
		mlx->rays.ray_x = mlx->rays.vx;
		mlx->rays.ray_y = mlx->rays.vy;
		mlx->render3d.distance = mlx->rays.distV
			* cos(mlx->rays.ray_angle - mlx->player.angle);
	}
	if (mlx->rays.distH < mlx->rays.distV)
	{
		mlx->rays.ray_x = mlx->rays.hx;
		mlx->rays.ray_y = mlx->rays.hy;
		mlx->render3d.distance = mlx->rays.distH
			* cos(mlx->rays.ray_angle - mlx->player.angle);
	}
}

void	set_pixels_by_line(t_mlx *mlx)
{
	int	y;

	y = mlx->render3d.wall_top_pixel;
	while (++y <= mlx->render3d.wall_bottom_pixel)
	{
		if (mlx->rays.distH < mlx->rays.distV)
		{
			my_mlx_pixel_put(&(mlx->img_3d), mlx->rays.ray * 1, y, 0x00FF0000);
			my_mlx_pixel_put(&(mlx->img_3d), mlx->rays.ray * 1 + 1, y, 0x00FF0000);
			/*my_mlx_pixel_put(&(mlx->img_3d), mlx->rays.ray * 1 + 2, y, 0x00FF0000);
			my_mlx_pixel_put(&(mlx->img_3d), mlx->rays.ray * 1 + 3, y, 0x00FF0000);
			my_mlx_pixel_put(&(mlx->img_3d), mlx->rays.ray * 4 + 4, y, 0x00FF0000);
			my_mlx_pixel_put(&(mlx->img_3d), mlx->rays.ray * 4 + 5, y, 0x00FF0000);
			my_mlx_pixel_put(&(mlx->img_3d), mlx->rays.ray * 4 + 6, y, 0x00FF0000);
			my_mlx_pixel_put(&(mlx->img_3d), mlx->rays.ray * 4 + 7, y, 0x00FF0000);*/
		}
		else
		{
			my_mlx_pixel_put(&(mlx->img_3d), mlx->rays.ray * 1, y, 0x0000FF00);
			my_mlx_pixel_put(&(mlx->img_3d), mlx->rays.ray * 1 + 1, y, 0x0000FF00);
			/*my_mlx_pixel_put(&(mlx->img_3d), mlx->rays.ray * 1 + 2, y, 0x0000FF00);
			my_mlx_pixel_put(&(mlx->img_3d), mlx->rays.ray * 1 + 3, y, 0x0000FF00);
			my_mlx_pixel_put(&(mlx->img_3d), mlx->rays.ray * 4 + 4, y, 0x0000FF00);
			my_mlx_pixel_put(&(mlx->img_3d), mlx->rays.ray * 4 + 5, y, 0x0000FF00);
			my_mlx_pixel_put(&(mlx->img_3d), mlx->rays.ray * 4 + 6, y, 0x0000FF00);
			my_mlx_pixel_put(&(mlx->img_3d), mlx->rays.ray * 4 + 7, y, 0x0000FF00);*/
		}
	}
}

void	edit_3d_image(t_mlx *mlx)
{
	mlx->render3d.projected_wall_h = (64 / mlx->render3d.distance)
		* ((mlx->win_x / 2) / tan((120 * (PI / 180)) / 2));
	mlx->render3d.wall_strip_h = (int)mlx->render3d.projected_wall_h;
	mlx->render3d.wall_top_pixel = (mlx->win_y / 2) - (mlx->render3d.wall_strip_h / 2);
	if (mlx->render3d.wall_top_pixel < 0)
		mlx->render3d.wall_top_pixel = 0;
	mlx->render3d.wall_bottom_pixel = (mlx->win_y / 2) + (mlx->render3d.wall_strip_h / 2);
	if (mlx->render3d.wall_bottom_pixel > mlx->win_x)
		mlx->render3d.wall_bottom_pixel = mlx->win_y;
	set_pixels_by_line(mlx);
}

void	ft_draw_rays(t_mlx *mlx)
{
	mlx->rays.ray_angle = mlx->player.angle;
	mlx->rays.ray = 0;
	mlx->rays.ray_angle = mlx->player.angle - (DR * 30);
	while (mlx->rays.ray < 480)
	{
		get_ray_angle(mlx);
		ft_cast_vertical(mlx);
		ft_cast_horizontal(mlx);
		get_ray_collision(mlx);
		//draw_line(mlx->mlx_ptr, mlx->win_ptr, mlx->player.pos_x,
		//	mlx->player.pos_y, mlx->rays.ray_x, mlx->rays.ray_y, 0xFF000000);
		edit_3d_image(mlx);
		mlx->rays.ray++;
		mlx->rays.ray_angle += (DR / 8);
		if (mlx->rays.ray_angle < 0)
			mlx->rays.ray_angle += 2 * PI;
		if (mlx->rays.ray_angle > 2 * PI)
			mlx->rays.ray_angle -= 2 * PI;
	}
}

void	editimage(t_data *data, int size_x, int size_y, int color)
{
	int	win_x;
	int	win_y;

	win_x = 0;
	win_y = 0;
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
