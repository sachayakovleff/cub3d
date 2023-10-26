/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakovle <syakovle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:33:44 by marvin            #+#    #+#             */
/*   Updated: 2023/10/26 19:39:24 by syakovle         ###   ########.fr       */
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
			write(1, &pars->map2[i * pars->map_w + j], 1);
			j++;
		}
		printf("%c", '\n');
		fflush(stdout);
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
	print_map2(&mlx.pars);
	init(&mlx);
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, mlx.win_x, mlx.win_y, "cub3d");
	if (mlx.win_ptr == NULL)
		return (ft_free(&mlx),
			printf("Error couldn't create the window, Exited\n"),
			free_pars_struct(&mlx.pars), 1);
	mlx_hook(mlx.win_ptr, 17, 1L << 17, ft_close, &mlx);
	mlx_hook(mlx.win_ptr, KeyPress, KeyPressMask, handlekey, &mlx);
	mlx_hook(mlx.win_ptr, KeyRelease, KeyReleaseMask, handlekeyrelease, &mlx);
	ft_display_ground(&mlx);
	mlx_loop_hook(mlx.mlx_ptr, handleloop, &mlx);
	mlx_loop(mlx.mlx_ptr);
	free_pars_struct(&mlx.pars);
	ft_free(&mlx);
	return (0);
}
