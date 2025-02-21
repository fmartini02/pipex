/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:05:14 by francema          #+#    #+#             */
/*   Updated: 2025/02/19 17:46:36 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child_utils(t_pipex *pip)
{
	int		fd_in;

	fd_in = open(pip->file_in, O_RDONLY);
	if (fd_in == -1)
	{
		perror(ERR"Error: open failed" RESET);
		free_mid(pip, OPEN);
	}
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		perror(ERR"Error: dup2 failed" RESET);
		close(fd_in);
		free_mid(pip, DUP2);
	}
	close(fd_in);
	if (dup2(pip->pipe_fd[pip->pip_idx][WRITE_END], STDOUT_FILENO) == -1)
	{
		perror(ERR "Error: dup2 failed" RESET);
		close_pipfd(pip);
		free_mid(pip, DUP2);
	}
}

void	first_child(t_pipex *pip, char *path)
{
	first_child_utils(pip);
	close_pipfd(pip);
	free_bf_execve(pip);
	if (execve(path, pip->args, pip->envp) == -1)
	{
		perror(ERR "Error: execve failed" RESET);
		free_mid(pip, EXECVE);
	}
}

void	mid_child(t_pipex *pip, char *path)
{
	if (dup2(pip->pipe_fd[pip->pip_idx - 1][READ_END], STDIN_FILENO) == -1)
	{
		perror(ERR "Error: dup2 failed" RESET);
		close_pipfd(pip);
		free_mid(pip, DUP2);
	}
	if (dup2(pip->pipe_fd[pip->pip_idx][WRITE_END], STDOUT_FILENO) == -1)
	{
		perror(ERR "Error: dup2 failed" RESET);
		close_pipfd(pip);
		free_mid(pip, DUP2);
	}
	close_pipfd(pip);
	free_bf_execve(pip);
	if (execve(path, pip->args, pip->envp) == -1)
	{
		perror(ERR "Error: execve failed" RESET);
		free_mid(pip, EXECVE);
	}
}

void	last_child_utils(t_pipex *pip)
{
	int	fd_out;

	if (pip->here_doc_flag)
		fd_out = open(pip->file_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd_out = open(pip->file_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		perror(ERR "Error: open failed" RESET);
		free_mid(pip, OPEN);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror(ERR "Error: du2p failed" RESET);
		close(fd_out);
		free_mid(pip, DUP2);
	}
	close (fd_out);
	if (dup2(pip->pipe_fd[pip->pip_idx - 1][READ_END], STDIN_FILENO) == -1)
	{
		perror(ERR "Error: dup2 failed" RESET);
		close_pipfd(pip);
		free_mid(pip, DUP2);
	}
}

void	last_child(t_pipex *pip, char *path)
{
	last_child_utils(pip);
	close_pipfd(pip);
	free_bf_execve(pip);
	if (execve(path, pip->args, pip->envp) == -1)
	{
		perror(ERR "Error: execve failed" RESET);
		free_mid(pip, EXECVE);
	}
}
