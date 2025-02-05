/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 10:36:03 by francema          #+#    #+#             */
/*   Updated: 2025/02/04 18:41:26 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_mem(t_pipex *pip, int exit_code)
{
	int	i;

	i = 0;
	free(pip->cmds);
	i = 0;
	while (pip->pipe_fd[i])
		free(pip->pipe_fd[i++]);
	free(pip->pipe_fd);
	exit(exit_code);
}

void	executer(t_pipex *pip)
{
	if (pip->here_doc_flag)
		execute_here_doc(pip);
	else
		execute_cmds(pip);
}

void	free_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		free(args[i++]);
	free(args);
}

int	main(int ac, char **av, char **envp)
{
	int		i;
	t_pipex	pipex;
	pid_t	pid;

	i = 0;
	if (ac < 5)
	{
		errno = EINVAL;
		perror("Error: Wrong number of arguments");
		exit(127);
	}
	else
		init_struct(&pipex, av, ac, envp);
	while (pipex.cmds[pipex.cmd_idx])
	{
		pipex.args = give_args(pipex.cmds[pipex.cmd_idx]);
		pipex.path = find_path(pipex.args[0]);
		pid = fork();
		if (pid == -1)
		{
			perror("Error: fork failed");
			free_mem(&pipex, EXIT_FAILURE);
		}
		else if (pid == 0)
			executer(&pipex);
		else
			waitpid(pid, NULL, 0);
		free_args(pipex.args);
		free(pipex.path);
		pipex.cmd_idx++;
		pipex.pip_idx++;
	}
	free_mem(&pipex, EXIT_SUCCESS);
}
