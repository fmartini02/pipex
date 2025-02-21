/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_cleaner.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francema <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:06:41 by francema          #+#    #+#             */
/*   Updated: 2025/02/21 11:13:30 by francema         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*clear the cmd args*/
void	free_args(char **args)
{
	int	i;

	i = 0;
	if (!args || !args[0])
		return ;
	while (args[i])
		free(args[i++]);
	free(args);
}

/*free before execve*/
void	free_bf_execve(t_pipex *pip)
{
	int	i;

	i = 0;
	while (i < pip->n_pipes)
		free(pip->pipe_fd[i++]);
	i = 0;
	while (i < pip->n_cmds)
		free(pip->cmds[i++]);
	free(pip->cmds);
	free(pip->pipe_fd);
	free(pip->file_in);
	free(pip->file_out);
}

/*this fun clear every things allocated but without using exit*/
void	free_here_doc(t_pipex *pip)
{
	int	i;

	i = 0;
	while (i < pip->n_pipes)
		free(pip->pipe_fd[i++]);
	i = 0;
	while (i < pip->n_cmds)
		free(pip->cmds[i++]);
	free(pip->cmds);
	free(pip->pipe_fd);
	free(pip->path);
	free_args(pip->args);
	free(pip->file_in);
	free(pip->file_out);
	if (pip->delimiter)
		free(pip->delimiter);
}

/*clear everything allocated and use exit in the middle of the execution*/
void	free_mid(t_pipex *pip, int exit_code)
{
	int	i;

	i = 0;
	while (i < pip->n_pipes)
		free(pip->pipe_fd[i++]);
	i = 0;
	while (i < pip->n_cmds)
		free(pip->cmds[i++]);
	free(pip->cmds);
	free(pip->pipe_fd);
	free_args(pip->args);
	free(pip->path);
	free(pip->file_in);
	free(pip->file_out);
	if (pip->here_doc_flag)
		free(pip->delimiter);
	exit(exit_code);
}

/*clear everything allocated and use exit*/
void	free_end(t_pipex *pip, int exit_code)
{
	int	i;

	i = 0;
	while (i < pip->n_pipes)
		free(pip->pipe_fd[i++]);
	i = 0;
	while (i < pip->n_cmds)
		free(pip->cmds[i++]);
	free(pip->cmds);
	free(pip->pipe_fd);
	free(pip->file_in);
	free(pip->file_out);
	if (pip->here_doc_flag)
		free(pip->delimiter);
	exit(exit_code);
}
