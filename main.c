/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:33:44 by marvin            #+#    #+#             */
/*   Updated: 2023/10/02 18:07:03 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	ft_display_map(t_mlx *mlx)
{
	int x = 0;
	int y = 0;
	static int i = 0;
	if (i % 50 != 0)
		return (i++, 0);
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
	i++;
	return (0);
}

float dist(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	ft_cast_horizontal(t_mlx *mlx)
{
	mlx->rays.dof = 0;
	float aTan = -1 / tan(mlx->rays.ray_angle);
	if (mlx->rays.ray_angle > PI)
	{
		mlx->rays.ray_y = (((int)mlx->player.pos_y >> 6) << 6) - 0.0001;
		mlx->rays.ray_x = (mlx->player.pos_y - mlx->rays.ray_y) * aTan + mlx->player.pos_x;
		mlx->rays.yo = -64;
		mlx->rays.xo = -(mlx->rays.yo * aTan); 
	}
	if (mlx->rays.ray_angle < PI)
	{
		mlx->rays.ray_y = (((int)mlx->player.pos_y >> 6) << 6) + 64;
		mlx->rays.ray_x = (mlx->player.pos_y - mlx->rays.ray_y) * aTan + mlx->player.pos_x;
		mlx->rays.yo = 64;
		mlx->rays.xo = -(mlx->rays.yo * aTan); 
	}
	if (mlx->rays.ray_angle == 0 || mlx->rays.ray_angle == PI)
	{
		mlx->rays.ray_x = mlx->player.pos_x;
		mlx->rays.ray_y = mlx->player.pos_y;
		mlx->rays.dof = 8;
	}
	while (mlx->rays.dof < 8)
	{
		mlx->rays.mx = (int) (mlx->rays.ray_x) >> 6;
		mlx->rays.my = (int) (mlx->rays.ray_y) >> 6;
		if (mlx->rays.mx >= 500)
			mlx->rays.mx = 500;
		mlx->rays.mp = mlx->rays.my * mapx + mlx->rays.mx;			
		if (mlx->rays.mp >= 0 && mlx->rays.mp < mapx * mapy && map[mlx->rays.mp] == 1)
		{
			mlx->rays.hx = mlx->rays.ray_x;
			mlx->rays.hy = mlx->rays.ray_y;
			mlx->rays.distH = dist(mlx->player.pos_x, mlx->player.pos_y, mlx->rays.hx, mlx->rays.hy);
			mlx->rays.dof = 8;
		}
		else
		{
			mlx->rays.ray_x += mlx->rays.xo;
			mlx->rays.ray_y += mlx->rays.yo;
			mlx->rays.dof += 1;
		}
	}
}

void	ft_cast_vertical(t_mlx *mlx)
{
	mlx->rays.dof = 0;
	float nTan = -tan(mlx->rays.ray_angle);
	if (mlx->rays.ray_angle > P2 && mlx->rays.ray_angle < P3)
	{
		mlx->rays.ray_x = (((int)mlx->player.pos_x >> 6) << 6) - 0.0001;
		mlx->rays.ray_y = (mlx->player.pos_x - mlx->rays.ray_x) * nTan + mlx->player.pos_y;
		mlx->rays.xo = -64;
		mlx->rays.yo = -(mlx->rays.xo * nTan); 
	}
	if (mlx->rays.ray_angle < P2 || mlx->rays.ray_angle > P3)
	{
		mlx->rays.ray_x = (((int)mlx->player.pos_x >> 6) << 6) + 64;
		mlx->rays.ray_y = (mlx->player.pos_x - mlx->rays.ray_x) * nTan + mlx->player.pos_y;
		mlx->rays.xo = 64;
		mlx->rays.yo = -(mlx->rays.xo * nTan); 
	}
	if (mlx->rays.ray_angle == 0 || mlx->rays.ray_angle == PI)
	{
		mlx->rays.ray_y = mlx->player.pos_y;
		mlx->rays.ray_x = mlx->player.pos_x;
		mlx->rays.dof = 8;
	}
	while (mlx->rays.dof < 8)
	{
		mlx->rays.mx = (int) (mlx->rays.ray_x) >> 6;
		mlx->rays.my = (int) (mlx->rays.ray_y) >> 6;
		if (mlx->rays.mx >= 500)
			mlx->rays.mx = 500;
		mlx->rays.mp = mlx->rays.my * mapx + mlx->rays.mx;			
		if (mlx->rays.mp >= 0 && mlx->rays.mp < mapx * mapy && map[mlx->rays.mp] == 1)
		{
			mlx->rays.dof = 8;
		}
		else
		{
			mlx->rays.ray_x += mlx->rays.xo;
			mlx->rays.ray_y += mlx->rays.yo;
			mlx->rays.dof += 1;
		}
	}
}

void	ft_draw_rays(t_mlx *mlx)
{
	mlx->rays.ray_angle = mlx->player.angle;
	mlx->rays.ray = 0;
	mlx->rays.ray_angle = mlx->player.angle - (DR * 30);
	while (mlx->rays.ray < 60)
	{
		if (mlx->rays.ray_angle < 0)
			mlx->rays.ray_angle += 2 * PI;
		if (mlx->rays.ray_angle > 2 * PI)
			mlx->rays.ray_angle -= 2 * PI;
		
		mlx->rays.distH = 100000;
		mlx->rays.distV = 100000;
		ft_cast_vertical(mlx);
		mlx->rays.vx = mlx->rays.ray_x;
		mlx->rays.vy = mlx->rays.ray_y;
		mlx->rays.distV = dist(mlx->player.pos_x, mlx->player.pos_y, mlx->rays.vx, mlx->rays.vy);
		ft_cast_horizontal(mlx);
		mlx->rays.hx = mlx->rays.ray_x;
		mlx->rays.hy = mlx->rays.ray_y;
		mlx->rays.distH = dist(mlx->player.pos_x, mlx->player.pos_y, mlx->rays.hx, mlx->rays.hy);	
		if (mlx->rays.distH > mlx->rays.distV)
		{
			mlx->rays.ray_x = mlx->rays.vx;
			mlx->rays.ray_y = mlx->rays.vy;
		}
		if (mlx->rays.distH < mlx->rays.distH)
		{
			mlx->rays.ray_x = mlx->rays.hx;
			mlx->rays.ray_y = mlx->rays.hy;
		}
		draw_line(mlx->mlx_ptr, mlx->win_ptr, mlx->player.pos_x, mlx->player.pos_y, mlx->rays.ray_x, mlx->rays.ray_y, 0xFF000000);
		mlx->rays.ray++;
		mlx->rays.ray_angle += DR;
		if (mlx->rays.ray_angle < 0)
			mlx->rays.ray_angle += 2 * PI;
		if (mlx->rays.ray_angle > 2 * PI)
			mlx->rays.ray_angle -= 2 * PI;
	}
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