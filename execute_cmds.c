/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 15:05:14 by francema          #+#    #+#             */
/*   Updated: 2025/02/04 18:35:39 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**give_args(char *cmd)
{
	char	**args;

	args = ft_split(cmd, ' ');
	if (!args)
	{
		errno = ENOMEM;
		perror("Error: malloc failed");
		exit(127);
	}
	return (args);
}

void	first_child(t_pipex *pip, char *path)
{
	int		fd_in;

	fd_in = open(pip->file_in, O_RDONLY);
	if (fd_in == -1)
	{
		perror("Error: open failed");
		free_mem(pip, EXIT_FAILURE);
	}
	if (dup2(fd_in, STDIN_FILENO) == -1)
	{
		perror("Error: dup failed");
		close(fd_in);
		free_mem(pip, EXIT_FAILURE);
	}
	close(fd_in);
	if (dup2(pip->pipe_fd[pip->pip_idx][WRITE_END], STDOUT_FILENO) == -1)
	{
		perror("Error: dup failed");
		close(pip->pipe_fd[pip->pip_idx][WRITE_END]);
		close_pipfd(pip);
		free_mem(pip, EXIT_FAILURE);
	}
	close(pip->pipe_fd[pip->pip_idx][WRITE_END]);
	close_pipfd(pip);
	if (execve(path, pip->args, pip->envp) == -1)
	{
		perror("Error: execve failed");
		free_mem(pip, EXIT_FAILURE);
	}
}

void	mid_child(t_pipex *pip, char *path)
{
	if (dup2(pip->pipe_fd[pip->pip_idx - 1][READ_END], STDIN_FILENO) == -1)
	{
		perror("Error: dup failed");
		free_mem(pip, EXIT_FAILURE);
	}
	close(pip->pipe_fd[pip->pip_idx - 1][READ_END]);
	if (dup2(pip->pipe_fd[pip->pip_idx][WRITE_END], STDOUT_FILENO) == -1)
	{
		perror("Error: dup failed");
		close(pip->pipe_fd[pip->pip_idx][WRITE_END]);
		close_pipfd(pip);
		free_mem(pip, EXIT_FAILURE);
	}
	close(pip->pipe_fd[pip->pip_idx][WRITE_END]);
	close_pipfd(pip);
	if (execve(path, pip->args, pip->envp) == -1)
	{
		perror("Error: execve failed");
		free_mem(pip, EXIT_FAILURE);
	}
}

void	last_child(t_pipex *pip, char *path)
{
	int	fd_out;

	if (pip->here_doc_flag)
		fd_out = open(pip->file_out, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd_out = open(pip->file_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		perror("Error: open failed");
		free_mem(pip, EXIT_FAILURE);
	}
	if (dup2(fd_out, STDOUT_FILENO) == -1)
	{
		perror("Error: dup failed");
		close(fd_out);
		free_mem(pip, EXIT_FAILURE);
	}
	close (fd_out);
	if (dup2(pip->pipe_fd[pip->pip_idx - 1][READ_END], STDIN_FILENO) == -1)
	{
		perror("Error: dup failed");
		close (pip->pipe_fd[pip->pip_idx - 1][READ_END]);
		close_pipfd(pip);
		free_mem(pip, EXIT_FAILURE);
	}
	close (pip->pipe_fd[pip->pip_idx - 1][READ_END]);
	close_pipfd(pip);
	if (execve(path, pip->args, pip->envp) == -1)
	{
		perror("Error: execve failed");
		free_mem(pip, EXIT_FAILURE);
	}
}

void	execute_cmds(t_pipex *pip)
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
