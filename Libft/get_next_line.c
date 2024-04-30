/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgodart <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 12:18:43 by vgodart           #+#    #+#             */
/*   Updated: 2023/11/20 12:18:46 by vgodart          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_join_free(char *buffer, char *tmp_buffer)
{
	char	*result;

	if (buffer)
	{
		result = ft_strjoin2(buffer, tmp_buffer);
		free(buffer);
	}
	else
		result = ft_strjoin2("", tmp_buffer);
	return (result);
}

static char	*get_buffer_file(int fd, char *buffer, char *tmp_buffer)
{
	int	bytes;

	while (!tmp_buffer || !ft_strchr2(buffer, '\n'))
	{
		bytes = read(fd, tmp_buffer, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(tmp_buffer);
			return (NULL);
		}
		if (bytes == 0)
			break ;
		tmp_buffer[bytes] = '\0';
		buffer = ft_join_free(buffer, tmp_buffer);
		if (!buffer)
		{
			free(tmp_buffer);
			return (NULL);
		}
	}
	free(tmp_buffer);
	return (buffer);
}

static char	*get_line(char *buffer)
{
	char	*line;
	int		len;

	if (!buffer)
		return (NULL);
	len = 0;
	while (buffer[len] && buffer[len] != '\n')
		len++;
	if (buffer[len] == '\n')
		len++;
	line = (char *)malloc(len + 1);
	if (!line)
		return (NULL);
	ft_strlcpy2(line, buffer, len + 1);
	return (line);
}

char	*clean_buffer(char *line, char *buffer)
{
	int		start;
	int		end;
	int		size;
	char	*new_buffer;

	if (!line || !buffer)
		return (NULL);
	start = ft_strlen2(line);
	end = ft_strlen2(buffer);
	size = end - start;
	if (size < 0)
		return (NULL);
	if (size == 0)
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = (char *)malloc(size + 1);
	if (!new_buffer)
		return (NULL);
	ft_strlcpy2(new_buffer, buffer + start, size + 1);
	free(buffer);
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*tmp_buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1024)
		return (NULL);
	tmp_buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!tmp_buffer)
		return (NULL);
	buffer = get_buffer_file(fd, buffer, tmp_buffer);
	line = get_line(buffer);
	buffer = clean_buffer(line, buffer);
	return (line);
}
