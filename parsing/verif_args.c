/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakovle <syakovle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:57:42 by amontign          #+#    #+#             */
/*   Updated: 2023/11/07 18:44:46 by syakovle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_map.h"

int	try_openning(char **argv)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		error("Error\nImpossible d'ouvrir le fichier\n");
		return (0);
	}
	close(fd);
	return (1);
}

int	is_arg_valid(int argc, char **argv)
{
	int	file_name_len;

	if (argc != 2)
	{
		error("Error\nNombre d'arguments invalides\n");
		return (0);
	}
	file_name_len = ft_strlen(argv[1]);
	if (file_name_len < 5)
	{
		error("Error\nNom du fichier invalide\n");
		return (0);
	}
	if (argv[1][file_name_len - 1] != 'b' || argv[1][file_name_len - 2] != 'u'
		|| argv[1][file_name_len - 3] != 'c'
		|| argv[1][file_name_len - 4] != '.')
	{
		error("Error\nNom du fichier invalide\n");
		return (0);
	}
	return (try_openning(argv));
}
