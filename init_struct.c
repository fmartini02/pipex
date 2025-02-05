/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:50:24 by francema          #+#    #+#             */
/*   Updated: 2025/02/04 16:49:42 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fill_pip(t_pipex *pip, int tot_elem)
{
	int	i;
	int	special;

	i = 0;
	special = 3;
	if (pip->here_doc_flag)
		special = 4 - 1;//-1 becuse we need 1 pipe more for here_doc
	while (i < (tot_elem - special))
	{
		pip->pipe_fd[i] = malloc(sizeof(int) * 2);
		if (!pip->pipe_fd[i])
		{
			errno = ENOMEM;
			perror("Error: malloc failed");
			free_mem(pip, EXIT_FAILURE);
		}
		if (pipe(pip->pipe_fd[i]) == -1)
		{
			perror("Error: pipe failed");
			free_mem(pip, EXIT_FAILURE);
		}
		i++;
	}
	pip->pipe_fd[i] = NULL;
}

void	fill_cmds(t_pipex *pip, char **av, int ac)
{
	int	i;
	int	special;

	i = 0;
	special = 3;
	if (pip->here_doc_flag)
		special = 4;
	while (i < (ac - special))
	{
		pip->cmds[i] = ft_strdup(av[i + 2]);
		if (!pip->cmds[i])
		{
			errno = ENOMEM;
			perror("Error: malloc failed");
			free_mem(pip, EXIT_FAILURE);
		}
		i++;
	}
}

void	element_init(t_pipex *pip, char **av, int tot_elm)
{
	int	special;
	int	i;

	special = 3;
	i = 1;
	if (pip->here_doc_flag)
	{
		special = 4;
		pip->pipe_fd = malloc(sizeof(int *) * (tot_elm - special + 1));
	}
	else
	{
		pip->pipe_fd = malloc(sizeof(int *) * (tot_elm - special + 1));
		pip->cmds = malloc(sizeof(char *) * (tot_elm - special + 1));
	}
	if (pip->here_doc_flag)
		pip->delimiter = av[++i];
	if (!pip->pipe_fd || !pip->cmds)
	{
		errno = ENOMEM;
		perror("Error: malloc failed");
		free_mem(pip, EXIT_FAILURE);
	}
	fill_pip(pip, tot_elm);
	fill_cmds(pip, av, tot_elm);
}

void	init_struct(t_pipex *pip, char **av, int ac, char **envp)
{
	int	tot_elem;

	tot_elem = ac;
	pip->envp = envp;
	pip->here_doc_flag = 0;
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
	}
	element_init(pip, av, tot_elem);
}
