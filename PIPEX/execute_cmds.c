/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:05:14 by francema          #+#    #+#             */
/*   Updated: 2025/01/23 15:59:47 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(t_pipex *pip, char *path)
{
	if (pip->pip_idx == 0)
	{
		close(1);
		if (dup(pip->pipe_fd[pip->pip_idx - 1][WRITE_END]) == -1)
		{
			perror("Error: dup failed");
			exit(1);
		}
		close_pipfd(pip);
		if (execve(path, pip->cmds[pip->cmd_idx], NULL) == -1)
		{
			perror("Error: execve failed");
			exit(1);
		}
	}
}

void	succ_child(t_pipex *pip, char *path)
{
	if (pip->cmd_idx != 0)
	{
		close(0);
		if (dup(pip->pipe_fd[pip->pip_idx - 1][READ_END]) == -1)
		{
			perror("Error: dup failed");
			exit(1);
		}
		close(1);
		if (dup(pip->pipe_fd[pip->pip_idx][WRITE_END]) == -1)
		{
			perror("Error: dup failed");
			exit(1);
		}
		if (pip->pip_idx == pip->n_cmds)
		{
			close_pipfd(pip);
			if (execve(path, pip->cmds[pip->cmd_idx], NULL) == -1)
			{
				perror("Error: execve failed");
				exit(1);
			}
		}
	}
}

void	last_child(t_pipex *pip, char *path)
{
	if (pip->pip_idx == pip->n_cmds)
	{
		close(1);
		if (dup(pip->pipe_fd[pip->pip_idx][WRITE_END]) == -1)
		{
			perror("Error: dup failed");
			exit(1);
		}
		close_pipfd(pip);
		pip->pip_idx++;
		if (execve(path, pip->cmds[pip->cmd_idx], NULL) == -1)
		{
			perror("Error: execve failed");
			exit(1);
		}
	}
}

void	execute_cmds(t_pipex *pip, char *path)
{
	if (pip->pip_idx == 0)
		first_child(pip, path);
	else if (pip->pip_idx == pip->n_cmds)
		last_child(pip, path);
	else
		succ_child(pip, path);
}
