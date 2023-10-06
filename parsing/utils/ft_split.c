/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 20:46:45 by amontign          #+#    #+#             */
/*   Updated: 2023/10/06 12:34:26 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../init_map.h"

int	ft_count_words(char const *s, char c)
{
	int	i;
	int	nb_words;

	i = 0;
	nb_words = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] != c)
		{
			nb_words++;
			while (s[i] && s[i] != c)
				i++;
		}
		if (s[i])
			i++;
	}
	return (nb_words);
}

void	free_tab(char **tab, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	**alloc_tab(char **tab, char const *s, char c, int i)
{
	int	nb_words;
	int	j;

	j = 0;
	nb_words = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			j = 0;
			while (s[i + j] && s[i + j] != c)
				j++;
			i += j;
			tab[nb_words] = malloc((j + 1) * sizeof(char));
			if (!tab[nb_words])
			{
				free_tab(tab, nb_words);
				return (NULL);
			}
			nb_words++;
		}
		if (s[i])
			i++;
	}
	return (tab);
}

char	**complete_tab(char **tab, char const *s, char c, int i)
{
	int	j;
	int	nb_words;

	j = 0;
	nb_words = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			j = 0;
			while (s[i] && s[i] != c)
			{
				tab[nb_words][j] = s[i];
				j++;
				i++;
			}
			tab[nb_words][j] = '\0';
			nb_words++;
		}
		if (s[i])
			i++;
	}
	tab[nb_words] = NULL;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		nb_words;
	int		i;

	i = 0;
	nb_words = ft_count_words(s, c);
	res = malloc((nb_words + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (s[i] && s[i] == c)
		i++;
	res = alloc_tab(res, s, c, i);
	if (!res)
		return (NULL);
	res = complete_tab(res, s, c, i);
	return (res);
}
