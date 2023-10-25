/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:18:00 by amontign          #+#    #+#             */
/*   Updated: 2023/10/25 16:55:13 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_pars(t_pars *pars)
{
	pars->n_t.path = NULL;
	pars->s_t.path = NULL;
	pars->e_t.path = NULL;
	pars->w_t.path = NULL;
	pars->f_colors[0] = -1;
	pars->f_colors[1] = -1;
	pars->f_colors[2] = -1;
	pars->c_colors[0] = -1;
	pars->c_colors[1] = -1;
	pars->c_colors[2] = -1;
	pars->map = NULL;
	pars->map2 = NULL;
}

void	free_pars_struct(t_pars *pars)
{
	if (pars->n_t.path)
		free(pars->n_t.path);
	if (pars->s_t.path)
		free(pars->s_t.path);
	if (pars->e_t.path)
		free(pars->e_t.path);
	if (pars->w_t.path)
		free(pars->w_t.path);
	if (pars->map2)
		free(pars->map2);
	free_strings_tab(pars->map);
}

void	set_player_pos(t_pars *pars)
{
	int	i;

	i = 0;
	while (pars->map2[i])
	{
		if (pars->map2[i] == 'N' || pars->map2[i] == 'S'
			|| pars->map2[i] == 'E' || pars->map2[i] == 'W')
		{
			pars->x_pos = i % pars->map_w;
			pars->y_pos = (int)floor(i / pars->map_w);
			if (pars->map2[i] == 'N')
				pars->view = 1;
			if (pars->map2[i] == 'S')
				pars->view = 2;
			if (pars->map2[i] == 'E')
				pars->view = 3;
			if (pars->map2[i] == 'W')
				pars->view = 4;
		}
		i++;
	}
}

void	finish_map(t_pars *pars)
{
	int	i;
	int	j;
	int	c;

	i = -1;
	c = 0;
	while (pars->map[++i])
		c += ft_strlen(pars->map[i]);
	pars->map2 = malloc(sizeof(char) * (c + 1));
	i = 0;
	while (pars->map[i])
	{
		j = 0;
		while (pars->map[i][j])
		{
			pars->map2[i * pars->map_w + j] = pars->map[i][j];
			j++;
		}
		i++;
	}
	set_player_pos(pars);
}

int	parsing_main(int argc, char **argv, t_mlx *mlx)
{
	int		ret_value;

	ret_value = 0;
	init_pars(&mlx->pars);
	if (!is_arg_valid(argc, argv))
	{
		ret_value = 1;
	}
	else if (parsing(argv, &mlx->pars) == 0)
		ret_value = 1;
	else if (fill_texture_struct(&mlx->pars) == 0)
		ret_value = 1;
	else if (is_map_valid(mlx->pars.map, &mlx->pars) == 0)
	{
		error("Error\nLa map n'est pas valide\n");
		ret_value = 1;
	}
	if (ret_value == 0)
	{
		finish_map(&mlx->pars);
		print_map(mlx->pars.map);
	}
	return (ret_value);
}
