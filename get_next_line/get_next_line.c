/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amontign <amontign@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 04:14:17 by amontign          #+#    #+#             */
/*   Updated: 2023/10/24 16:50:30 by amontign         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*l;
	unsigned int	i;
	unsigned int	n;

	i = 0;
	n = size * nmemb;
	l = malloc(size * nmemb);
	if (l == NULL)
		return (NULL);
	while (i < n)
	{
		*((unsigned char *) l + i) = 0;
		i++;
	}
	return (l);
}

int	pos_return_in_line(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*get_next_line_return(char *temp, int file_end)
{
	int		size;
	char	*sub;
	char	*next_line;

	if (file_end == 1 && !temp[0])
	{
		free(temp);
		return (NULL);
	}
	else if (file_end == 1)
		size = ft_strlen(temp);
	else
		size = pos_return_in_line(temp) + 1;
	next_line = ft_calloc(sizeof(char), size + 2);
	if (!next_line)
		return (NULL);
	ft_strncat(next_line, temp, size);
	sub = ft_substr(temp, size, BUFFER_SIZE);
	ft_strncpy(temp, sub, BUFFER_SIZE);
	free(sub);
	return (next_line);
}

char	*new_temp(char *temp, char *buffer, int *file_end)
{
	char			*temp2;
	unsigned int	i;

	if (ft_strncat(temp, buffer, BUFFER_SIZE) == 0)
		*file_end = 1;
	i = 0;
	if (!temp[0])
	{
		free(temp);
		return (NULL);
	}
	temp2 = ft_calloc(sizeof(char), (ft_strlen(temp) + BUFFER_SIZE + 1));
	while (i < ft_strlen(temp))
	{
		temp2[i] = temp[i];
		i++;
	}
	temp2[i] = '\0';
	free(temp);
	return (temp2);
}

char	*get_next_line(int fd, int clear)
{
	int			file_end;
	char		*buffer;
	static char	*temp;

	file_end = 0;
	if (fd < 0)
		return (NULL);
	if (!temp || clear == 1)
		temp = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	if (!temp)
		return (NULL);
	if (temp[0] && pos_return_in_line(temp) >= 0)
		return (get_next_line_return(temp, file_end));
	while (pos_return_in_line(temp) < 0 && file_end == 0)
	{
		buffer = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
		if (!buffer)
			return (NULL);
		read(fd, buffer, BUFFER_SIZE);
		temp = new_temp(temp, buffer, &file_end);
		free(buffer);
		if (!temp)
			return (NULL);
	}
	return (get_next_line_return(temp, file_end));
}
