/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:12:56 by amontign          #+#    #+#             */
/*   Updated: 2023/10/12 18:48:43 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_map.h"

char	**fill_map2(char **map, size_t max)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (map[i])
	{
		tmp = ft_strdup(map[i]);
		free(map[i]);
		if (!tmp)
			return (NULL);
		map[i] = malloc(sizeof(char) * (max + 1));
		ft_memset(map[i], ' ', max);
		map[i][max] = '\0';
		j = 0;
		while (tmp[j])
		{
			map[i][j] = tmp[j];
			j++;
		}
		free(tmp);
		i++;
	}
	return (map);
}

char	**fill_map(char	**map)
{
	int		i;
	int	max;

	i = 0;
	max = 0;
	if (!map)
		return (NULL);
	while (map[i])
	{
		if (map[i][ft_strlen(map[i]) - 1] == '\n')
			map[i][ft_strlen(map[i]) - 1] = '\0';
		if (ft_strlen(map[i]) > max)
			max = ft_strlen(map[i]);
		i++;
	}
	map = fill_map2(map, max);
	return (map);
}

char	**realloc_tab(char **tab, char *str)
{
	char	**ret;
	int		i;

	i = 0;
	while (tab && tab[i])
	{
		i++;
	}
	ret = malloc(sizeof(char *) * (i + 2));
	if (!ret)
		return (NULL);
	i = 0;
	while (tab && tab[i])
	{
		ret[i] = ft_strdup(tab[i]);
		if (!ret[i])
			return (NULL);
		i++;
	}
	free_strings_tab(tab);
	ret[i] = ft_strdup(str);
	if (!ret[i])
		return (NULL);
	ret[i + 1] = NULL;
	return (ret);
}

int	str_is_valid_map(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '0' && str[i] != '1' && str[i] != 'N'
			&& str[i] != 'S' && str[i] != 'E' && str[i] != 'W'
			&& str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	map_parsing(int fd, t_pars *pars)
{
	char	*str;
	int		ret_valid;

	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		if (!str_is_empty(str))
		{
			ret_valid = str_is_valid_map(str);
			if (ret_valid != 1)
			{
				free(str);
				return (ret_valid);
			}
			pars->map = realloc_tab(pars->map, str);
			if (!pars->map)
				return (2);
		}
		free(str);
	}
	pars->map = fill_map(pars->map);
	return (1);
}
