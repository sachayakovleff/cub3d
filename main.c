/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakovle <syakovle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:33:44 by marvin            #+#    #+#             */
/*   Updated: 2023/11/07 18:53:47 by syakovle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	int	i;
	int	j;

	i = 0;
	while (i < pars->map_h)
	{
		j = 0;
		while (j < pars->map_w)
		{
			j++;
		}
		i++;
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
	mlx_hook(mlx.win_ptr, 17, 1L << 17, ft_close, &mlx);
	mlx_hook(mlx.win_ptr, KeyPress, KeyPressMask, handlekey, &mlx);
	mlx_hook(mlx.win_ptr, KeyRelease, KeyReleaseMask, handlekeyrelease, &mlx);
	ft_display_ground(&mlx);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.syakovle.img, 0, 0);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.amontign.img, 0, 760);
	mlx_loop_hook(mlx.mlx_ptr, handleloop, &mlx);
	mlx_loop(mlx.mlx_ptr);
	mlx_destroy_image(mlx.mlx_ptr, mlx.img_3d.img);
	free_pars_struct(&mlx.pars);
	ft_free(&mlx);
	return (0);
}
