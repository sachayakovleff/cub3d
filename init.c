/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/02 17:33:40 by marvin            #+#    #+#             */
/*   Updated: 2023/10/02 17:33:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	imginit(t_data *data, t_mlx *mlx, int img_sizex, int img_sizey)
{
	data->img = mlx_new_image(mlx->mlx_ptr, img_sizex, img_sizey);
	if (data->img == NULL)
		return (printf("Error couldn't create image\n"), ft_free(mlx),
			free_pars_struct(&mlx->pars), exit(1));
	data->addr = mlx_get_data_addr(data->img, &(data->bits_per_pixel),
			&(data->line_length), &(data->endian));
}

void	initxpm(t_mlx *mlx, t_data *data, int height, int width, char *name)
{
	data->width = width;
	data->height = height;
	data->img = mlx_xpm_file_to_image(mlx->mlx_ptr, name, &data->width, &data->height);
	if (data->img == NULL)
		return (printf("Error couldn't create image\n"), ft_free(mlx),
			free_pars_struct(&mlx->pars), exit(1));
	data->addr = mlx_get_data_addr(data->img, &data->bits_per_pixel, &data->line_length, &data->endian);
}

void	initimages(t_mlx *mlx)
{
	imginit(&mlx->img_font, mlx, 1920, 1080);
	imginit(&mlx->img_empty, mlx, 64, 64);
	imginit(&mlx->img_ground, mlx, 64, 64);
	imginit(&mlx->img_wall, mlx, 64, 64);
	imginit(&mlx->img_player, mlx, 16, 16);
	editimage(&mlx->img_empty, 64, 64, 0x00000000);
	editimage(&mlx->img_ground, 64, 64, 0x000000FF);
	editimage(&mlx->img_wall, 64, 64, 0x0000FF00);
	editimage(&mlx->img_player, 8, 8, 0xFF000000);
	initxpm(mlx, &mlx->img_n, mlx->pars.n_t.y_size, mlx->pars.n_t.x_size, mlx->pars.n_t.path);
	initxpm(mlx, &mlx->img_s, mlx->pars.s_t.y_size, mlx->pars.s_t.x_size, mlx->pars.s_t.path);
	initxpm(mlx, &mlx->img_e, mlx->pars.e_t.y_size, mlx->pars.e_t.x_size, mlx->pars.e_t.path);
	initxpm(mlx, &mlx->img_w, mlx->pars.w_t.y_size, mlx->pars.w_t.x_size, mlx->pars.w_t.path);
}

void	initall(t_mlx *mlx)
{
	mlx->img_3d.img = NULL;
	mlx->img_e.img = NULL;
	mlx->img_empty.img = NULL;
	mlx->img_font.img = NULL;
	mlx->img_ground.img = NULL;
	mlx->img_n.img = NULL;
	mlx->img_player.img = NULL;
	mlx->img_s.img = NULL;
	mlx->img_w.img = NULL;
	mlx->img_wall.img = NULL;
	mlx->mlx_ptr = NULL;
	mlx->win_ptr = NULL;
}

void	init(t_mlx *mlx)
{
	initall(mlx);
	mlx->player.pos_x = 290;
	mlx->player.pos_y = 500;
	mlx->player.z = false;
	mlx->player.q = false;
	mlx->player.s = false;
	mlx->player.d = false;
	mlx->win_x = 1920;
	mlx->win_y = 1080;
	mlx->mlx_ptr = mlx_init();
	if (mlx->mlx_ptr == NULL)
		return (printf("Error mlx_init returned NULL ptr\n"),
			free_pars_struct(&mlx->pars), exit(1));
	mlx->player.delta_x = 1;
	mlx->player.delta_y = 0;
	mlx->player.angle = 0;
	initimages(mlx);
}
