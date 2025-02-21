/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_closing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:18:49 by francema          #+#    #+#             */
/*   Updated: 2025/02/17 17:55:29 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_first_cmd(t_pipex *pip)
{
	int	i;

	i = 0;
	while (i < pip->n_pipes)
	{
		close(pip->pipe_fd[i][WRITE_END]);
		close(pip->pipe_fd[i][READ_END]);
		i++;
	}
}

void	close_following(t_pipex *pip)
{
	int	i;

	i = 0;
	while (i != pip->pip_idx - 1)
		close(pip->pipe_fd[i++][READ_END]);
	while (i < pip->n_pipes)
	{
		close(pip->pipe_fd[i][WRITE_END]);
		close(pip->pipe_fd[i][READ_END]);
		i++;
	}
}

void	close_pipfd(t_pipex *pip)
{
	if (pip->here_doc_flag || pip->pip_idx == 0)
		close_first_cmd(pip);
	else
		close_following(pip);
}
