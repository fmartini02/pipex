/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:50:24 by francema          #+#    #+#             */
/*   Updated: 2025/01/23 18:41:45 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fill_pip_and_cmd(t_pipex *pip, char **av, int ac)
{
	int	i;
	int	tot_elem;
	int	special;

	i = 0;
	special = 2;
	tot_elem = ac - 1;
	while (i < tot_elem - special)
	{
		pip->pipe_fd[i - 1] = malloc(sizeof(int) * 2);
		if (!*pip->pipe_fd[i - 1])
		{
			perror("Error: malloc failed");
			exit(1);
		}
		pipe(pip->pipe_fd[i - 1]);
		pip->cmds[i - 1] = av[i];
		i++;
	}
}

void	element_init(t_pipex *pip, char **av, int tot_elm, int i)
{
	int	special;

	special = 2;
	if (pip->here_doc_flag)
		special = 3;
	pip->pipe_fd = malloc(sizeof(int *) * (tot_elm - special));
	pip->cmds = malloc(sizeof(int *) * (tot_elm - special));
	pip->delimiter = av[i++];
	if (!*pip->pipe_fd || !*pip->cmds)
	{
		perror("Error: malloc failed");
		exit(1);
	}
	fill_pip_and_cmd(pip, av, tot_elm);
}

void	init_struct(t_pipex *pip, char **av, int ac)
{
	int	i;
	int	tot_elem;

	i = 1;
	tot_elem = ac - 1;
	pip->here_doc_flag = 0;
	pip->cmd_idx = 0;
	pip->pip_idx = 0;
	if (ft_strcmp(av[1], "here_doc") == 0)
		pip->here_doc_flag = 1;
	else
	{
		pip->file_in = av[i];
		i++;
	}
	pip->file_out = av[tot_elem + 1];
	element_init(pip, av, tot_elem, i);
}
