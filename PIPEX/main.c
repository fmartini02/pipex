/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:36:03 by francema          #+#    #+#             */
/*   Updated: 2025/01/23 18:24:39 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_mem(t_pipex *pip)
{
	int	i;

	i = 0;
	while (pip->cmds[i])
		free(pip->cmds[i++]);
	free(pip->cmds);
	i = 0;
	while (pip->pipe_fd[i])
		free(pip->pipe_fd[i++]);
	free(pip->pipe_fd);
}

void	executer(t_pipex *pip)
{
	char	*path;

	path = find_path(&pip->cmds[pip->cmd_idx][0]);
	if (pip->here_doc_flag)
		execute_here_doc(pip, path);
	else
		execute_cmds(pip, path);
}

int	main(int ac, char **av)
{
	int		i;
	t_pipex	pipex;
	pid_t 	pid;

	i = 0;
	if (ac != 5)
		perror("Error: Wrong number of arguments");
	else
		init_struct(&pipex, av, ac);
	while (pipex.cmds[pipex.cmd_idx])
	{
		pid = fork();
		if (pid == -1)
		{
			perror("Error: fork failed");
			exit(1);
		}
		else if (pid == 0)
			executer(&pipex);
		else
			waitpid(pid, NULL, 0);
		pipex.cmd_idx++;
	}
	free_mem(&pipex);
}
