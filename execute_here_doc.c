/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_here_doc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:17:55 by francema          #+#    #+#             */
/*   Updated: 2025/02/19 17:48:10 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	add_lines(t_pipex *pip)
{
	char	*line;

	line = get_next_line(0);
	while (line)
	{
		if (ft_strcmp(line, pip->delimiter) == 0)
		{
			free(line);
			close_pipfd(pip);
			free_here_doc(pip);
			exit(EXIT_SUCCESS);
		}
		ft_putstr_fd(line, pip->pipe_fd[0][1]);
		free(line);
		line = get_next_line(0);
	}
	free_here_doc(pip);
	exit(EXIT_FAILURE);
}

void	reader(t_pipex *pip)
{
	pid_t	reader_pid;

	reader_pid = fork();
	if (reader_pid == -1)
	{
		perror(ERR "Error: fork failed" RESET);
		free_mid(pip, EXIT_FAILURE);
	}
	else if (reader_pid == 0)
		add_lines(pip);
	else
	{
		close(pip->pipe_fd[0][1]);
		wait(NULL);
	}
}

void	redirector(t_pipex *pip)
{
	if (dup2(pip->pipe_fd[1][1], STDOUT_FILENO) == -1)
	{
		perror(ERR "Error: dup2 failed" RESET);
		close(pip->pipe_fd[1][1]);
		free_mid(pip, DUP2);
	}
	if (dup2(pip->pipe_fd[0][0], STDIN_FILENO) == -1)
	{
		perror(ERR "Error: dup2 failed" RESET);
		close(pip->pipe_fd[0][0]);
		free_mid(pip, DUP2);
	}
	close_pipfd(pip);
}

void	execute_here_doc(t_pipex *pip)
{
	char	*path;
	pid_t	pid;

	path = pip->path;
	reader(pip);
	pid = fork();
	if (pid == -1)
	{
		perror(ERR "error: fork failed" RESET);
		free_mid(pip, EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		redirector(pip);
		free_bf_execve(pip);
		if (execve(path, pip->args, NULL) == -1)
		{
			perror(ERR "Error: execve failed" RESET);
			free_mid(pip, EXIT_FAILURE);
		}
	}
	else
		wait(NULL);
	pip->here_doc_flag = 2;
}
