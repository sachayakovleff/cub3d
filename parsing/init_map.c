/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:18:00 by amontign          #+#    #+#             */
/*   Updated: 2023/10/06 12:33:25 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init_map.h"

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

void	free_pars_struct(t_pars *pars)
{
	free(pars->n_texture);
	free(pars->s_texture);
	free(pars->e_texture);
	free(pars->w_texture);
	free_strings_tab(pars->map);
}

int	main(int argc, char **argv)
{
	t_pars	pars_struct;
	int		ret_value;

	ret_value = 0;
	init_pars(&pars_struct);
	if (!is_arg_valid(argc, argv))
	{
		ret_value = 1;
	}
	else if (parsing(argv, &pars_struct) == 0)
	{
		ret_value = 1;
	}
	else if (is_map_valid(pars_struct.map) == 0)
	{
		error("Error\nLa map n'est pas valide\n");
		ret_value = 1;
	}
	if (ret_value == 0)
	{
		print_map(pars_struct.map);
	}
	free_pars_struct(&pars_struct);
	return (ret_value);
}
