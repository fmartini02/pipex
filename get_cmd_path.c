/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:33:34 by francema          #+#    #+#             */
/*   Updated: 2025/02/19 17:49:40 by francema         ###   ########.fr       */
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
			break ;
		}
		else
		{
			free(path);
			free(tmp);
		}
		i++;
	}
	if (!paths[i])
		path = NULL;
	free_paths(paths);
	return (path);
}

char	*find_path(char *cmd, t_pipex *pip)
{
	char	**paths;
	char	*path;

	paths = ft_split(getenv("PATH"), ':');
	if (!paths)
	{
		ft_printf(ERR "Error: malloc failed\n" RESET);
		free_args(pip->args);
		free_mid(pip, MALLOC);
	}
	path = brute_testing(paths, cmd);
	if (!path)
	{
		ft_printf(ERR "%s: command not found\n" RESET, cmd);
		//free_args(pip->args);
		free_mid(pip, PATH);
	}
	return (path);
}
