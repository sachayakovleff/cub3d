/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: syakovle <syakovle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/28 14:42:43 by syakovle          #+#    #+#             */
/*   Updated: 2023/02/20 18:44:58 by syakovle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <strings.h>
#include <stdlib.h>
#include <stdio.h>

char	*ft_getsavedchar(char *read_line);

int	ft_eol(char *buffer)
{
	if (buffer == NULL)
		return (0);
	while (*buffer)
	{
		if (*buffer == '\n')
		{	
			return (1);
		}	
		buffer++;
	}
	return (0);
}

size_t	ft_strlen(const char *theString)
{
	int	i;

	i = 0;
	if (theString == NULL)
		return (i);
	while (theString[i])
		i++;
	return (i);
}

char	*ft_strjoins(char *s1, char *s2)
{
	char		*str;
	int			i;
	int			j;
	const int	k = ft_strlen(s1);
	const int	l = ft_strlen(s2);

	str = malloc(sizeof(char) * (k + l + 1));
	if (str == NULL)
		return (NULL);
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
	free(s2);
	str[i] = 0;
	return (str);
}

char	*ft_getresult(char *saved_chars, char *read_line)
{
	int		index;
	char	*result;

	if (read_line == NULL)
		return (NULL);
	index = 0;
	while (read_line[index])
		index++;
	result = malloc(sizeof(char) * (index + 1));
	if (result == NULL)
		return (NULL);
	index = 0;
	while (read_line[index])
	{
		result[index] = read_line[index];
		if (read_line[index] == '\n')
			break ;
		index++;
	}
	result[index + 1] = 0;
	result = ft_strjoins(saved_chars, result);
	return (result);
}

char	*ft_result(char **saved_chars, char *read_line)
{
	char	*returned_line;

	if ((saved_chars[0] == NULL) && read_line[0] == 0)
	{
		free(read_line);
		return (NULL);
	}
	if (!ft_eol(read_line) && read_line != NULL)
	{
		returned_line = ft_strjoins(saved_chars[0], read_line);
		if (saved_chars[0])
			free(saved_chars[0]);
		if (*returned_line == 0)
		{
			free(returned_line);
			return (NULL);
		}
		saved_chars[0] = NULL;
		return (returned_line);
	}
	returned_line = ft_getresult(saved_chars[0], read_line);
	if (saved_chars[0])
		free(saved_chars[0]);
	saved_chars[0] = ft_getsavedchar(read_line);
	return (returned_line);
}
