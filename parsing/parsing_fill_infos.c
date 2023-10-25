/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_fill_infos.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 12:27:53 by amontign          #+#    #+#             */
/*   Updated: 2023/10/25 16:47:04 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_map.h"

int	place_texture(char *str, char **texture)
{
	size_t	i;
	size_t	length;

	if (*texture)
		return (0);
	i = 2;
	while (str[i] == ' ')
		i++;
	if (!str[i] || str[i] == '\n')
		return (0);
	length = strlen(str) - i - 1;
	*texture = malloc(sizeof(char) * (length + 1));
	if (!*texture)
		return (2);
	strncpy(*texture, str + i, length);
	(*texture)[length] = '\0';
	return (1);
}

int	numbers_valid(char **numbers)
{
	int	i;
	int	j;

	i = 0;
	while (numbers[i])
	{
		j = 0;
		while (numbers[i][j])
		{
			if (j > 5)
				return (0);
			if ((numbers[i][j] < 48 || numbers[i][j] > 57)
				&& numbers[i][j] != '\n')
				return (0);
			if (numbers[i][j] == '\n')
				numbers[i][j] = '\0';
			j++;
		}
		i++;
	}
	if (i != 3)
		return (0);
	return (1);
}

int	place_floor_ceiling(char *str, int (*colors)[3])
{
	size_t	i;
	char	**numbers;

	if ((*colors)[0] != -1)
		return (0);
	i = 1;
	while (str[i] == ' ')
		i++;
	if (!str[i] || str[i] == '\n')
		return (0);
	numbers = ft_split(str + i, ',');
	if (!numbers)
		return (2);
	if (!numbers_valid(numbers))
		return (0);
	(*colors)[0] = ft_atoi(numbers[0]);
	(*colors)[1] = ft_atoi(numbers[1]);
	(*colors)[2] = ft_atoi(numbers[2]);
	free_strings_tab(numbers);
	return (1);
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

int	open_and_fill_texture(t_texture *texture)
{
	int		fd;
	char	*str;
	int		i;

	i = 0;
	fd = open(texture->path, O_RDONLY);
	str = malloc(sizeof(char) * 3001);
	if (fd < 0)
		return (1);
	while (1)
	{
		if (read(fd, str, 3000) < 1)
			break ;
		while (str[i] && str[i] != '"')
			i++;
		if (str[i] && str[i] == '"')
			return (fill_texture_size(texture, str, i));
		else
			break ;
	}
	error("Error\nMauvais formattage d'une texture\n");
	if (str)
		free(str);
	close(fd);
	return (1);
}

int	fill_texture_struct(t_pars *pars)
{
	if (open_and_fill_texture(&pars->n_t))
		return (0);
	if (open_and_fill_texture(&pars->s_t))
		return (0);
	if (open_and_fill_texture(&pars->e_t))
		return (0);
	if (open_and_fill_texture(&pars->w_t))
		return (0);
	return (1);
}