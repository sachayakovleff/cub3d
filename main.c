/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:33:44 by marvin            #+#    #+#             */
/*   Updated: 2023/10/16 14:18:08 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	pixelsize = 64;
/*int	mapx = 8;
int	mapy = 8;

char	map[] = 
{
	'1', '1', '1', '1', '1', '1', '1', '1',
	'1', '0', '0', '0', '0', '0', '0', '1',
	'1', '0', '0', '0', '0', '0', '1', ' ',
	'1', '0', '0', '0', '0', '1', '0', '1',
	'1', '0', '0', '0', '1', '0', '0', '1',
	'1', '0', '0', '0', '0', '0', '0', '1',
	'1', '0', '0', '0', '0', '0', '0', '1',
	'1', '1', '1', '1', '1', '1', '1', '1',
};*/

int draw_line(t_mlx *mlx, void *win, int beginX, int beginY, int endX, int endY, int color)
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
		if (pixelX < mlx->pars.map_w * pixelsize && pixelY < mlx->pars.map_h * pixelsize)
			mlx_pixel_put(mlx->mlx_ptr, win, pixelX, pixelY, color);
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
	// int i;
	// int j;

	// i = 0;
	// j = 0;
	// while (j < 14)
	// {
	// 	while (i < 14)
	// 	{
	// 		if (x - 7 + i < 0 || x - 7 + i > ft_strlen(mlx->pars.map[0]))
	// 			mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_empty.img, i * 64, j * 64);
	// 		else if (y - 7 + j < 0 || y - 7 + j > ft_strlen(mlx->pars.map[0]))
	// 			mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_empty.img, i * 64, j * 64);
	// 		else if (mlx->pars.map[j][i] == '1')
	// 			mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_wall.img, i * 64, j * 64);
	// 		else if (mlx->pars.map[j][i] == '0')
	// 			mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_ground.img, i * 64, j * 64);
	// 		else
	// 			mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img_empty.img, i * 64, j * 64);
	// 		i++;
	// 	}
	// 	i = 0;
	// 	j++;
	// }
	// return (0);
	static int	i = 0;

	if (i % 50 != 0)
		return (i++, 0);
	while (y < mlx->pars.map_h + 1)
	{
		while (x < mlx->pars.map_w)
		{
			if (mlx->pars.map2[y * mlx->pars.map_w + x] == '1')
			{
				mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr,
					mlx->img_wall.img, x * 64, y * 64);
			}
			else if (mlx->pars.map2[y * mlx->pars.map_w + x] == '0')
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

int	gettexture(t_mlx *mlx, int y, t_data *data)
{
	char	*dst;

	//int testy1 = ((y - mlx->render3d.wall_top_pixel) / (mlx->render3d.wall_bottom_pixel - mlx->render3d.wall_top_pixel)) * 1500;
	float testy1 = y - mlx->render3d.wall_top_pixel;
	float testy2 = mlx->render3d.wall_bottom_pixel - mlx->render3d.wall_top_pixel;
	float testy3 = 1500 * (testy1 / testy2);
	float x1 = fmod(mlx->rays.ray_x, 64);
	float x2 = x1 / 64;
	float x3 = x2 * 1500;
	//printf("x1: %f\n\n", x1);
	//printf("x2: %f\n\n", x2);
	//printf("x3: %f\n\n", x3);
	//printf("\n\ny: %d\n", y);
	//printf("testy1 %f\n", testy1);
	//printf("testy2 %f\n", testy2);
	//printf("testy3 %d\n", (int)testy3);
	
	dst = data->addr + ((int) testy3 * data->line_length + (int) x3 * (data->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}

int	gettexture2(t_mlx *mlx, int y, t_data *data)
{
	char	*dst;

	//int testy1 = ((y - mlx->render3d.wall_top_pixel) / (mlx->render3d.wall_bottom_pixel - mlx->render3d.wall_top_pixel)) * 1500;
	float testy1 = y - mlx->render3d.wall_top_pixel;
	float testy2 = mlx->render3d.wall_bottom_pixel - mlx->render3d.wall_top_pixel;
	float testy3 = 1500 * (testy1 / testy2);
	float x1 = fmod(mlx->rays.ray_y, 64);
	float x2 = x1 / 64;
	float x3 = x2 * 1500;
	//printf("x1: %f\n\n", x1);
	//printf("x2: %f\n\n", x2);
	//printf("x3: %f\n\n", x3);
	//printf("\n\ny: %d\n", y);
	//printf("testy1 %f\n", testy1);
	//printf("testy2 %f\n", testy2);
	//printf("testy3 %d\n", (int)testy3);
	
	dst = data->addr + (((int) testy3) * data->line_length + (int)x3 * (data->bits_per_pixel / 8));
	return (*(unsigned int *)dst);
}


void	set_pixels_by_line(t_mlx *mlx)
{
	int	y;

	y = mlx->render3d.wall_top_pixel;
	while (++y <= mlx->render3d.wall_bottom_pixel && y <= mlx->win_y)
	{
		if (y < 0)
			continue;
		if (mlx->rays.distH < mlx->rays.distV)
		{
			my_mlx_pixel_put(&(mlx->img_3d), mlx->rays.ray * 1, y, gettexture(mlx, y, &mlx->img_n));
			//my_mlx_pixel_put(&(mlx->img_3d), mlx->rays.ray * 1 + 1, y, gettexture(mlx, y, &mlx->img_n));
			/*my_mlx_pixel_put(&(mlx->img_3d), mlx->rays.ray * 1 + 2, y, 0x00FF0000);
			my_mlx_pixel_put(&(mlx->img_3d), mlx->rays.ray * 1 + 3, y, 0x00FF0000);
			my_mlx_pixel_put(&(mlx->img_3d), mlx->rays.ray * 4 + 4, y, 0x00FF0000);
			my_mlx_pixel_put(&(mlx->img_3d), mlx->rays.ray * 4 + 5, y, 0x00FF0000);
			my_mlx_pixel_put(&(mlx->img_3d), mlx->rays.ray * 4 + 6, y, 0x00FF0000);
			my_mlx_pixel_put(&(mlx->img_3d), mlx->rays.ray * 4 + 7, y, 0x00FF0000);*/
		}
		else
		{
			my_mlx_pixel_put(&(mlx->img_3d), mlx->rays.ray * 1, y, gettexture2(mlx, y, &mlx->img_w));
			//my_mlx_pixel_put(&(mlx->img_3d), mlx->rays.ray * 1 + 1, y, gettexture2(mlx, y, &mlx->img_w));
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
	mlx->render3d.wall_bottom_pixel = (mlx->win_y / 2) + (mlx->render3d.wall_strip_h / 2);
	set_pixels_by_line(mlx);
}

void	ft_draw_rays(t_mlx *mlx)
{
	mlx->rays.ray_angle = mlx->player.angle;
	mlx->rays.ray = 0;
	mlx->rays.ray_angle = mlx->player.angle - (DR * 30);
	while (mlx->rays.ray < 600)
	{
		get_ray_angle(mlx);
		ft_cast_vertical(mlx);
		ft_cast_horizontal(mlx);
		get_ray_collision(mlx);
		//draw_line(mlx, mlx->win_ptr, mlx->player.pos_x,
		//	mlx->player.pos_y, mlx->rays.ray_x, mlx->rays.ray_y, 0xFF000000);
		edit_3d_image(mlx);
		mlx->rays.ray++;
		mlx->rays.ray_angle += (DR / 10);
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

	if (parsing_main(ac, av, &mlx))
	{
		free_pars_struct(&mlx.pars);
		return (1);
	}
	init(&mlx);
	editimage(&mlx.img_font, 1920, 1080, 0x00000000);
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, mlx.win_x, mlx.win_y, "cub3d");
	mlx_hook(mlx.win_ptr, 17, 1L << 17, ft_close, &mlx);
	mlx_hook(mlx.win_ptr, KeyPress, KeyPressMask, handlekey, &mlx);
	mlx_hook(mlx.win_ptr, KeyRelease, KeyReleaseMask, handlekeyrelease, &mlx);
	ft_display_ground(&mlx);
	mlx_loop_hook(mlx.mlx_ptr, handleloop, &mlx);
	mlx_loop(mlx.mlx_ptr);
	free_pars_struct(&mlx.pars);
	return (0);
}
