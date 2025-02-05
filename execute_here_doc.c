/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_here_doc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:17:55 by francema          #+#    #+#             */
/*   Updated: 2025/02/04 16:51:44 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	put_in_pipe(t_pipex *pip)
{
	char	*tmp;

	while (1)
	{
		tmp = get_next_line(0);
		if (!tmp)
		{
			errno = ENOMEM;
			perror("Error: get_next_line failed");
			free_mem(pip, EXIT_FAILURE);
		}
		write(pip->pipe_fd[0][WRITE_END], tmp, ft_strlen(tmp));
		if (ft_strcmp(tmp, pip->delimiter) == 0)
		{
			free(tmp);
			break ;
		}
		free(tmp);
	}
}

void	handle_fd(t_pipex *pip)
{
	close(0);
	if (dup(pip->pipe_fd[0][READ_END]) == -1)
	{
		perror("Error: dup failed");
		free_mem(pip, EXIT_FAILURE);
	}
	close(1);
	if (dup(pip->pipe_fd[1][WRITE_END]) == -1)
	{
		perror("Error: dup failed");
		free_mem(pip, EXIT_FAILURE);
	}
	close_pipfd(pip);
	pip->pip_idx += 2;
}

void	execute_here_doc(t_pipex *pip)
{
	char	*path;

	path = pip->path;
	put_in_pipe(pip);
	handle_fd(pip);
	pip->args = give_args(pip->cmds[pip->cmd_idx]);
	if (execve(path, pip->args, NULL) == -1)
	{
		perror("Error: execve failed");
		free_mem(pip, EXIT_FAILURE);
	}
	pip->here_doc_flag = 0;
}
