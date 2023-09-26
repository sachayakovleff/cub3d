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

int	infos_complete(t_pars *pars)
{
	if (pars->n_texture && pars->s_texture && pars->e_texture
		&& pars->w_texture/* && pars->f_colors[0] >= 0 && pars->f_colors[1] >= 0
		&& pars->f_colors[2] >= 0 && pars->c_colors[0] >= 0
		&& pars->c_colors[1] >= 0 && pars->c_colors[2] >= 0*/)
	{
		return (1);
	}
	return (0);
}

int	place_arg(char *str, char **texture)
{
	size_t i;

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

int	str_is_valid(char *str, t_pars *pars)
{
	if (strncmp(str, "NO ", 3) == 0)
	{
		return (place_arg(str, &pars->n_texture));
	}
	if (strncmp(str, "SO ", 3) == 0)
	{
		return (place_arg(str, &pars->s_texture));
	}
	if (strncmp(str, "EA ", 3) == 0)
	{
		return (place_arg(str, &pars->e_texture));
	}
	if (strncmp(str, "WE ", 3) == 0)
	{
		return (place_arg(str, &pars->w_texture));
	}
	return (0);
}

int	infos_parsing(int fd, t_pars *pars)
{
	char *str;

	while (!infos_complete(pars))
	{
		str = get_next_line(fd);
		if (!str)
			return (0);
		if (!str_is_empty(str))
		{
			if (!str_is_valid(str, pars))
			{
				free(str);
				return (0);
			}
			if (str_is_valid(str, pars) == 2)
			{
				free(str);
				return (2);
			} // a revoir pour faire 1 seule fois str_is_valid
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
}

int	parsing(char **argv, t_pars *pars)
{
	int	fd;
	int	error_val;

	init_pars(pars);
	fd = open(argv[1], O_RDONLY);
	error_val = infos_parsing(fd, pars);
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
}