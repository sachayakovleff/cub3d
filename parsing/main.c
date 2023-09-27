#include "parsing.h"

void	error(char *str)
{
	while (*str)
		write(2, str++, 1);
}

int	str_is_empty(char *str)
{
	int len_str;

	len_str = strlen(str);
	if (len_str < 2)
		return (1);
	return (0);
}

void	free_strings_tab(char **str_tab)
{
	int	i;

	i = 0;
	if (!str_tab)
		return ;
	while (str_tab[i])
	{
		free(str_tab[i]);
		i++;
	}
	free(str_tab);
}

void	free_pars_struct(t_pars *pars)
{
	free(pars->n_texture);
	free(pars->s_texture);
	free(pars->e_texture);
	free(pars->w_texture);
	free_strings_tab(pars->map);
}

int	infos_complete(t_pars *pars)
{
	if (pars->n_texture && pars->s_texture && pars->e_texture
		&& pars->w_texture && pars->f_colors[0] >= 0 && pars->f_colors[1] >= 0
		&& pars->f_colors[2] >= 0 && pars->c_colors[0] >= 0
		&& pars->c_colors[1] >= 0 && pars->c_colors[2] >= 0)
	{
		return (1);
	}
	return (0);
}

int	place_texture(char *str, char **texture)
{
	size_t	i;

	if (*texture)
		return (0);
	i = 2;
	while (str[i] == ' ')
		i++;
	if (!str[i] || str[i] == '\n')
		return (0);
	*texture = malloc(sizeof(char) * (strlen(str) - i + 1));
	if (!*texture)
		return (2);
	strncpy(*texture, str + i, strlen(str) - i + 1);
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
			if ((numbers[i][j] < 48 || numbers[i][j] > 57) && numbers[i][j] != '\n')
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

int	str_is_valid(char *str, t_pars *pars)
{
	if (strncmp(str, "NO ", 3) == 0)
	{
		return (place_texture(str, &pars->n_texture));
	}
	if (strncmp(str, "SO ", 3) == 0)
	{
		return (place_texture(str, &pars->s_texture));
	}
	if (strncmp(str, "EA ", 3) == 0)
	{
		return (place_texture(str, &pars->e_texture));
	}
	if (strncmp(str, "WE ", 3) == 0)
	{
		return (place_texture(str, &pars->w_texture));
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

int	is_map_valid2(char **map)
{
	int	x;
	int	y;

	y = 1;
	while (map[y] && map[y + 1])
	{
		x = 1;
		while (map[y][x] && map[y][x + 1])
		{
			if (map[y][x] == '0' || map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E' || map[y][x] == 'W')
			{
				if (map[y - 1][x] == ' ' || map[y + 1][x] == ' ' || map[y][x - 1] == ' ' || map[y][x + 1] == ' ')
					return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}

int	map_minim(char **map)
{
	int	x;
	int	y;
	int	count;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E' || map[y][x] == 'W')
				count++;
			x++;
		}
		y++;
	}
	if (count != 1)
		return (0);
	return (1);
}

int	is_map_valid(char **map)
{
	int	x;
	int	y;
	int	len;

	if (!map)
		return (0);
	if (!map_minim(map))
		return (0);
	y = 0;
	while (map[y])
	{
		len = ft_strlen(map[y]);
		x = 0;
		while (map[y][x])
		{
			if (y == 0 || x == 0 || x == (len - 1) || !(map[y + 1]))
			{
				if (map[y][x] == '0' || map[y][x] == 'N' || map[y][x] == 'S' || map[y][x] == 'E' || map[y][x] == 'W')
					return (0);
			}
			x++;
		}
		y++;
	}
	return (is_map_valid2(map));
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
		if (str[i] != ' ' && str[i] != '0' && str[i] != '1' && str[i] != 'N' && str[i] != 'S' && str[i] != 'E' && str[i] != 'W' && str[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

char	**fill_map(char	**map)
{
	int		i;
	int		j;
	size_t	max;
	char	*tmp;

	i = 0;
	max = 0;
	while (map[i])
	{
		if (map[i][ft_strlen(map[i]) - 1] == '\n')
			map[i][ft_strlen(map[i]) - 1] = '\0';
		if (ft_strlen(map[i]) > max)
			max = ft_strlen(map[i]);
		i++;
	}
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

int	map_parsing(int fd, t_pars *pars)
{
	char *str;
	int ret_valid;

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

int	infos_parsing(int fd, t_pars *pars)
{
	char *str;
	int ret_valid;

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

void	init_pars(t_pars *pars)
{
	pars->n_texture = NULL;
	pars->s_texture = NULL;
	pars->e_texture = NULL;
	pars->w_texture = NULL;
	pars->f_colors[0] = -1;
	pars->f_colors[1] = -1;
	pars->f_colors[2] = -1;
	pars->c_colors[0] = -1;
	pars->c_colors[1] = -1;
	pars->c_colors[2] = -1;
	pars->map = NULL;
}

int	parsing(char **argv, t_pars *pars)
{
	int	fd;
	int	error_val;

	init_pars(pars);
	fd = open(argv[1], O_RDONLY);
	error_val = infos_parsing(fd, pars);
	if (error_val == 1)
		error_val = map_parsing(fd, pars);
	if (error_val == 1)
		error_val = 1; // remplacer par une fonction qui verifie les lignes suivantes de get_next_line pour verifier qu'elles sont vides et eviter un leak avec le cache de gnl
	else
		error_val = (error_val * 2) / 2; // remplacer par une fonction qui skip les lignes de gnl pour eviter qu'il y ai encore qqchose dans le cache de gnl
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

int	is_arg_valid(int argc, char **argv)
{
	int	file_name_len;
	int	fd;

	if (argc != 2)
	{
		error("Error\nNombre d'arguments invalides\n");
		return (0);
	}
	file_name_len = strlen(argv[1]);
	if (file_name_len < 5)
	{
		error("Error\nNom du fichier invalide\n");
		return (0);
	}
	if (argv[1][file_name_len - 1] != 'b' || argv[1][file_name_len - 2] != 'u' || argv[1][file_name_len - 3] != 'c' || argv[1][file_name_len - 4] != '.')
	{
		error("Error\nNom du fichier invalide\n");
		return (0);
	}
	fd = open(argv[1], O_RDONLY); 
	if (fd < 0) {
		error("Error\nImpossible d'ouvrir le fichier\n");
		return (0);
	}
	close(fd);
	return (1);
}

void	print_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_pars pars_struct;
	if (!is_arg_valid(argc, argv))
	{
		return (1);
	}
	if (parsing(argv, &pars_struct) == 0)
	{
		return (1);
	}
	if (is_map_valid(pars_struct.map) == 0)
	{
		error("Error\nLa map n'est pas valide\n");
		return (1);
	}
	print_map(pars_struct.map);
	free_pars_struct(&pars_struct);
}