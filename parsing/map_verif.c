/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_verif.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:18:18 by amontign          #+#    #+#             */
/*   Updated: 2023/11/07 18:31:04 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_map.h"

int	map_minim(char **map)
{
	int	x;
	int	y;
	int	count;

	y = 0;
	count = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S'
				|| map[y][x] == 'E' || map[y][x] == 'W')
				count++;
			x++;
		}
		y++;
	}
	if (count != 1)
		return (0);
	return (1);
}

int	is_map_valid2(char **map, t_pars *pars)
{
	int	x;
	int	y;

	y = 1;
	while (map[y] && map[y + 1])
	{
		x = 1;
		while (map[y][x] && map[y][x + 1])
		{
			if (map[y][x] == '0' || map[y][x] == 'N' || map[y][x] == 'S'
				|| map[y][x] == 'E' || map[y][x] == 'W')
			{
				if (map[y - 1][x] == ' ' || map[y + 1][x] == ' '
					|| map[y][x - 1] == ' ' || map[y][x + 1] == ' ')
					return (0);
			}
			x++;
		}
		pars->map_w = x + 1;
		y++;
	}
	pars->map_h = y;
	return (1);
}

int	is_map_valid(char **map, t_pars *pars)
{
	int	x;
	int	y;
	int	len;

	if (!map)
		return (0);
	if (!map_minim(map))
		return (0);
	y = -1;
	while (map[++y])
	{
		len = ft_strlen(map[y]);
		x = 0;
		while (map[y][x])
		{
			if (y == 0 || x == 0 || x == (len - 1) || !(map[y + 1]))
			{
				if (map[y][x] == '0' || map[y][x] == 'N' || map[y][x] == 'S'
					|| map[y][x] == 'E' || map[y][x] == 'W')
					return (0);
			}
			x++;
		}
	}
	return (is_map_valid2(map, pars));
}

int	fill_texture_size(t_texture *texture, char *str, int i)
{
	int	k;
	int	j;

	k = 1;
	while (str[i + k] && str[i + k] != ' ')
		k++;
	k++;
	j = k;
	while (str[i + k] && str[i + k] != ' ')
		k++;
	str[i + k] = '\0';
	texture->y_size = ft_atoi(str + i + j);
	str[j] = '\0';
	texture->x_size = ft_atoi(str + i + 1);
	free(str);
	return (0);
}
