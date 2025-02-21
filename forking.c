/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 11:33:02 by francema          #+#    #+#             */
/*   Updated: 2025/02/21 11:33:46 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child_part(t_pipex *pip)
{
	char	*path;

	path = pip->path;
	if (pip->pip_idx == 0)
		first_child(pip, path);
	else if (pip->pip_idx != pip->n_cmds -1)
		mid_child(pip, path);
	else
		last_child(pip, path);
}

void	here_doc_part(t_pipex *pip)
{
	execute_here_doc(pip);
	free_args(pip->args);
	free(pip->path);
	close(pip->pipe_fd[pip->pip_idx][WRITE_END]);
}

void	parent_part(t_pipex *pip, pid_t pid)
{
	int	status;

	status = 0;
	if (pip->pip_idx != pip->n_cmds - 1)
		close(pip->pipe_fd[pip->pip_idx][WRITE_END]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) != 1)
	{
		ft_printf(ERR "Error: child process failed\n" RESET);
		free_mid(pip, OPEN);
	}
	free_args(pip->args);
	free(pip->path);
}

void	main_utils(t_pipex *pip)
{
	pid_t	pid;

	pip->args = give_args(pip->cmds[pip->cmd_idx]);
	pip->path = find_path(pip->args[0], pip);
	if (pip->here_doc_flag == 1)
	{
		here_doc_part(pip);
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror(ERR "Error: fork failed" RESET);
		free_mid(pip, EXIT_FAILURE);
	}
	else if (pid == 0)
		child_part(pip);
	else
		parent_part(pip, pid);
}
