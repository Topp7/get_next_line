/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stopp <stopp@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 15:26:44 by stopp             #+#    #+#             */
/*   Updated: 2023/11/23 15:54:47 by stopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*rd_to_str(int fd, char *str)
{
	char	*buf;
	int		bytes;

	if (read(fd, 0, 0) < 0)
		return (free(str), NULL);
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buf == NULL)
		return (NULL);
	bytes = 1;
	while (ft_strchr(str, '\n') == NULL && bytes != 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes == -1)
		{
			free (buf);
			free (str);
			return (NULL);
		}
		buf[bytes] = '\0';
		str = ft_strjoin(str, buf);
		if (str == NULL)
			return (NULL);
	}
	free (buf);
	return (str);
}

char	*get_line1(char *str)
{
	int		i;
	char	*new_line;

	i = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] != '\n' && str[i])
		i++;
	if (str[i] == '\n')
		i++;
	new_line = malloc(sizeof(char) * (i + 1));
	if (new_line == NULL)
		return (NULL);
	new_line[i] = '\0';
	while (--i >= 0)
		new_line[i] = str[i];
	return (new_line);
}

char	*update_str(char *str)
{
	int		i;
	int		j;
	char	*updated;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free (str);
		return (NULL);
	}
	if (str[i] == '\n')
		i++;
	updated = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (updated == NULL)
		return (free(str), NULL);
	j = 0;
	while (str[i])
		updated[j++] = str[i++];
	updated[j] = '\0';
	free (str);
	return (updated);
}

char	*get_next_line(int fd)
{
	static char	*str[1024];
	char		*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 1023)
		return (NULL);
	str[fd] = rd_to_str(fd, str[fd]);
	if (str[fd] == NULL)
		return (NULL);
	if (*str[fd] == '\0')
	{
		free (str[fd]);
		str[fd] = NULL;
		return (NULL);
	}
	next_line = get_line1(str[fd]);
	str[fd] = update_str(str[fd]);
	if (str[fd] == NULL)
		return (next_line);
	return (next_line);
}
