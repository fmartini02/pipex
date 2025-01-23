/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_here_doc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 14:17:55 by francema          #+#    #+#             */
/*   Updated: 2025/01/23 16:48:28 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	create_and_fill_doc(t_pipex *pip)
{
	char	*tmp;
	char	*here;
	int		fd_here;

	here = ".here_doc";
	fd_here = open(here, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd_here == -1)
	{
		perror("Error: open failed");
		exit(1);
	}
	tmp = NULL;
	while (1)
	{
		tmp = get_next_line(0);
		write(fd_here, tmp, ft_strlen(tmp));
		write(fd_here, "\n", 1);
		if (ft_strstr(tmp, pip->delimiter))
		{
			free(tmp);
			break ;
		}
		free(tmp);
	}
	return (fd_here);
}

void	handle_fd(t_pipex *pip)
{
	close(0);
	if (dup(pip->pipe_fd[pip->pip_idx][READ_END]) == -1)
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
	close_pipfd(pip);
	pip->pip_idx++;
}

void	execute_here_doc(t_pipex *pip, char *path)
{
	int	fd_here;

	fd_here = create_and_fill_doc(pip);
	pip->pipe_fd[pip->pip_idx][READ_END] = fd_here;
	handle_fd(pip);
	if (execve(path, pip->cmds[pip->cmd_idx], NULL) == -1)
	{
		perror("Error: execve failed");
		exit(1);
	}
	pip->here_doc_flag = 0;
}
