/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:33:44 by marvin            #+#    #+#             */
/*   Updated: 2023/10/22 16:49:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		if (pixelX < mlx->pars.map_w * 64 && pixelY < mlx->pars.map_h * 64)
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

void	print_map2(t_pars *pars)
{
	int	i = 0;
	int	j;

	while (i < pars->map_h)
	{
		j = 0;
		while (j < pars->map_w)
		{
			write(1, &pars->map2[i * pars->map_w + j], 1);
			j++;
		}
		printf("%c", '\n');
		fflush(stdout);
		i++;
	}
}

void freemlx(t_mlx mlx)
{
	mlx_destroy_window(mlx.mlx_ptr, mlx.win_ptr);
	mlx_destroy_image(mlx.mlx_ptr, mlx.img_e.img);
	mlx_destroy_image(mlx.mlx_ptr, mlx.img_n.img);
	mlx_destroy_image(mlx.mlx_ptr, mlx.img_s.img);
	mlx_destroy_image(mlx.mlx_ptr, mlx.img_w.img);
	mlx_destroy_image(mlx.mlx_ptr, mlx.img_empty.img);
	mlx_destroy_image(mlx.mlx_ptr, mlx.img_ground.img);
	mlx_destroy_image(mlx.mlx_ptr, mlx.img_wall.img);
	mlx_destroy_image(mlx.mlx_ptr, mlx.img_font.img);
	mlx_destroy_image(mlx.mlx_ptr, mlx.img_player.img);
	mlx_destroy_display(mlx.mlx_ptr);
	free(mlx.mlx_ptr);
}

int	main(int ac, char **av)
{
	t_mlx	mlx;

	if (parsing_main(ac, av, &mlx))
	{
		free_pars_struct(&mlx.pars);
		return (1);
	}
	print_map2(&mlx.pars);
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
	freemlx(mlx);
	return (0);
}
