/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:44:46 by amontign          #+#    #+#             */
/*   Updated: 2023/10/06 12:33:42 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_MAP_H
# define INIT_MAP_H

# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct	s_pars {
	char	*n_texture;
	char	*s_texture;
	char	*e_texture;
	char	*w_texture;
	int		f_colors[3];
	int		c_colors[3];
	char	**map;
}				t_pars;

char	*get_next_line(int fd);


// init_map_utils.c
void	error(char *str);
void	free_strings_tab(char **str_tab);
void	print_map(char **map);
int		str_is_empty(char *str);

// verif_args.c
int		is_arg_valid(int argc, char **argv);

// parsing.c
int		parsing(char **argv, t_pars *pars);

// parsing_map.c
int		map_parsing(int fd, t_pars *pars);

// map_verif.c
int		is_map_valid(char **map);

// parsing_fill_infos.c
int		place_floor_ceiling(char *str, int (*colors)[3]);
int		place_texture(char *str, char **texture);

// LIBFT
char	**ft_split(char const *s, char c);
int		ft_atoi(const char *nptr);
char	*ft_strdup(const char *s);
size_t	ft_strlen(const char *s);
void	*ft_memset(void *s, int c, size_t n);

#endif