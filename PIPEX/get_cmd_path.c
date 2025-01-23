/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:33:34 by francema          #+#    #+#             */
/*   Updated: 2025/01/23 19:08:44 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_paths(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
}

char	*brute_testing(char **paths, char *cmd)
{
	char	*path;
	char	*tmp;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		path = ft_strjoin(tmp, cmd);
		if (access(path, X_OK) == 0)
		{
			free(tmp);
			break;
		}
		else
		{
			free(path);
			free(tmp);
		}
		i++;
	}
	free_paths(paths);
	return (path);
}

char	*find_path(char *cmd)
{
	char	**paths;
	char	*path;

	paths = ft_split(getenv("PATH"), ':');
	if (!paths)
	{
		perror("Error: malloc failed");
		exit(1);
	}
	path = brute_testing(paths, cmd);
	if (!path)
	{
		perror("Error: command not found");
		exit(1);
	}
	return (path);
}
