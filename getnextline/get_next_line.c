/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakovle <syakovle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/20 18:09:07 by syakovle          #+#    #+#             */
/*   Updated: 2023/05/10 19:31:11 by syakovle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include "get_next_line.h"

char	*ft_strjoins(char *s1, char *s2);
int		ft_strlen(const char *theString);
char	*ft_result(char **saved_chars, char *read_line);
int		ft_eol(char *buffer);
char	*ft_getresult(char *saved_chars, char *read_line);

char	*ft_strjoin(char *s1, char const *s2)
{
	char		*str;
	int			i;
	int			j;
	const int	k = ft_strlen(s1);
	const int	l = ft_strlen(s2);

	str = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	i = 0;
	j = 0;
	while (i < k)
	{
		str[i] = s1[i];
		i++;
	}
	while (j < l)
	{
		str[i] = s2[j];
		i++;
		j++;
	}
	str[i] = '\0';
	if (*s1)
		free(s1);
	return (str);
}

char	*ft_read(int fd)
{
	char	*buffer;
	char	*result;
	int		i;

	result = "";
	while (true)
	{	
		buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		i = read(fd, buffer, BUFFER_SIZE);
		if (i < 0)
		{
			free(buffer);
			return (NULL);
		}
		buffer[BUFFER_SIZE - (BUFFER_SIZE - i)] = 0;
		result = ft_strjoin(result, buffer);
		if (i == 0 || ft_eol(buffer))
		{
			free(buffer);
			break ;
		}	
		free(buffer);
	}
	return (result);
}

char	*ft_getsavedchar(char *read_line)
{
	int		index;
	char	*saved_chars;
	int		index2;

	index = 1;
	index2 = 0;
	while (read_line[index] && read_line[index - 1] != '\n')
		index++;
	saved_chars = malloc(sizeof(char) * (ft_strlen(read_line) - index + 1));
	while (read_line[index])
	{
		saved_chars[index2] = read_line[index];
		index++;
		index2++;
	}
	saved_chars[index2] = 0;
	free(read_line);
	return (saved_chars);
}

char	*get_next_line(int fd)
{
	static char	*saved_chars;
	char		*read_line;
	char		*returned_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (ft_eol(saved_chars))
	{
		returned_line = ft_getresult("", saved_chars);
		saved_chars = ft_getsavedchar(saved_chars);
		return (returned_line);
	}
	read_line = ft_read(fd);
	if (read_line == NULL)
		return (NULL);
	return (ft_result(&saved_chars, read_line));
}
