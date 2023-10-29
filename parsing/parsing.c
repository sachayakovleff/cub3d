/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakovle <syakovle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:06:48 by amontign          #+#    #+#             */
/*   Updated: 2023/10/29 18:20:07 by syakovle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_map.h"

int	infos_complete(t_pars *pars)
{
	if (pars->n_t.path && pars->s_t.path && pars->e_t.path
		&& pars->w_t.path && pars->f_colors[0] >= 0 && pars->f_colors[1] >= 0
		&& pars->f_colors[2] >= 0 && pars->c_colors[0] >= 0
		&& pars->c_colors[1] >= 0 && pars->c_colors[2] >= 0)
	{
		return (1);
	}
	return (0);
}

int	str_is_valid(char *str, t_pars *pars)
{
	if (strncmp(str, "NO ", 3) == 0)
	{
		return (place_texture(str, &pars->n_t.path));
	}
	if (strncmp(str, "SO ", 3) == 0)
	{
		return (place_texture(str, &pars->s_t.path));
	}
	if (strncmp(str, "EA ", 3) == 0)
	{
		return (place_texture(str, &pars->e_t.path));
	}
	if (strncmp(str, "WE ", 3) == 0)
	{
		return (place_texture(str, &pars->w_t.path));
	}
	if (strncmp(str, "F ", 2) == 0)
	{
		return (place_floor_ceiling(str, &pars->f_colors));
	}
	if (strncmp(str, "C ", 2) == 0)
	{
		return (place_floor_ceiling(str, &pars->c_colors));
	}
	return (0);
}

int	infos_parsing(int fd, t_pars *pars)
{
	char	*str;
	int		ret_valid;

	while (!infos_complete(pars))
	{
		str = get_next_line(fd);
		if (!str)
			return (0);
		if (!str_is_empty(str))
		{
			ret_valid = str_is_valid(str, pars);
			if (ret_valid != 1)
			{
				free(str);
				return (ret_valid);
			}
		}
		free(str);
	}
	return (1);
}

int	verif_lines_end(int fd)
{
	char	*str;
	int		ret_value;

	ret_value = 1;
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		if (!str_is_empty(str))
		{
			ret_value = 0;
		}
		free(str);
	}
	return (ret_value);
}

int	parsing(char **argv, t_pars *pars)
{
	int	fd;
	int	error_val;

	fd = open(argv[1], O_RDONLY);
	error_val = infos_parsing(fd, pars);
	if (error_val == 1)
		error_val = map_parsing(fd, pars);
	if (error_val == 1)
		error_val = verif_lines_end(fd);
	else
		verif_lines_end(fd);
	if (error_val == 0)
	{
		error("Error\nFormattage de la carte incorrect\n");
		return (0);
	}
	if (error_val == 2)
	{
		error("Error\nAllocation echouee\n");
		return (0);
	}
	close(fd);
	return (1);
}
