/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:50:24 by francema          #+#    #+#             */
/*   Updated: 2025/02/19 17:49:07 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**give_args(char *cmd)
{
	char	**args;

	args = ft_split(cmd, ' ');
	if (!args)
	{
		ft_printf(ERR "Error: malloc failed" RESET);
		exit(MALLOC);
	}
	return (args);
}

void	init_pip(t_pipex *pip, int tot_elem)
{
	int	i;
	int	dummy_elem;

	i = 0;
	dummy_elem = 3;
	while (i < (tot_elem - dummy_elem - 1))
	{
		pip->pipe_fd[i] = malloc(sizeof(int) * 2);
		if (!pip->pipe_fd[i])
		{
			ft_printf(ERR "Error: malloc failed\n" RESET);
			free_mid(pip, MALLOC);
		}
		if (pipe(pip->pipe_fd[i]) == -1)
		{
			perror(ERR "Error: pipe failed\n" RESET);
			free_mid(pip, MALLOC);
		}
		i++;
	}
}

void	init_cmds(t_pipex *pip, char **av, int ac)
{
	int	i;
	int	dummy_elem;
	int	boh;

	i = 0;
	dummy_elem = 3;
	boh = 2;
	if (pip->here_doc_flag)
	{
		dummy_elem = 4;
		boh = 3;
	}
	while (i < (ac - dummy_elem))
	{
		pip->cmds[i] = ft_strdup(av[i + boh]);
		if (!pip->cmds[i])
		{
			ft_printf(ERR "Error: malloc failed\n" RESET);
			free_mid(pip, MALLOC);
		}
		i++;
	}
}

void	init_pipes_cmds(t_pipex *pip, char **av, int tot_elm)
{
	int	dummy_elem;
	int	i;

	dummy_elem = 3;
	i = 1;
	if (pip->here_doc_flag)
		pip->n_pipes = pip->n_cmds;
	else
		pip->n_pipes = pip->n_cmds - 1;
	pip->pipe_fd = malloc(sizeof(int *) * (tot_elm - dummy_elem - 1));
	if (pip->here_doc_flag)
		pip->cmds = malloc(sizeof(char *) * (tot_elm - dummy_elem - 1));
	else
		pip->cmds = malloc(sizeof(char *) * (tot_elm - dummy_elem));
	if (!pip->pipe_fd || !pip->cmds)
	{
		ft_printf(ERR "Error: malloc failed\n" RESET);
		free_mid(pip, MALLOC);
	}
	if (pip->here_doc_flag)
		pip->delimiter = ft_strjoin(av[++i], "\n");
	init_pip(pip, tot_elm);
	init_cmds(pip, av, tot_elm);
}

void	init_struct(t_pipex *pip, char **av, int ac, char **envp)
{
	int	tot_elem;

	tot_elem = ac;
	pip->envp = envp;
	pip->here_doc_flag = 0;
	pip->path = NULL;
	pip->args = NULL;
	pip->cmd_idx = 0;
	pip->pip_idx = 0;
	pip->path = NULL;
	if (ft_strcmp(av[1], "here_doc") == 0)
	{
		pip->here_doc_flag = 1;
		pip->file_in = NULL;
		pip->file_out = ft_strdup(av[tot_elem - 1]);
		pip->n_cmds = tot_elem - 4;
	}
	else
	{
		pip->file_in = ft_strdup(av[1]);
		pip->file_out = ft_strdup(av[tot_elem - 1]);
		pip->n_cmds = tot_elem - 3;
		pip->delimiter = NULL;
	}
	init_pipes_cmds(pip, av, tot_elem);
}
