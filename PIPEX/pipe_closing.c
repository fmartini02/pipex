/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_closing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 19:18:49 by francema          #+#    #+#             */
/*   Updated: 2025/01/23 19:28:18 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_pipfd(t_pipex *pip)
{
	int	i;

	if (pip->here_doc_flag || pip->pip_idx == 0)
	{
		i = 1;
		close(pip->pipe_fd[pip->pip_idx][READ_END]);
		while(pip->pipe_fd[i])
		{
			close(pip->pipe_fd[i][WRITE_END]);
			close(pip->pipe_fd[i][READ_END]);
			i++;
		}
	}
	else if (pip->pip_idx != 0)
	{
		close
	}
}
