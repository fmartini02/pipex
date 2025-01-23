/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:06:03 by francema          #+#    #+#             */
/*   Updated: 2024/11/22 18:01:58 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*extract_line(char *line)
{
	int		i;
	char	*ret;

	i = ft_strlen_char(line, '\n');
	ret = ft_calloc(i + 2, sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		ret[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
		ret[i++] = '\n';
	ret[i] = '\0';
	return (ret);
}

char	*ft_get_surplus(char *line)
{
	int		i;
	char	*ret;

	i = ft_strlen_char(line, '\n');
	ret = NULL;
	if (line[i] == '\n')
		ret = malloc(sizeof(char) * (i + 2));
	else if (line[i] == '\0')
		ret = malloc(sizeof(char) * (i + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		ret[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
		ret[i++] = '\n';
	ret[i] = '\0';
	return (ret);
}

char	*ft_fill_line(int fd, char *ret)
{
	int		r_bytes;
	char	*buf;

	buf = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buf)
		return (NULL);
	r_bytes = 1;
	while (!ft_strchr(buf, '\n') && r_bytes > 0)
	{
		r_bytes = read(fd, buf, BUFFER_SIZE);
		if (r_bytes <= 0)
		{
			free(buf);
			if (r_bytes == 0)
				return (ret);
			free(ret);
			return (NULL);
		}
		buf[r_bytes] = '\0';
		ret = ft_strjoin_free(ret, buf);
	}
	free(buf);
	return (ret);
}

char	*ft_update_line(char *line)
{
	int		i;
	char	*tmp;

	i = ft_strlen_char(line, '\n');
	if (!line[i])
	{
		free(line);
		return (NULL);
	}
	tmp = ft_strdup(&line[i + 1]);
	free(line);
	if (!tmp[0])
	{
		free(tmp);
		return (NULL);
	}
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*line = NULL;
	char		*ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (line)
	{
		ret = ft_get_surplus(line);
		line = ft_update_line(line);
	}
	else
		ret = NULL;
	if (!ret)
		line = ft_fill_line(fd, ret);
	if (line && (!ret || !ret[0]))
	{
		ret = extract_line(line);
		line = ft_update_line(line);
	}
	return (ret);
}

