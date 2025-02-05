/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_closing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:18:49 by francema          #+#    #+#             */
/*   Updated: 2025/02/04 19:07:07 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_first_cmd(t_pipex *pip)
{
	int	i;

	i = 1;
	close(pip->pipe_fd[0][READ_END]);
	while (i < pip->n_cmds - 1)
	{
		close(pip->pipe_fd[i][WRITE_END]);
		close(pip->pipe_fd[i][READ_END]);
		i++;
	}
}

void	close_mid_cmd(t_pipex *pip)
{
	int	i;

	i = 0;
	while (i < pip->pip_idx -1)
	{
		close(pip->pipe_fd[i][WRITE_END]);
		close(pip->pipe_fd[i][READ_END]);
		i++;
	}
	close(pip->pipe_fd[pip->pip_idx - 1][WRITE_END]);
	close(pip->pipe_fd[pip->pip_idx][READ_END]);
	//close(pip->pipe_fd[pip->pip_idx][WRITE_END]);
	i = pip->pip_idx + 1;
	while (i < pip->n_cmds -1)
	{
		close(pip->pipe_fd[i][WRITE_END]);
		close(pip->pipe_fd[i][READ_END]);
		i++;
	}
}

void	close_last_cmd(t_pipex *pip)
{
	int	i;

	close(pip->pipe_fd[pip->pip_idx - 1][WRITE_END]);
	close(pip->pipe_fd[pip->pip_idx][READ_END]);
	close(pip->pipe_fd[pip->pip_idx][WRITE_END]);
	i = 0;
	while (i < pip->n_cmds - 1)
	{
		close(pip->pipe_fd[i][WRITE_END]);
		if (!(i == pip->n_cmds - 2))
			close(pip->pipe_fd[i][READ_END]);
		i++;
	}
}

void	close_pipfd(t_pipex *pip)
{
	if (pip->here_doc_flag || pip->pip_idx == 0)
		close_first_cmd(pip);
	else if (pip->pip_idx != 0 && pip->pip_idx != pip->n_cmds - 1)
		close_mid_cmd(pip);
	else if (pip->pip_idx == pip->n_cmds - 1)
		close_last_cmd(pip);
}
